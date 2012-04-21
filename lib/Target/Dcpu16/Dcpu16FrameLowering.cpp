//===-- Dcpu16FrameLowering.cpp - Dcpu16 Frame Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Dcpu16 implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "Dcpu16FrameLowering.h"
#include "Dcpu16InstrInfo.h"
#include "Dcpu16MachineFunctionInfo.h"
#include "llvm/Function.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Target/TargetData.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/CommandLine.h"

using namespace llvm;

void Dcpu16FrameLowering::emitPrologue(MachineFunction &MF) const {
  MachineBasicBlock &MBB = MF.front();
  MachineFrameInfo *MFI = MF.getFrameInfo();
  const Dcpu16InstrInfo &TII =
    *static_cast<const Dcpu16InstrInfo*>(MF.getTarget().getInstrInfo());
  MachineBasicBlock::iterator MBBI = MBB.begin();
  DebugLoc dl = MBBI != MBB.end() ? MBBI->getDebugLoc() : DebugLoc();

  // Get the number of bytes to allocate from the FrameInfo
  int NumBytes = (int) MFI->getStackSize();

  /*BuildMI(MBB, MBBI, dl, TII.get(DCPU16::SETmar))
    .addReg(DCPU16::SP).addImm(-4).addReg(DCPU16::J);*/
  BuildMI(MBB, MBBI, dl, TII.get(DCPU16::ADDrc), DCPU16::SP)
    .addReg(DCPU16::SP).addImm(-NumBytes);
}

void Dcpu16FrameLowering::emitEpilogue(MachineFunction &MF,
                                  MachineBasicBlock &MBB) const {
  MachineBasicBlock::iterator MBBI = MBB.getLastNonDebugInstr();
  const Dcpu16InstrInfo &TII =
    *static_cast<const Dcpu16InstrInfo*>(MF.getTarget().getInstrInfo());
  DebugLoc dl = MBBI->getDebugLoc();
  assert(MBBI->getOpcode() == DCPU16::RET &&
         "Can only put epilog before 'ret' instruction!");

  MachineFrameInfo *MFI = MF.getFrameInfo();
  int NumBytes = (int) MFI->getStackSize();

  BuildMI(MBB, MBBI, dl, TII.get(DCPU16::ADDrc), DCPU16::SP)
    .addReg(DCPU16::SP).addImm(NumBytes);
  //BuildMI(MBB, MBBI, dl, TII.get(DCPU16::SETrma), DCPU16::J).addReg(DCPU16::J).addImm(-4);
}
