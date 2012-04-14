//===-- Dcpu16RegisterInfo.h - Dcpu16 Register Information Impl ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Dcpu16 implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef DCPU16REGISTERINFO_H
#define DCPU16REGISTERINFO_H

#include "llvm/Target/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "Dcpu16GenRegisterInfo.inc"

namespace llvm {

class Dcpu16Subtarget;
class TargetInstrInfo;
class Type;

struct Dcpu16RegisterInfo : public Dcpu16GenRegisterInfo {
  Dcpu16Subtarget &Subtarget;
  const TargetInstrInfo &TII;

  Dcpu16RegisterInfo(Dcpu16Subtarget &st, const TargetInstrInfo &tii);

  /// Code Generation virtual methods...
  const uint16_t *getCalleeSavedRegs(const MachineFunction *MF = 0) const;

  BitVector getReservedRegs(const MachineFunction &MF) const;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I) const;

  void eliminateFrameIndex(MachineBasicBlock::iterator II,
                           int SPAdj, RegScavenger *RS = NULL) const;

  void processFunctionBeforeFrameFinalized(MachineFunction &MF) const;

  // Debug information queries.
  unsigned getFrameRegister(const MachineFunction &MF) const;

  // Exception handling queries.
  unsigned getEHExceptionRegister() const;
  unsigned getEHHandlerRegister() const;
};

} // end namespace llvm

#endif
