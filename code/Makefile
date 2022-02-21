# Makefile to build class stp_synthetic_reverb for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
lib.name = externals.howto.stp_synthetic_reverb

# input source file (class name == source file basename)
class.sources = stp_synthetic_reverb~.c
stp_synthetic_reverb~.class.sources = stp_delay.c stp_low_pass.c stp_comb_filter.c stp_all_pass_filter.c stp_synthetic_reverb.c 
# all extra files to be included in binary distribution of the library
datafiles =

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder
