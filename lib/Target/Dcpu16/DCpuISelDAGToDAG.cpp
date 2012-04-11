#include "Dcpu16TargetMachine.h"
#include "llvm/CodeGen/SelectionDAGISel.h"

namespace {
class Dcpu16DAGToDAGISel : public SelectionDAGISel {

  virtual const char *getPassName() const {
    return "DCPU16 DAG->DAG Pattern Instruction Selection";
  }

#include "Dcpu16GenDAGISel.inc"
};
}
