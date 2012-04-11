//===-- Dcpu16MCTargetDesc.h - Dcpu16 Target Descriptions -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Dcpu16 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#ifndef DCPU16MCTARGETDESC_H
#define DCPU16MCTARGETDESC_H

namespace llvm {
class Target;

extern Target TheDcpu16Target;

} // End llvm namespace

// Defines symbolic names for Dcpu16 registers.
// This defines a mapping from register name to register number.
#define GET_REGINFO_ENUM
#include "Dcpu16GenRegisterInfo.inc"

// Defines symbolic names for the Dcpu16 instructions.
#define GET_INSTRINFO_ENUM
#include "Dcpu16GenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "Dcpu16GenSubtargetInfo.inc"

#endif
