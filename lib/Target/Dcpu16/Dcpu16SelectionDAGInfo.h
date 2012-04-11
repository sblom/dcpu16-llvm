#ifndef DCPU16SELECTIONDAGINFO_H
#define DCPU16SELECTIONDAGINFO_H

#include "llvm/Target/TargetSelectionDAGInfo.h"

namespace llvm {

class Dcpu16TargetMachine;

class Dcpu16SelectionDAGInfo : public TargetSelectionDAGInfo {
public:
  explicit Dcpu16SelectionDAGInfo(const Dcpu16TargetMachine &TM);
  ~Dcpu16SelectionDAGInfo();
};

}

#endif
