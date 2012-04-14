//===-- Dcpu16TargetInfo.cpp - Dcpu16 Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Dcpu16.h"
#include "llvm/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target llvm::TheDcpu16Target;
Target llvm::TheDcpu16V9Target;

extern "C" void LLVMInitializeDcpu16TargetInfo() {
  RegisterTarget<Triple::dcpu16> X(TheDcpu16Target, "dcpu16", "Dcpu16");
}
