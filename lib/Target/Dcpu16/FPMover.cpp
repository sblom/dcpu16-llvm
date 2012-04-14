//===-- FPMover.cpp - Dcpu16 double-precision floating point move fixer ----===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Expand FpMOVD/FpABSD/FpNEGD instructions into their single-precision pieces.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "fpmover"
#include "Dcpu16.h"
#include "Dcpu16Subtarget.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetInstrInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

STATISTIC(NumFpDs , "Number of instructions translated");
STATISTIC(NoopFpDs, "Number of noop instructions removed");

namespace {
  struct FPMover : public MachineFunctionPass {
    /// Target machine description which we query for reg. names, data
    /// layout, etc.
    ///
    TargetMachine &TM;

    static char ID;
    explicit FPMover(TargetMachine &tm)
      : MachineFunctionPass(ID), TM(tm) { }

    virtual const char *getPassName() const {
      return "Dcpu16 Double-FP Move Fixer";
    }

    bool runOnMachineBasicBlock(MachineBasicBlock &MBB);
    bool runOnMachineFunction(MachineFunction &F);
  };
  char FPMover::ID = 0;
} // end of anonymous namespace

/// createDcpu16FPMoverPass - Returns a pass that turns FpMOVD
/// instructions into FMOVS instructions
///
FunctionPass *llvm::createDcpu16FPMoverPass(TargetMachine &tm) {
  return new FPMover(tm);
}

/// getDoubleRegPair - Given a DFP register, return the even and odd FP
/// registers that correspond to it.
static void getDoubleRegPair(unsigned DoubleReg, unsigned &EvenReg,
                             unsigned &OddReg) {
  static const uint16_t EvenHalvesOfPairs[] = {
    DCPU16::F0, DCPU16::F2, DCPU16::F4, DCPU16::F6, DCPU16::F8, DCPU16::F10, DCPU16::F12, DCPU16::F14,
    DCPU16::F16, DCPU16::F18, DCPU16::F20, DCPU16::F22, DCPU16::F24, DCPU16::F26, DCPU16::F28, DCPU16::F30
  };
  static const uint16_t OddHalvesOfPairs[] = {
    DCPU16::F1, DCPU16::F3, DCPU16::F5, DCPU16::F7, DCPU16::F9, DCPU16::F11, DCPU16::F13, DCPU16::F15,
    DCPU16::F17, DCPU16::F19, DCPU16::F21, DCPU16::F23, DCPU16::F25, DCPU16::F27, DCPU16::F29, DCPU16::F31
  };
  static const uint16_t DoubleRegsInOrder[] = {
    DCPU16::D0, DCPU16::D1, DCPU16::D2, DCPU16::D3, DCPU16::D4, DCPU16::D5, DCPU16::D6, DCPU16::D7, DCPU16::D8,
    DCPU16::D9, DCPU16::D10, DCPU16::D11, DCPU16::D12, DCPU16::D13, DCPU16::D14, DCPU16::D15
  };
  for (unsigned i = 0; i < array_lengthof(DoubleRegsInOrder); ++i)
    if (DoubleRegsInOrder[i] == DoubleReg) {
      EvenReg = EvenHalvesOfPairs[i];
      OddReg = OddHalvesOfPairs[i];
      return;
    }
  llvm_unreachable("Can't find reg");
}

/// runOnMachineBasicBlock - Fixup FpMOVD instructions in this MBB.
///
bool FPMover::runOnMachineBasicBlock(MachineBasicBlock &MBB) {
  bool Changed = false;
  for (MachineBasicBlock::iterator I = MBB.begin(); I != MBB.end(); ) {
    MachineInstr *MI = I++;
    DebugLoc dl = MI->getDebugLoc();
    if (MI->getOpcode() == DCPU16::FpMOVD || MI->getOpcode() == DCPU16::FpABSD ||
        MI->getOpcode() == DCPU16::FpNEGD) {
      Changed = true;
      unsigned DestDReg = MI->getOperand(0).getReg();
      unsigned SrcDReg  = MI->getOperand(1).getReg();
      if (DestDReg == SrcDReg && MI->getOpcode() == DCPU16::FpMOVD) {
        MBB.erase(MI);   // Eliminate the noop copy.
        ++NoopFpDs;
        continue;
      }

      unsigned EvenSrcReg = 0, OddSrcReg = 0, EvenDestReg = 0, OddDestReg = 0;
      getDoubleRegPair(DestDReg, EvenDestReg, OddDestReg);
      getDoubleRegPair(SrcDReg, EvenSrcReg, OddSrcReg);

      const TargetInstrInfo *TII = TM.getInstrInfo();
      if (MI->getOpcode() == DCPU16::FpMOVD)
        MI->setDesc(TII->get(DCPU16::FMOVS));
      else if (MI->getOpcode() == DCPU16::FpNEGD)
        MI->setDesc(TII->get(DCPU16::FNEGS));
      else if (MI->getOpcode() == DCPU16::FpABSD)
        MI->setDesc(TII->get(DCPU16::FABSS));
      else
        llvm_unreachable("Unknown opcode!");

      MI->getOperand(0).setReg(EvenDestReg);
      MI->getOperand(1).setReg(EvenSrcReg);
      DEBUG(errs() << "FPMover: the modified instr is: " << *MI);
      // Insert copy for the other half of the double.
      if (DestDReg != SrcDReg) {
        MI = BuildMI(MBB, I, dl, TM.getInstrInfo()->get(DCPU16::FMOVS), OddDestReg)
          .addReg(OddSrcReg);
        DEBUG(errs() << "FPMover: the inserted instr is: " << *MI);
      }
      ++NumFpDs;
    }
  }
  return Changed;
}

bool FPMover::runOnMachineFunction(MachineFunction &F) {
  // If the target has V9 instructions, the fp-mover pseudos will never be
  // emitted.  Avoid a scan of the instructions to improve compile time.
  if (TM.getSubtarget<Dcpu16Subtarget>().isV9())
    return false;

  bool Changed = false;
  for (MachineFunction::iterator FI = F.begin(), FE = F.end();
       FI != FE; ++FI)
    Changed |= runOnMachineBasicBlock(*FI);
  return Changed;
}
