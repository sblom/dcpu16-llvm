//===-- Dcpu16.td - Describe the Dcpu16 Target Machine -------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// DCPU16 Subtarget features.
//
 
def FeatureV9
  : SubtargetFeature<"v9", "IsV9", "true",
                     "Enable DCPU16-V9 instructions">;
def FeatureV8Deprecated
  : SubtargetFeature<"deprecated-v8", "V8DeprecatedInsts", "true",
                     "Enable deprecated V8 instructions in V9 mode">;
def FeatureVIS
  : SubtargetFeature<"vis", "IsVIS", "true",
                     "Enable UltraDCPU16 Visual Instruction Set extensions">;

//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "Dcpu16RegisterInfo.td"
include "Dcpu16CallingConv.td"
include "Dcpu16InstrInfo.td"

def Dcpu16InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// DCPU16 processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;
def : Proc<"v8",              []>;
def : Proc<"superdcpu16",      []>;
def : Proc<"dcpu16lite",       []>;
def : Proc<"f934",            []>;
def : Proc<"hyperdcpu16",      []>;
def : Proc<"dcpu16lite86x",    []>;
def : Proc<"dcpu16let",        []>;
def : Proc<"tsc701",          []>;
def : Proc<"v9",              [FeatureV9]>;
def : Proc<"ultradcpu16",      [FeatureV9, FeatureV8Deprecated]>;
def : Proc<"ultradcpu163",     [FeatureV9, FeatureV8Deprecated]>;
def : Proc<"ultradcpu163-vis", [FeatureV9, FeatureV8Deprecated, FeatureVIS]>;


//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def Dcpu16 : Target {
  // Pull in Instruction Info:
  let InstructionSet = Dcpu16InstrInfo;
}
