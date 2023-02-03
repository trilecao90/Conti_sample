#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/rsa.h>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CHK_NULL(x) if((x) == NULL) exit(1);
#define CHK_ERR(err, s) if((err) == -1) { perror(s); exit(1); }
#define CHK_SSL(err) if((err) == -1) { ERR_print_errors_fp(stderr); exit(2); }

int main(void) {
int err;
    int listen_sd;
    int sd;
    struct sockaddr_in sa_serv;
    struct sockaddr_in sa_cli;
    size_t client_len;

    SSL_CTX  *ctx;
    SSL    *ssl;
    X509                *client_cert;
    char                *str;
    char                buf[4096];
    const SSL_METHOD  *meth;

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();
    meth = TLS_server_method();
    ctx = SSL_CTX_new(meth);

    if(!ctx) {
        ERR_print_errors_fp(stderr);
        exit(2);
    }

    if(SSL_CTX_use_certificate_file(ctx, "./servercert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(3);
    }

    if(SSL_CTX_use_PrivateKey_file(ctx, "./serverkey.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(4);
    }

    if(!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr, "Private key does not match the certificate public keyn");
        exit(5);
    }

    listen_sd = socket(AF_INET, SOCK_STREAM, 0);
    CHK_ERR(listen_sd, "socket");

    memset(&sa_serv, 0x00, sizeof(sa_serv));
    sa_serv.sin_family = AF_INET;
    sa_serv.sin_addr.s_addr = INADDR_ANY;
    sa_serv.sin_port = htons(1111);

    err = bind(listen_sd, (struct sockaddr*)&sa_serv, sizeof(sa_serv));
    CHK_ERR(err, "bind");

    err = listen(listen_sd, 5);
    CHK_ERR(err, "listen");

    client_len = sizeof(sa_cli);
    sd = accept(listen_sd, (struct sockaddr*)&sa_cli, (socklen_t*) &client_len);
    CHK_ERR(sd, "accept");
    close(listen_sd);

    // to request client's certificate
    SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER | SSL_VERIFY_FAIL_IF_NO_PEER_CERT, NULL);

    if(!SSL_CTX_load_verify_locations(ctx, "cacert.pem", "./")) {
        ERR_print_errors_fp(stderr);
        exit(6);
    }

    ssl = SSL_new(ctx);
    CHK_NULL(ssl);
    SSL_set_fd(ssl, sd);

    err = SSL_accept(ssl);
    CHK_SSL(err);

    printf("SSL connection using %s \n", SSL_get_cipher(ssl));

    client_cert = SSL_get_peer_certificate(ssl);

    if(client_cert != NULL) {
        printf("Client certificate: \n");

        str = X509_NAME_oneline(X509_get_subject_name(client_cert), 0, 0);
        CHK_NULL(str);
        printf("\t subject: %s\n", str);
        OPENSSL_free(str);

        str = X509_NAME_oneline(X509_get_issuer_name(client_cert), 0, 0);
        CHK_NULL(str);
        printf("\t issuer: %s\n", str);
        OPENSSL_free(str);

        X509_free(client_cert);
    } else {
        printf("Client does not have certificate. \n");
    }

    err = SSL_read(ssl, buf, sizeof(buf)-1);
    CHK_SSL(err);
    buf[err] = 0x00;
    printf("Got %d chars: %s \n", err, buf);

    err = SSL_write(ssl, "Hello from Server!", strlen("Hello from Server!"));
    CHK_SSL(err);

    close(sd);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return(0);
}