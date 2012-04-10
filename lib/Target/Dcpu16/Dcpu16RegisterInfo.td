// Registers

// General-purpose registers
def A : Register<"A">;
def B : Register<"B">;
def C : Register<"C">;
def X : Register<"X">;
def Y : Register<"Y">;
def Z : Register<"Z">;
def I : Register<"I">;
def J : Register<"J">;

// Special-purpose registers
def PC : Register<"PC">, DwarfRegNum<[-1]>;
def SP : Register<"SP">, DwarfRegNum<[-1]>;
def O : Register<"O">, DwarfRegNum<[-1]>;

// Register classes.
//
// FIXME: the register order should be defined in terms of the preferred
// allocation order...
//
def WritableRegs : RegisterClass<"DCPU", [i16], 16, [A, B, C, X, Y, Z, I, J]>;
def ReadableRegs : RegisterClass<"DCPU", [i16], 16, [A, B, C, X, Y, Z, I, J, PC, SP, O]>;
