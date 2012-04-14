//===-- Dcpu16MCAsmInfo.h - Dcpu16 asm properties ----------------*- C++ -*--===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the Dcpu16MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef DCPU16TARGETASMINFO_H
#define DCPU16TARGETASMINFO_H

#include "llvm/MC/MCAsmInfo.h"

namespace llvm {
  class StringRef;
  class Target;

  class Dcpu16ELFMCAsmInfo : public MCAsmInfo {
    virtual void anchor();
  public:
    explicit Dcpu16ELFMCAsmInfo(const Target &T, StringRef TT);
  };

} // namespace llvm

#endif
