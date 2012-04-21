//===-- Dcpu16CallingConv.td - Calling Conventions Dcpu16 ----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This describes the calling conventions for the Dcpu16 architectures.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Return Value Calling Conventions
//===----------------------------------------------------------------------===//

// Dcpu16 C return-value convention.
def RetCC_Dcpu16 : CallingConv<[
  CCIfType<[i32], CCAssignToReg<[X, Y, Z]>>
]>;

// Dcpu16 C Calling convention.
def CC_Dcpu16 : CallingConv<[
  //Custom assign SRet to [sp+64].
  CCIfSRet<CCCustom<"CC_Dcpu16_Assign_SRet">>,
  // i16 arguments get passed in integer registers if there is space.
  CCIfType<[i32], CCAssignToReg<[X, Y, Z]>>,

  // Alternatively, they are assigned to the stack in 4-byte aligned units.
  CCAssignToStack<4, 4>
]>;
