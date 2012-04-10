include "llvm/Target/Target.td"

include "Dcpu16RegisterInfo.td"
// include "SparcCallingConv.td"
include "Dcpu16InstrInfo.td"

def Dcpu16InstrInfo : InstrInfo;

def Dcpu16 : Target {
  let InstructionSet = Dcpu16InstrInfo;
}
