class InstDcpu<dag outs, dag ins, string asmstr, list<dag> pattern> :
Instruction {
  let Namespace = "DCPU16";
  let OutOperandList = outs;
  let InOperandList = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
}

class BasicInstruction<dag outs, dag ins, string asmstr, list<dag> pattern>
  : InstDcpu<outs, ins, asmstr, pattern>;
