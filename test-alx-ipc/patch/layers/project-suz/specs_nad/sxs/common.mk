########################################################
# Copyright 2019 Continental Automotive Systems Inc.
# ########################################################
#.
#.%define sbr_hw_variant %(echo $CAS_TARGET_HW | grep sbr)
#.%define suz_hw_variant %(echo $CAS_TARGET_HW | grep suz)
#.
#.Summary         : common module
#.License         : Continental AG.
#.Group           : Module
#.Requires        : glib conti-tp-common conti-persistence libxml2 conti-persistence--pcl conti-vcs conti-location-mgr telematics-services-frwk telematics-services audio connectivity oem-configuration pss-v2x telematics-services-voicemgr openssl
#.After           : openssl
#.#MocksExcluded  : conti-tp-common conti-persistence conti-persistence--pcl conti-vcs conti-location-mgr
#.#MocksExcluded  : telematics-services-frwk telematics-services audio connectivity oem-configuration pss-v2x
#.#Sanitizers     : sanitize sanitize-thread sanitize-memory
#.
#.#using summary for description
#.%description
#.%{summary}
#.
#.%package devel
#.Group           : Module
#.Summary         : common
#.
#.%description devel
#.This package contains Function Center Common module
#.
#.%files
#.%defattr(-,root,root)
#./tst/console/*
#./tst/bin/*
#.%{opt_dir}/lib/*.so*
#.%{opt_dir}/share/*
#.%{opt_dir}/bin/*
#./lib/systemd/system
#.
#.%files devel
#.%defattr(-,root,root)
#.%{opt_dir}/include/*
#./opt/conti/lib/pkgconfig/*

CAS_TARGET_HW_PREFIX = $(shell echo ${CAS_TARGET_HW} | head -c 6)

# Common packages names that are CPU NODE agnostic: SYS
include conti/conti-test.inc
# conti-dcm path switcher
ifneq (,$(findstring sbr,${CAS_TARGET_HW}))
CONTIDCM = conti-dcm-sbr
else ifneq (,$(findstring suz,${CAS_TARGET_HW}))
CONTIDCM = conti-dcm-szk
else
CONTIDCM =
endif

ifneq (,$(findstring sbr,${CAS_TARGET_HW}))
SUBDIRS = conti-gm-fs \
conti-gm-configuration \
$(CONTIDCM) \
autonomous-logger-client
else ifneq (,$(findstring suz,${CAS_TARGET_HW}))
SUBDIRS = conti-gm-fs \
conti-gm-configuration \
$(CONTIDCM) \
autonomous-logger-client \
dce-pf-api \
test-alx-ipc \
test-mtls
endif

all docs install uninstall:
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	  echo "Running target [$@] in [$$subdir]"; \
	  (cd $$subdir && $(MAKE) $@ DESTDIR=$(buildroot) MAKE_CMD=$@) || exit $$?; \
	done;

clean distclean clobber:
	list='$(SUBDIRS)'; \
	for subdir in $$list; do \
	  echo "Running target [$@] in [$$subdir]"; \
	  (cd $$subdir && $(MAKE) $@ DESTDIR=$(bld_top_dir)/release/fs/devel && MAKE_CMD=$@) || exit $$?; \
	  (cd $$subdir && $(MAKE) $@ DESTDIR=$(abspath ${CURDIR}/../targetbuild) && MAKE_CMD=$@) || exit $$?; \
	done;
