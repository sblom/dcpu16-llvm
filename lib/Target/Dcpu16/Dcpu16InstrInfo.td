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
def SDT_SPRet     : SDTypeProfile<0, 0, []>;
def retflag       : SDNode<"DCPU16ISD::RET_FLAG", SDT_SPRet,
                           [SDNPHasChain, SDNPOptInGlue]>;

def brtarget : Operand<OtherVT>;
def calltarget : Operand<i32>;
def SDT_SPCall    : SDTypeProfile<0, -1, [SDTCisVT<0, i32>]>;
def call          : SDNode<"DCPU16ISD::CALL", SDT_SPCall,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue,
                            SDNPVariadic]>;

multiclass Math_Instr<string OpcStr, SDNode OpNode> {
  let Constraints = "$arg1 = $dst" in {
    // register
    def rr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, GeneralRegs:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, GeneralRegs:$arg2))]>;

    // constant
    def rc : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, imm:$arg2))]>;

    // load from register location
    def rmr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, GeneralRegs:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load GeneralRegs:$arg2)))]>;

    // load from constant location
    def rmc : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load imm:$arg2)))]>;

    // load from frame location
    def rmf : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, MEMri:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load ADDRri:$arg2)))]>;

    // TODO
  }
}

multiclass Cond_Branch_Instr<string OpcStr, CondCode CCNode> {
  let isBranch = 1, isTerminator = 1 in {
    // register - register
    def rr : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, GeneralRegs:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, $arg2\n\tSET %pc $b"),
                          [(brcond (setcc GeneralRegs:$arg1, GeneralRegs:$arg2, CCNode), bb:$b)]>;

    // register - constant
    def rc : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, i32imm:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, $arg2\n\tSET %pc $b"),
                          [(brcond (setcc GeneralRegs:$arg1, imm:$arg2, CCNode), bb:$b)]>;

    // register - memory location
    def rmc : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, i32imm:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, [$arg2]\n\tSET %pc $b"),
                          [(brcond (setcc GeneralRegs:$arg1, (load imm:$arg2), CCNode), bb:$b)]>;

    // register - frame location
    def rmf : BasicInstruction<(outs ), (ins GeneralRegs:$arg1, MEMri:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, [$arg2]\n\tSET %pc $b"),
                          [(brcond (setcc GeneralRegs:$arg1, (load ADDRri:$arg2), CCNode), bb:$b)]>;

    // frame location - constant
    def mfc : BasicInstruction<(outs ), (ins MEMri:$arg1, i32imm:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " [$arg1], $arg2\n\tSET %pc $b"),
                          [(brcond (setcc (load ADDRri:$arg1), imm:$arg2, CCNode), bb:$b)]>;
  }

  /*def test : BasicInstruction<(outs $dst), (ins MEMri:$arg1, i32imm:$arg2, brtarget:$b),
                        !strconcat(OpcStr, " [$arg1], $arg2\n\tSET %pc $b"),
                        [(set GeneralRegs:$dst (select (setcc (load ADDRri:$arg1), imm:$arg2, CCNode), bb:$b)]>;*/

}

defm ADD : Math_Instr<"ADD", add>;
defm SUB : Math_Instr<"SUB", sub>;
defm MUL : Math_Instr<"MUL", mul>;
defm DIV : Math_Instr<"DIV", udiv>;
defm AND : Math_Instr<"AND", and>;
defm BOR : Math_Instr<"BOR", or>;
defm XOR : Math_Instr<"XOR", xor>;

defm BEQ : Cond_Branch_Instr<"IFE", SETEQ>;
defm BGT : Cond_Branch_Instr<"IFG", SETGT>;
defm BNE : Cond_Branch_Instr<"IFN", SETNE>;

def SETrr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1),
                  "SET $dst, $arg1",
                  []>;

def SETrc : BasicInstruction<(outs GeneralRegs:$dst), (ins i32imm:$arg1),
                  "SET $dst, $arg1",
                  [(set GeneralRegs:$dst, imm:$arg1)]>;

def SETrmr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load GeneralRegs:$arg1))]>;

def SETrmc : BasicInstruction<(outs GeneralRegs:$dst), (ins i32imm:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load imm:$arg1))]>;

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

}

def RET: BasicInstruction<(outs), (ins),
              "SET %pc POP", [(retflag)]> {
  let isBarrier = 1;
  let isReturn = 1;
  let isTerminator = 1;
}

def JSR: BasicInstruction<(outs), (ins calltarget:$dst, variable_ops),
              "JSR $dst", []> {
  let isCall = 1;
}

def : Pat<(call tglobaladdr:$dst),
          (JSR tglobaladdr:$dst)>;
