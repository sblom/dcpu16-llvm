//===-- Dcpu16SelectionDAGInfo.cpp - Dcpu16 SelectionDAG Info ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Dcpu16SelectionDAGInfo class.
//
//===----------------------------------------------------------------------===//

#define DEBUG_TYPE "dcpu16-selectiondag-info"
#include "Dcpu16TargetMachine.h"
using namespace llvm;

Dcpu16SelectionDAGInfo::Dcpu16SelectionDAGInfo(const Dcpu16TargetMachine &TM)
  : TargetSelectionDAGInfo(TM) {
}

Dcpu16SelectionDAGInfo::~Dcpu16SelectionDAGInfo() {
}
