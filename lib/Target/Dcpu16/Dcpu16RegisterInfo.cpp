//===-- Dcpu16RegisterInfo.cpp - DCPU16 Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the DCPU16 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "Dcpu16RegisterInfo.h"
#include "Dcpu16.h"
#include "Dcpu16Subtarget.h"
#include "llvm/Type.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"

#define GET_REGINFO_TARGET_DESC
#include "Dcpu16GenRegisterInfo.inc"

using namespace llvm;

Dcpu16RegisterInfo::Dcpu16RegisterInfo(Dcpu16Subtarget &st,
                                     const TargetInstrInfo &tii)
  : Dcpu16GenRegisterInfo(DCPU16::Z), Subtarget(st), TII(tii) {
}

const uint16_t* Dcpu16RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF)
                                                                         const {
  static const uint16_t CalleeSavedRegs[] = { 0 };
  return CalleeSavedRegs;
}

BitVector Dcpu16RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  // FIXME: G1 reserved for now for large imm generation by frame code.
  /*Reserved.set(DCPU16::G1);
  Reserved.set(DCPU16::G2);
  Reserved.set(DCPU16::G3);
  Reserved.set(DCPU16::G4);
  Reserved.set(DCPU16::O6);
  Reserved.set(DCPU16::I6);
  Reserved.set(DCPU16::I7);
  Reserved.set(DCPU16::G0);
  Reserved.set(DCPU16::G5);
  Reserved.set(DCPU16::G6);
  Reserved.set(DCPU16::G7);*/
  return Reserved;
}

void Dcpu16RegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {
  /*MachineInstr &MI = *I;
  DebugLoc dl = MI.getDebugLoc();
  int Size = MI.getOperand(0).getImm();
  if (MI.getOpcode() == DCPU16::ADJCALLSTACKDOWN)
    Size = -Size;
  if (Size)
    BuildMI(MBB, I, dl, TII.get(DCPU16::ADDri), DCPU16::O6).addReg(DCPU16::O6).addImm(Size);
  MBB.erase(I);*/
}

void
Dcpu16RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                       int SPAdj, RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  unsigned i = 0;
  MachineInstr &MI = *II;
  DebugLoc dl = MI.getDebugLoc();
  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands() && "Instr doesn't have FrameIndex operand!");
  }

  int FrameIndex = MI.getOperand(i).getIndex();

  // Addressable stack objects are accessed using neg. offsets from %fp
  MachineFunction &MF = *MI.getParent()->getParent();
  int Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex) +
               MI.getOperand(i+1).getImm();
  Offset -= 8;

  // Replace frame index with a frame pointer reference.
  // If the offset is small enough to fit in the immediate field, directly
  // encode it.
  MI.getOperand(i).ChangeToRegister(DCPU16::J, false);
  MI.getOperand(i+1).ChangeToImmediate(Offset);
}

void Dcpu16RegisterInfo::
processFunctionBeforeFrameFinalized(MachineFunction &MF) const {}

unsigned Dcpu16RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return DCPU16::SP;
}

unsigned Dcpu16RegisterInfo::getEHExceptionRegister() const {
  llvm_unreachable("What is the exception register");
}

unsigned Dcpu16RegisterInfo::getEHHandlerRegister() const {
  llvm_unreachable("What is the exception handler register");
}
