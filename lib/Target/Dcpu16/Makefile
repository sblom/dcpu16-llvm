##===- lib/Target/Dcpu16/Makefile ---------------------------*- Makefile -*-===##
#
#                     The LLVM Compiler Infrastructure
#
# This file is distributed under the University of Illinois Open Source
# License. See LICENSE.TXT for details.
#
##===----------------------------------------------------------------------===##

LEVEL = ../../..
LIBRARYNAME = LLVMDcpu16CodeGen
TARGET = Dcpu16

# Make sure that tblgen is run, first thing.
BUILT_SOURCES = Dcpu16GenRegisterInfo.inc Dcpu16GenInstrInfo.inc \
		Dcpu16GenAsmWriter.inc Dcpu16GenDAGISel.inc \
		Dcpu16GenSubtargetInfo.inc Dcpu16GenCallingConv.inc

DIRS = TargetInfo MCTargetDesc

include $(LEVEL)/Makefile.common

