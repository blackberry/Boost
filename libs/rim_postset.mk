# Post-set make macros common to the recursive makefiles

# Use the QNX build system's $(VARIANT_LIST) to determine whether to use
# debugging libraries, etc.
ifeq ($(filter g,$(VARIANT_LIST)),g)
  CCFLAGS += -O0
else
  # Non-debug build.
  #
  # Enable optimizations suitable for modern C++.
  CCFLAGS += -O3
endif
