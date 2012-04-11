#ifndef DCPU16INSTRUCTIONINFO_H
#define DCPU16INSTRUCTIONINFO_H

#include "Dcpu16RegisterInfo.h"
#include "llvm/Target/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "Dcpu16GenInstrInfo.inc"

namespace llvm {

class Dcpu16InstrInfo : public Dcpu16GenInstrInfo {
  const Dcpu16RegisterInfo RI;

public:
  virtual const Dcpu16RegisterInfo &getRegisterInfo() const { return RI; }
};
}

#endif
