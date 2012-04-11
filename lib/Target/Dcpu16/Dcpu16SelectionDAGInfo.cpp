#include "Dcpu16TargetMachine.h"
using namespace llvm;

Dcpu16SelectionDAGInfo::Dcpu16SelectionDAGInfo(const Dcpu16TargetMachine &TM)
  : TargetSelectionDAGInfo(TM) {
}

Dcpu16SelectionDAGInfo::~Dcpu16SelectionDAGInfo() {
}
