include ../../oem-configuration/conti-oem-headers/buildConfiguration.mk

FOLDER_NAME := $(shell basename $(CURDIR))
TARGET := $(FOLDER_NAME)
PKG_CFG := $(FOLDER_NAME).pc
SYSTEMD := $(FOLDER_NAME).service

# 2nd-level subdirs, for example: common/mailboxes/ libraries/client_ipc/ services/server_ipc/ ...
SUBDIRS := $(wildcard */)
SUBDIRS := $(filter-out patch/, $(SUBDIRS))
SUBDIRS := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)*/))
SUBDIRS := $(filter-out $(wildcard common/*) $(wildcard libraries/*) $(wildcard services/*), $(SUBDIRS))
SUBDIRS := $(sort $(dir $(SUBDIRS)))

SOURCES := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)*.cpp))
OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(SOURCES:.cpp=.d)
HEADERS := $(foreach dir, $(SUBDIRS), $(wildcard $(dir)*.h))

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

export CCFLAGS
export LDFLAGS

$(info **************** DEBUG_AREA ****************)
# print log here
$(info **************** DEBUG_AREA ****************)

.PHONY : all install clean distclean

all : install

install : $(TARGET)
	$(call installExec, $(TARGET), $(DESTDIR_INT)/tst/bin/)
	$(call installFile, ./services/console/console.xml, $(CONSOLE_XML_PATH)$(FOLDER_NAME))

$(TARGET) : $(OBJECTS)
	$(CC) $(CCFLAGS) $(LDFLAGS) $^ -o $@

%.o : %.cpp
	$(CC) $(CCFLAGS) -c $< -o $@

clean distclean:
	rm -rf $(TARGET)
	rm -rf $(OBJECTS)
	rm -rf $(DEPENDS)
