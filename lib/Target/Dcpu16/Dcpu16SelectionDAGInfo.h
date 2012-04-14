//===-- Dcpu16SelectionDAGInfo.h - Dcpu16 SelectionDAG Info -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the Dcpu16 subclass for TargetSelectionDAGInfo.
//
//===----------------------------------------------------------------------===//

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
