//===-- Dcpu16TargetMachine.h - Define TargetMachine for Dcpu16 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Dcpu16 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef DCPU16TARGETMACHINE_H
#define DCPU16TARGETMACHINE_H

#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {

class Dcpu16TargetMachine : public LLVMTargetMachine {
  const TargetData DataLayout;       // Calculates type size & alignment
public:
  Dcpu16TargetMachine(const Target &T, StringRef TT,
                     StringRef CPU, StringRef FS, const TargetOptions &Options,
                     Reloc::Model RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);

  virtual const TargetData       *getTargetData() const { return &DataLayout; }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM);
};

} // end namespace llvm

#endif
