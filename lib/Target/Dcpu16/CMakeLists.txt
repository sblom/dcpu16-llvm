set(LLVM_TARGET_DEFINITIONS Dcpu16.td)

tablegen(LLVM Dcpu16GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM Dcpu16GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM Dcpu16GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM Dcpu16GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM Dcpu16GenCallingConv.inc -gen-callingconv)
tablegen(LLVM Dcpu16GenSubtargetInfo.inc -gen-subtarget)
add_public_tablegen_target(Dcpu16CommonTableGen)

add_llvm_target(Dcpu16CodeGen
  Dcpu16TargetMachine.cpp
  )

add_subdirectory(TargetInfo)
add_subdirectory(InstPrinter)
add_subdirectory(MCTargetDesc)
