#include "Dcpu16TargetMachine.h"
#include "llvm/Intrinsics.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

namespace {
class Dcpu16DAGToDAGISel : public SelectionDAGISel {

  virtual const char *getPassName() const {
    return "DCPU16 DAG->DAG Pattern Instruction Selection";
  }

#include "Dcpu16GenDAGISel.inc"
};
}
