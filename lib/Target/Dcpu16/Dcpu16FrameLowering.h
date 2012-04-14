//===-- Dcpu16FrameLowering.h - Define frame lowering for Dcpu16 --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//
//===----------------------------------------------------------------------===//

#ifndef DCPU16_FRAMEINFO_H
#define DCPU16_FRAMEINFO_H

#include "Dcpu16.h"
#include "Dcpu16Subtarget.h"
#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
  class Dcpu16Subtarget;

class Dcpu16FrameLowering : public TargetFrameLowering {
  const Dcpu16Subtarget &STI;
public:
  explicit Dcpu16FrameLowering(const Dcpu16Subtarget &sti)
    : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 8, 0), STI(sti) {
  }

  /// emitProlog/emitEpilog - These methods insert prolog and epilog code into
  /// the function.
  void emitPrologue(MachineFunction &MF) const;
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const;

  bool hasFP(const MachineFunction &MF) const { return false; }
};

} // End llvm namespace

#endif
