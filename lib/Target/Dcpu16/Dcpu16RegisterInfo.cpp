#include "Dcpu16RegisterInfo.h"
#include "Dcpu16.h"
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

// TODO(jfrikker): Let's have some of these!
const uint16_t* Dcpu16RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF)
                                                                         const {
  static const uint16_t CalleeSavedRegs[] = { 0 };
  return CalleeSavedRegs;
}

BitVector Dcpu16RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}

void Dcpu16RegisterInfo::
eliminateCallFramePseudoInstr(MachineFunction &MF, MachineBasicBlock &MBB,
                              MachineBasicBlock::iterator I) const {
}

void
Dcpu16RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                       int SPAdj, RegScavenger *RS) const {
}

void Dcpu16RegisterInfo::
processFunctionBeforeFrameFinalized(MachineFunction &MF) const {}

unsigned Dcpu16RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return SP::I6;
}

unsigned Dcpu16RegisterInfo::getEHExceptionRegister() const {
  llvm_unreachable("What is the exception register");
}

unsigned Dcpu16RegisterInfo::getEHHandlerRegister() const {
  llvm_unreachable("What is the exception handler register");
}
