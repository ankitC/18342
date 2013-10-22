#ifndef _KERNEL_H
#define _KERNEL_H

#define USR_STACK_BASE 0xa3000000
#define USR_MAIN_ADDR 0xa2000000
#define SWI_VECTOR_ADDR 0x08
#define LDR_PC_PC_minus_4 0xe51ff004 // opcode for ldr pc, [pc, #-4]

//void init(int argc, char** argv);
//void dispatcher();

#endif
