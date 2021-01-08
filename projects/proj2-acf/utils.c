#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

/* Sign extends the given field to a 32-bit integer where field is
 * interpreted an n-bit integer. Look in test_utils.c for examples. */
int sign_extend_number( unsigned int field, unsigned int n) {
    /* YOUR CODE HERE */
    //consider n > 32 or not? Not.
    Word mask = 0x0001 << (n - 1);
    int digit = (field & mask) >> (n - 1);
    Word generator = 0x0001;
    int i;
    if (!digit) {
        for (i = 0; i < (n - 1); i++) {
            generator = (generator << 1) + 1;
        }
        field = field & generator;
    } else {
        for (i = 0; i < (32 - n - 1); i++) {
            generator = (generator << 1) + 1;
        }
        generator = generator << n;
        field = field | generator;
    }
    return field;
}

/* Unpacks the 32-bit machine code instruction given into the correct
 * type within the instruction struct. Look at types.h */
Instruction parse_instruction(uint32_t instruction_bits) {
    Instruction instruction;
    /* YOUR CODE HERE */
    instruction.opcode = instruction_bits & 0x7f;
    switch(instruction.opcode) {
        /* I-type */
        case 0x03:
        case 0x13:
        case 0x67:
        case 0x73:
            instruction.itype.rd = (instruction_bits & 0x00000f80) >> 7;
            instruction.itype.funct3 = (instruction_bits & 0x00007000) >> 12;
            instruction.itype.rs1 = (instruction_bits & 0x000f8000) >> 15;
            instruction.itype.imm = (instruction_bits & 0xfff00000) >> 20;
            break;
        /* U-type */
        case 0x17:
        case 0x37:
            instruction.utype.rd = (instruction_bits & 0x00000f80) >> 7;
            instruction.utype.imm = (instruction_bits & 0xfffff000) >> 12;
            break;
        /* S-type */
        case 0x23:
            instruction.stype.imm5= (instruction_bits & 0x00000f80) >> 7;
            instruction.stype.funct3 = (instruction_bits & 0x00007000) >> 12;
            instruction.stype.rs1 = (instruction_bits & 0x000f8000) >> 15;
            instruction.stype.rs2 = (instruction_bits & 0x01f00000) >> 20;
            instruction.stype.imm7 = (instruction_bits & 0xfe000000) >> 25;
            break;
        /* R-type */
        case 0x33:
            instruction.rtype.rd = (instruction_bits & 0x00000f80) >> 7;
            instruction.rtype.funct3 = (instruction_bits & 0x00007000) >> 12;
            instruction.rtype.rs1 = (instruction_bits & 0x000f8000) >> 15;
            instruction.rtype.rs2 = (instruction_bits & 0x01f00000) >> 20;
            instruction.rtype.funct7 = (instruction_bits & 0xfe000000) >> 25;
            break;
        /* SB-type */
        case 0x63:
            instruction.sbtype.imm5= (instruction_bits & 0x00000f80) >> 7;
            instruction.sbtype.funct3 = (instruction_bits & 0x00007000) >> 12;
            instruction.sbtype.rs1 = (instruction_bits & 0x000f8000) >> 15;
            instruction.sbtype.rs2 = (instruction_bits & 0x01f00000) >> 20;
            instruction.sbtype.imm7 = (instruction_bits & 0xfe000000) >> 25;
            break;
        /* UJ-type */
        case 0x6f:
            instruction.ujtype.rd = (instruction_bits & 0x00000f80) >> 7;
            instruction.ujtype.imm = (instruction_bits & 0xfffff000) >> 12;
            break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            break;
    }
    return instruction;
}

/* Return the number of bytes (from the current PC) to the branch label using the given
 * branch instruction */
int get_branch_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    Word imm_12and10to5 = instruction.sbtype.imm7;
    Word imm_4to1and11 = instruction.sbtype.imm5;
    Word imm_12 = (imm_12and10to5 & 0x00000040) << 6;   // (>> 6) << 12 == <<6;
    Word imm_10to5 = (imm_12and10to5 & 0x0000003f) << 5;
    Word imm_4to1 = imm_4to1and11 & 0x0000001e;
    Word imm_11 = (imm_4to1and11 & 0x00000001) << 11;
    return sign_extend_number((imm_12 | imm_11 | imm_10to5 | imm_4to1), 13);
}

/* Returns the number of bytes (from the current PC) to the jump label using the given
 * jump instruction */
int get_jump_offset(Instruction instruction) {  //jal
    /* YOUR CODE HERE */
    Word imm = instruction.ujtype.imm;
    Word imm_20 = (imm & 0x00080000) << 1;
    Word imm_19to12 = (imm & 0x000000ff) << 12;
    Word imm_11 = (imm & 0x00000100) << 3;
    Word imm_10to1 = (imm & 0x0007fe00) >> 8;   // (>> 6) << 12 == <<6;
    return sign_extend_number((imm_20 | imm_19to12 | imm_11 | imm_10to1), 21);
}

/* Returns the byte offset (from the address in rs2) for storing info using the given
 * store instruction */
int get_store_offset(Instruction instruction) {
    /* YOUR CODE HERE */
    Word imm_11to5 = (instruction.stype.imm7) << 5;
    Word imm_4to0 = instruction.stype.imm5;
    return sign_extend_number((imm_11to5 | imm_4to0), 12);
}

void handle_invalid_instruction(Instruction instruction) {
    printf("Invalid Instruction: 0x%08x\n", instruction.bits);
    exit(-1);
}

void handle_invalid_read(Address address) {
    printf("Bad Read. Address: 0x%08x\n", address);
    exit(-1);
}

void handle_invalid_write(Address address) {
    printf("Bad Write. Address: 0x%08x\n", address);
    exit(-1);
}
