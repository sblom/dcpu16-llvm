// Registers
class Dcpu16Register<string name> : Register <name> {
  let Namespace = "DCPU16";
}

// General-purpose registers
def A : Dcpu16Register<"A">;
def B : Dcpu16Register<"B">;
def C : Dcpu16Register<"C">;
def X : Dcpu16Register<"X">;
def Y : Dcpu16Register<"Y">;
def Z : Dcpu16Register<"Z">;
def I : Dcpu16Register<"I">;
def J : Dcpu16Register<"J">;

// Special-purpose registers
def PC : Dcpu16Register<"PC">, DwarfRegNum<[-1]>;
def SP : Dcpu16Register<"SP">, DwarfRegNum<[-1]>;
def O : Dcpu16Register<"O">, DwarfRegNum<[-1]>;

// Register classes.
def GeneralRegs : RegisterClass<"DCPU16", [i32], 16, (add A, B, C, X, Y, Z, I, J)>;
def ReadableRegs : RegisterClass<"DCPU16", [i32], 16, (add A, B, C, X, Y, Z, I, J, PC, SP, O)>;
