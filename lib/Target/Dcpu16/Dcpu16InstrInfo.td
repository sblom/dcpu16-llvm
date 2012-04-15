include "Dcpu16InstrFormats.td"

// Addressing modes.
def ADDRrr : ComplexPattern<i32, 2, "SelectADDRrr", [], []>;
def ADDRri : ComplexPattern<i32, 2, "SelectADDRri", [frameindex], []>;

def MEMrr : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GeneralRegs, GeneralRegs);
}
def MEMri : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops GeneralRegs, i32imm);
}

// Whatever this stuff is
def SDT_SPRet     : SDTypeProfile<0, 1, [SDTCisVT<0, i32>]>;
def retflag       : SDNode<"DCPU16ISD::RET_FLAG", SDT_SPRet,
                           [SDNPHasChain, SDNPOptInGlue]>;

def brtarget : Operand<OtherVT>;

multiclass Math_Instr<string OpcStr, SDNode OpNode> {
  let Constraints = "$arg1 = $dst" in {
    // register
    def rr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, GeneralRegs:$arg2),
                      !strconcat(OpcStr, "1 $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, GeneralRegs:$arg2))]>;

    // constant
    def rc : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                      !strconcat(OpcStr, "2 $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, imm:$arg2))]>;

    // load from register location
    def rmr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, GeneralRegs:$arg2),
                      !strconcat(OpcStr, "3 $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load GeneralRegs:$arg2)))]>;

    // load from constant location
    def rmc : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                      !strconcat(OpcStr, "4 $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load (i32 imm:$arg2))))]>;

    // load from frame location
    def rmf : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, MEMri:$arg2),
                      !strconcat(OpcStr, "5 $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load ADDRri:$arg2)))]>;

    // TODO
  }

}

defm ADD : Math_Instr<"ADD", add>;
defm SUB : Math_Instr<"SUB", sub>;
defm MUL : Math_Instr<"MUL", mul>;

def SETrr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1),
                  "SET $dst, $arg1",
                  [(set GeneralRegs:$dst, GeneralRegs:$arg1)]>;

def SETrc : BasicInstruction<(outs GeneralRegs:$dst), (ins i32imm:$arg1),
                  "SET $dst, $arg1",
                  [(set GeneralRegs:$dst, (i32 imm:$arg1))]>;

def SETrmr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load GeneralRegs:$arg1))]>;

def SETrmc : BasicInstruction<(outs GeneralRegs:$dst), (ins i32imm:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load (i32 imm:$arg1)))]>;

def SETrma : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                  "SET $dst, [$arg1+$arg2]",
                  []>;

def SETrmf : BasicInstruction<(outs GeneralRegs:$dst), (ins MEMri:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load ADDRri:$arg1))]>;

/*def SETmcr : BasicInstruction<(outs ), (ins MEMrr:$dst, GeneralRegs:$arg1),
                  "SET [$dst], $arg1",
                  [(store GeneralRegs:$arg1, ADDRrr:$dst)]>;*/

def SETmfr : BasicInstruction<(outs ), (ins MEMri:$dst, GeneralRegs:$arg1),
                  "SET [$dst], $arg1",
                  [(store GeneralRegs:$arg1, ADDRri:$dst)]>;

def SETmar : BasicInstruction<(outs ), (ins GeneralRegs:$dst1, i32imm:$dst2, GeneralRegs:$arg1),
                  "SET [$dst1+$dst2], $arg1",
                  []>;

let isBarrier = 1, isBranch = 1, isTerminator = 1 in {
  def BR : BasicInstruction<(outs), (ins brtarget:$dst),
                            "SET %pc $dst",
                            [(br bb:$dst)]>;

  def BEQrr : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, GeneralRegs:$arg2, brtarget:$b),
                        "IFE $arg1, $arg2\n\tSET %pc $b",
                        [(brcond (seteq GeneralRegs:$arg1, GeneralRegs:$arg2), bb:$b)]>;

  def BEQrc : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, i32imm:$arg2, brtarget:$b),
                        "IFE $arg1, $arg2\n\tSET %pc $b",
                        [(brcond (seteq GeneralRegs:$arg1, imm:$arg2), bb:$b)]>;
}

def RET: BasicInstruction<(outs), (ins i32imm:$val),
              "SET %pc [%sp+$val]", [(retflag (i32 imm:$val))]> {
  let isBarrier = 1;
  let isReturn = 1;
  let isTerminator = 1;
}
