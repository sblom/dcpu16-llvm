add_llvm_library(LLVMDcpu16Desc
  Dcpu16MCTargetDesc.cpp
  Dcpu16AsmInfo.cpp
  )

add_dependencies(LLVMDcpu16Desc Dcpu16CommonTableGen)
