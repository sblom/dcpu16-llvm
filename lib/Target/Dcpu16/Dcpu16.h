//==-- Dcpu16.h - Top-level interface for Dcpu16 representation --*- C++ -*-==//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in
// the LLVM Dcpu16 backend.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TARGET_DCPU16_H
#define LLVM_TARGET_DCPU16_H

#include "MCTargetDesc/Dcpu16MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class Target;

extern Target TheDcpu16Target;

namespace llvm {
  class Dcpu16TargetMachine;
  class FunctionPass;
  class formatted_raw_ostream;

  FunctionPass *createDcpu16ISelDag(Dcpu16TargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createDcpu16BranchSelectionPass();

} // end namespace llvm;

#endif
