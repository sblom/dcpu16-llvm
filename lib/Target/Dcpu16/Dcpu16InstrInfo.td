include "Dcpu16InstrFormats.td"

// Addressing modes.
def ADDRri : ComplexPattern<i32, 2, "SelectADDRri", [frameindex], []>;

def MEMri : Operand<i32> {
  let PrintMethod = "printMemOperand";
  let MIOperandInfo = (ops ReadableRegs, i32imm);
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
def SDT_SPCallSeqStart : SDCallSeqStart<[ SDTCisVT<0, i32> ]>;
def callseq_start : SDNode<"ISD::CALLSEQ_START", SDT_SPCallSeqStart,
                           [SDNPHasChain, SDNPOutGlue]>;
def SDT_SPCallSeqEnd   : SDCallSeqEnd<[ SDTCisVT<0, i32>,
                                        SDTCisVT<1, i32> ]>;
def callseq_end   : SDNode<"ISD::CALLSEQ_END",   SDT_SPCallSeqEnd,
                           [SDNPHasChain, SDNPOptInGlue, SDNPOutGlue]>;

class Pseudo<dag outs, dag ins, string asmstr, list<dag> pattern>
   : BasicInstruction<outs, ins, asmstr, pattern>;

multiclass Math_Instr<string OpcStr, SDNode OpNode> {
  let Constraints = "$arg1 = $dst" in {
    // register
    def rr : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, ReadableRegs:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, ReadableRegs:$arg2))]>;

    // constant
    def rc : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, i32imm:$arg2),
                      !strconcat(OpcStr, " $dst, $arg2"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, imm:$arg2))]>;

    // load from frame location
    def rm : BasicInstruction<(outs GeneralRegs:$dst), (ins GeneralRegs:$arg1, MEMri:$arg2),
                      !strconcat(OpcStr, " $dst, [$arg2]"),
                      [(set GeneralRegs:$dst, (OpNode GeneralRegs:$arg1, (load ADDRri:$arg2)))]>;

    // TODO
  }
}

multiclass Cond_Branch_Instr<string OpcStr, CondCode CCNode> {
  let isBranch = 1, isTerminator = 1, Defs = [SP] in {
    // register - register
    def rr : BasicInstruction<(outs ), (ins ReadableRegs:$arg1, ReadableRegs:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, $arg2\n\tSET %pc $b"),
                          [(brcond (setcc ReadableRegs:$arg1, ReadableRegs:$arg2, CCNode), bb:$b)]>;

    // register - constant
    def rc : BasicInstruction<(outs ), (ins ReadableRegs:$arg1, i32imm:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, $arg2\n\tSET %pc $b"),
                          [(brcond (setcc ReadableRegs:$arg1, imm:$arg2, CCNode), bb:$b)]>;

    // register - frame location
    def rm : BasicInstruction<(outs ), (ins ReadableRegs:$arg1, MEMri:$arg2, brtarget:$b),
                          !strconcat(OpcStr, " $arg1, [$arg2]\n\tSET %pc $b"),
                          [(brcond (setcc ReadableRegs:$arg1, (load ADDRri:$arg2), CCNode), bb:$b)]>;
  }
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

def SETrm : BasicInstruction<(outs GeneralRegs:$dst), (ins MEMri:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load ADDRri:$arg1))]>;

def SETrg : BasicInstruction<(outs GeneralRegs:$dst), (ins i32imm:$arg1),
                  "SET $dst, [$arg1]",
                  [(set GeneralRegs:$dst, (load tglobaladdr:$arg1))]>;

def SETmr : BasicInstruction<(outs ), (ins MEMri:$dst, GeneralRegs:$arg1),
                  "SET [$dst], $arg1",
                  [(store GeneralRegs:$arg1, ADDRri:$dst)]>;

def SETmc : BasicInstruction<(outs ), (ins MEMri:$dst, i32imm:$arg1),
                  "SET [$dst], $arg1",
                  [(store imm:$arg1, ADDRri:$dst)]>;

def SETgr : BasicInstruction<(outs ), (ins i32imm:$dst, GeneralRegs:$arg1),
                  "SET [$dst], $arg1",
                  [(store GeneralRegs:$arg1, tglobaladdr:$dst)]>;

def SETgc : BasicInstruction<(outs ), (ins i32imm:$dst, i32imm:$arg1),
                  "SET [$dst], $arg1",
                  [(store imm:$arg1, tglobaladdr:$dst)]>;

def BR : BasicInstruction<(outs), (ins brtarget:$dst),
                          "SET %pc $dst",
                          [(br bb:$dst)]> {
  let isBarrier = 1;
  let isBranch = 1;
  let isTerminator = 1;
  let Defs = [SP];
}

def RET: BasicInstruction<(outs), (ins),
              "SET %pc POP", [(retflag)]> {
  let isBarrier = 1;
  let isReturn = 1;
  let isTerminator = 1;
  let Uses = [SP];
}

def JSR: BasicInstruction<(outs), (ins calltarget:$dst, variable_ops),
              "JSR $dst", []> {
  let isCall = 1;
  let Uses = [SP];
}

def : Pat<(call tglobaladdr:$dst),
          (JSR tglobaladdr:$dst)>;
def : Pat<(call texternalsym:$dst),
          (JSR texternalsym:$dst)>;

let Defs = [SP], Uses = [SP] in {
  def ADJCALLSTACKDOWN : Pseudo<(outs), (ins i32imm:$amt),
                                "!ADJCALLSTACKDOWN $amt",
                                [(callseq_start timm:$amt)]>;
  def ADJCALLSTACKUP : Pseudo<(outs), (ins i32imm:$amt1, i32imm:$amt2),
                              "!ADJCALLSTACKUP $amt1",
                              [(callseq_end timm:$amt1, timm:$amt2)]>;
}
