include_directories( ${CMAKE_CURRENT_BINARY_DIR}/.. ${CMAKE_CURRENT_SOURCE_DIR}/.. )

add_llvm_library(LLVMDcpu16AsmPrinter
  Dcpu16InstPrinter.cpp
  )

add_dependencies(LLVMDcpu16AsmPrinter Dcpu16CommonTableGen)
