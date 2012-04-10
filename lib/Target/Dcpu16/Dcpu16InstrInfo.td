include "Dcpu16InstrFormats.td"

multiclass Math_Instr<string OpcStr, SDNode OpNode> {
  let Constraints = "$arg1 = $dst" in {
    // register
    def rr : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1, ReadableRegs:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set WritableRegs:$dst, (OpNode ReadableRegs:$arg1, ReadableRegs:$arg2))]>;

    // constant
    def rc : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1, i16imm:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set WritableRegs:$dst, (OpNode ReadableRegs:$arg1, (i16 imm:$arg2)))]>;

    // load from register location
    def rmr : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1, ReadableRegs:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set WritableRegs:$dst, (OpNode ReadableRegs:$arg1, (load ReadableRegs:$arg2)))]>;

    // load from constant location
    def rmc : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1, i16imm:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set WritableRegs:$dst, (OpNode ReadableRegs:$arg1, (load (i16 imm:$arg2))))]>;
  }
}

defm ADD : Math_Instr<"ADD", add>;
defm SUB : Math_Instr<"SUB", sub>;

def SETrr : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1),
                  "SET $dst, $arg1",
                  [(set WritableRegs:$dst, ReadableRegs:$arg1)]>;

def SETrc : BasicInstruction<(outs WritableRegs:$dst), (ins i16imm:$arg1),
                  "SET $dst, $arg1",
                  [(set WritableRegs:$dst, (i16 imm:$arg1))]>;

def SETrmr : BasicInstruction<(outs WritableRegs:$dst), (ins ReadableRegs:$arg1),
                  "SET $dst, [$arg1]",
                  [(set WritableRegs:$dst, (load ReadableRegs:$arg1))]>;

def SETrmc : BasicInstruction<(outs WritableRegs:$dst), (ins i16imm:$arg1),
                  "SET $dst, [$arg1]",
                  [(set WritableRegs:$dst, (load (i16 imm:$arg1)))]>;
