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

#include "Dcpu16InstrInfo.h"
#include "Dcpu16ISelLowering.h"
#include "Dcpu16FrameLowering.h"
#include "Dcpu16SelectionDAGInfo.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {

class Dcpu16TargetMachine : public LLVMTargetMachine {
  const TargetData DataLayout;       // Calculates type size & alignment
  Dcpu16TargetLowering TLInfo;
  Dcpu16SelectionDAGInfo TSInfo;
  Dcpu16InstrInfo InstrInfo;
  Dcpu16FrameLowering FrameLowering;
public:
  Dcpu16TargetMachine(const Target &T, StringRef TT,
                     StringRef CPU, StringRef FS, const TargetOptions &Options,
                     Reloc::Model RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);

  virtual const Dcpu16InstrInfo *getInstrInfo() const { return &InstrInfo; }
  virtual const TargetFrameLowering  *getFrameLowering() const {
    return &FrameLowering;
  }
  virtual const Dcpu16RegisterInfo *getRegisterInfo() const {
    return &InstrInfo.getRegisterInfo();
  }
  virtual const Dcpu16TargetLowering* getTargetLowering() const {
    return &TLInfo;
  }
  virtual const Dcpu16SelectionDAGInfo* getSelectionDAGInfo() const {
    return &TSInfo;
  }
  virtual const TargetData       *getTargetData() const { return &DataLayout; }

  // Pass Pipeline Configuration
  virtual TargetPassConfig *createPassConfig(PassManagerBase &PM);
};

} // end namespace llvm

#endif
