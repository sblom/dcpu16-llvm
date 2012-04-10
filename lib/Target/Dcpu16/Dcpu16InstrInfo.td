include "Dcpu16InstrFormats.td"

//let Constraints = "$arg1 = $dst" in
  def ADDrr : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs :$arg1, ReadableRegs:$arg2),
                    "ADD $dst, $arg1, $arg2",
                    [(set WritableRegs:$dst, (add ReadableRegs:$arg1, ReadableRegs:$arg2))]>;
