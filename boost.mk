#
# Copyright (c) 2011 Research In Motion Limited.
#

# Default target is release build for both platforms
default: x86 armv7le tests

TARGET         = $(QMAKE_TARGET)
MAVEN	       = mvn
MAVEN_FLAGS    = -s PlayBook-build/dev-settings.xml -f PlayBook-build/pom.xml


.PHONY: install hinstall clean Makefile-test tests tests-clean tests-distclean

# Run qmake to generate makefiles if not already present
Makefile-test:
	# $(QMAKE-HOST) -spec $(MKSPEC-HOST) -o Makefile tests/*.pro

# Define targets for host platform 
tests: Makefile-test 
	# $(MAKE) -C tests -f Makefile debug

tests-%: Makefile-test
	# $(MAKE) -C tests -f Makefile $*

install:
	bash PlayBook-build/build.sh install
	mkdir -p /tmp/target
	cp -r PlayBook-build/boost-stage/target/qnx6/* $(QNX_TARGET)

hinstall:
	bash PlayBook-build/build.sh hinstall
	mkdir -p /tmp/target/usr/include
	cp -r PlayBook-build/boost-stage/target/qnx6/usr/include/* $(QNX_TARGET)/usr/include

clean:
	bash PlayBook-build/build.sh clean

# Define maven targets
#install - maven build step
mvn-install: 
	$(MAKE) hinstall install
	${MAVEN} ${MAVEN_FLAGS} install

deploy: 
	$(MAKE) hinstall install
	${MAVEN} ${MAVEN_FLAGS} deploy

docs:
	${MAVEN} ${MAVEN_FLAGS} site
	
debug: 
	$(MAKE) VARIANTLIST=g hinstall install

release: 
	$(MAKE) EXCLUDE_VARIANTLIST=g hinstall install

simulator:
	 $(MAKE) CPULIST=x86 hinstall install

device: 
	$(MAKE) CPULIST=arm hinstall install

check: tests
	$(TEST-RUNNER)

