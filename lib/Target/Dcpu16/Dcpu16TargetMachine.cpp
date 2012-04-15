//===-- Dcpu16TargetMachine.cpp - Define TargetMachine for Dcpu16 -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "Dcpu16TargetMachine.h"
#include "Dcpu16.h"
#include "llvm/PassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeDcpu16Target() {
  // Register the target.
  RegisterTargetMachine<Dcpu16V8TargetMachine> X(TheDcpu16Target);
  RegisterTargetMachine<Dcpu16V9TargetMachine> Y(TheDcpu16V9Target);
}

/// Dcpu16TargetMachine ctor - Create an ILP32 architecture model
///
Dcpu16TargetMachine::Dcpu16TargetMachine(const Target &T, StringRef TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Reloc::Model RM, CodeModel::Model CM,
                                       CodeGenOpt::Level OL,
                                       bool is64bit)
  : LLVMTargetMachine(T, TT, CPU, FS, Options, RM, CM, OL),
    Subtarget(TT, CPU, FS, is64bit),
    DataLayout(Subtarget.getDataLayout()),
    TLInfo(*this), TSInfo(*this), InstrInfo(Subtarget),
    FrameLowering(Subtarget) {
}

namespace {
/// Dcpu16 Code Generator Pass Configuration Options.
class Dcpu16PassConfig : public TargetPassConfig {
public:
  Dcpu16PassConfig(Dcpu16TargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  Dcpu16TargetMachine &getDcpu16TargetMachine() const {
    return getTM<Dcpu16TargetMachine>();
  }

  virtual bool addInstSelector();
  virtual bool addPreEmitPass();
};
} // namespace

TargetPassConfig *Dcpu16TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new Dcpu16PassConfig(this, PM);
}

bool Dcpu16PassConfig::addInstSelector() {
  PM.add(createDcpu16ISelDag(getDcpu16TargetMachine()));
  return false;
}

/// addPreEmitPass - This pass may be implemented by targets that want to run
/// passes immediately before machine code is emitted.  This should return
/// true if -print-machineinstrs should print out the code after the passes.
bool Dcpu16PassConfig::addPreEmitPass(){
  return true;
}

void Dcpu16V8TargetMachine::anchor() { }

Dcpu16V8TargetMachine::Dcpu16V8TargetMachine(const Target &T,
                                           StringRef TT, StringRef CPU,
                                           StringRef FS,
                                           const TargetOptions &Options,
                                           Reloc::Model RM,
                                           CodeModel::Model CM,
                                           CodeGenOpt::Level OL)
  : Dcpu16TargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, false) {
}

void Dcpu16V9TargetMachine::anchor() { }

Dcpu16V9TargetMachine::Dcpu16V9TargetMachine(const Target &T,
                                           StringRef TT,  StringRef CPU,
                                           StringRef FS,
                                           const TargetOptions &Options,
                                           Reloc::Model RM,
                                           CodeModel::Model CM,
                                           CodeGenOpt::Level OL)
  : Dcpu16TargetMachine(T, TT, CPU, FS, Options, RM, CM, OL, true) {
}
