#include <stdio.h>
#include <memory.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CHK_NULL(x) if((x) == NULL) exit(1);
#define CHK_ERROR(err) if((err) <= 0) exit(1);
#define CHK_ERR(err, s) if((err) == -1) { perror(s); exit(1); }
#define CHK_SSL(err) if((err) == -1) { ERR_print_errors_fp(stderr); exit(2); }

int main(void) {
    int err;
    int sd;
    struct sockaddr_in sa;

    SSL_CTX   *ctx;
    SSL     *ssl;
    X509                    *server_cert;
    char                    *str;
    char                    buf[4096];
    const SSL_METHOD    *meth;

    SSL_load_error_strings();
    SSLeay_add_ssl_algorithms();
    meth = TLS_client_method();
    ctx = SSL_CTX_new(meth);
    CHK_NULL(ctx);

    if(SSL_CTX_use_certificate_file(ctx, "./clientcert.pem", SSL_FILETYPE_PEM) <= 0) {
        ERR_print_errors_fp(stderr);
        exit(3);
    }

    if(SSL_CTX_use_PrivateKey_file(ctx, "./clientkey.pem", SSL_FILETYPE_PEM) <= 0) {
    ERR_print_errors_fp(stderr);
    exit(4);
    }

    if(!SSL_CTX_check_private_key(ctx)) {
        fprintf(stderr, "Private key does not match the certificate public keyn");
        exit(5);
    }

    CHK_SSL(err);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    CHK_ERR(sd, "socket");

    memset(&sa, 0x00, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    sa.sin_port = htons(1111);

    err = connect(sd, (struct sockaddr*)&sa, sizeof(sa));
    CHK_ERR(err, "connect");

    ssl = SSL_new(ctx);
    CHK_NULL(ssl);

    SSL_set_fd(ssl, sd);
    err = SSL_connect(ssl);
    CHK_ERROR(err);

    printf("SSL connection using %s \n", SSL_get_cipher(ssl));

    server_cert = SSL_get_peer_certificate(ssl);
    CHK_NULL(server_cert);
    printf("Server certificate: \n");

    str = X509_NAME_oneline(X509_get_subject_name(server_cert), 0, 0);
    CHK_NULL(str);
    printf("\t subject: %s \n", str);
    OPENSSL_free(str);

    str = X509_NAME_oneline(X509_get_issuer_name(server_cert), 0, 0);
    CHK_NULL(str);
    printf("\t issuer: %s \n", str);
    OPENSSL_free(str);

    X509_free(server_cert);

    err = SSL_write(ssl, "Hello from Client!", strlen("Hello from Client!"));
    CHK_SSL(err);

    err = SSL_read(ssl, buf, sizeof(buf)-1);
    CHK_SSL(err);
    buf[err] = 0x0;
    printf("Got %d chars: %s \n", err, buf);
    SSL_shutdown(ssl);

    close(sd);
    SSL_free(ssl);
    SSL_CTX_free(ctx);

    return 0;
}