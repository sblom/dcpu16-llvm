//===-- Dcpu16MCTargetDesc.cpp - Dcpu16 Target Descriptions -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Dcpu16 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "Dcpu16MCTargetDesc.h"
#include "Dcpu16MCAsmInfo.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Dcpu16GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "Dcpu16GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Dcpu16GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createDcpu16MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitDcpu16MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createDcpu16MCRegisterInfo(StringRef TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitDcpu16MCRegisterInfo(X, DCPU16::Z);
  return X;
}

static MCSubtargetInfo *createDcpu16MCSubtargetInfo(StringRef TT, StringRef CPU,
                                                   StringRef FS) {
  MCSubtargetInfo *X = new MCSubtargetInfo();
  InitDcpu16MCSubtargetInfo(X, TT, CPU, FS);
  return X;
}

static MCCodeGenInfo *createDcpu16MCCodeGenInfo(StringRef TT, Reloc::Model RM,
                                               CodeModel::Model CM,
                                               CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  X->InitMCCodeGenInfo(RM, CM, OL);
  return X;
}

extern "C" void LLVMInitializeDcpu16TargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<Dcpu16ELFMCAsmInfo> X(TheDcpu16Target);
  RegisterMCAsmInfo<Dcpu16ELFMCAsmInfo> Y(TheDcpu16V9Target);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheDcpu16Target,
                                       createDcpu16MCCodeGenInfo);
  TargetRegistry::RegisterMCCodeGenInfo(TheDcpu16V9Target,
                                       createDcpu16MCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheDcpu16Target, createDcpu16MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheDcpu16Target, createDcpu16MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheDcpu16Target,
                                          createDcpu16MCSubtargetInfo);
}
