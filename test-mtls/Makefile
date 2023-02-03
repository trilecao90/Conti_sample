include ../../oem-configuration/conti-oem-headers/buildConfiguration.mk

SUBDIRS := $(wildcard */)
SUBDIRS := $(filter-out patch/, $(SUBDIRS))
SUBDIRS := $(sort $(dir $(SUBDIRS)))

TARGET_CLIENT := ./mtls_client/mtls_client
TARGET_SERVER := ./mtls_server/mtls_server

CCFLAGS += $(addprefix -I $(CURDIR)/, $(SUBDIRS))

packages := \
conti-oem-headers \
conti-alx-framework \
conti-alx-framework-client \
conti-alx-framework-config \
conti-alx-framework-console \
conti-alx-framework-inc \
conti-alx-framework-ipc \
tpsys \
glib-2.0

CCFLAGS += `pkg-config --cflags $(packages)`
LDFLAGS += `pkg-config --libs $(packages)`

CCFLAGS += -g $(OPTIMIZATIONS) -rdynamic -funwind-tables -flto -Wall -MMD -fasynchronous-unwind-tables -fPIC -DNAD_CPU -DPACK_ON -std=gnu++17

CCFLAGS += -I $(DESTDIR)/usr/include/
LDFLAGS += -L$(DESTDIR)/usr/lib/ -lssl -lcrypto

export CCFLAGS
export LDFLAGS

.PHONY : all install clean distclean $(SUBDIRS)

all : install

install : $(SUBDIRS)
	$(call installExec, $(TARGET_CLIENT), $(DESTDIR_INT)/tst/bin/)
	$(call installExec, $(TARGET_SERVER), $(DESTDIR_INT)/tst/bin/)

$(TARGET_CLIENT) $(TARGET_SERVER) : $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) all -C $@

clean distclean:
	for dir in $(SUBDIRS) ; do \
		$(MAKE) $@ -C $$dir ; \
	done
