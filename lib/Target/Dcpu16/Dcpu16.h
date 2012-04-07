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

#include "llvm/Target/TargetMachine.h"

namespace Dcpu16CC {
  // Dcpu16 specific condition code.
  enum CondCodes {
    COND_E  = 0,  // aka COND_Z
    COND_NE = 1,  // aka COND_NZ
    COND_HS = 2,  // aka COND_C
    COND_LO = 3,  // aka COND_NC
    COND_GE = 4,
    COND_L  = 5,

    COND_INVALID = -1
  };
}

namespace llvm {
  class Dcpu16TargetMachine;
  class FunctionPass;
  class formatted_raw_ostream;

  FunctionPass *createDcpu16ISelDag(Dcpu16TargetMachine &TM,
                                    CodeGenOpt::Level OptLevel);

  FunctionPass *createDcpu16BranchSelectionPass();

} // end namespace llvm;

#endif
