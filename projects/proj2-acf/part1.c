#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"

void print_rtype(char *, Instruction);
void print_itype_except_load(char *, Instruction, int);
void print_load(char *, Instruction);
void print_store(char *, Instruction);
void print_branch(char *, Instruction);
void print_utype(char*, Instruction);
void print_jal(Instruction);
void print_ecall(Instruction);
void write_rtype(Instruction);
void write_itype_except_load(Instruction);
void write_load(Instruction);
void write_store(Instruction);
void write_branch(Instruction);


void decode_instruction(uint32_t instruction_bits) {
    Instruction instruction = parse_instruction(instruction_bits); // Look in utils.c
    switch(instruction.opcode) {
        case 0x33:  //r-type
            /* YOUR CODE HERE */
            write_rtype(instruction);
            break;
        case 0x13:  //i-type
            /* YOUR CODE HERE */
            write_itype_except_load(instruction);
            break;
        case 0x3:   //load
            /* YOUR CODE HERE */
            write_load(instruction);
            break;
        case 0x67:  //jalr
            /* YOUR CODE HERE */
            print_itype_except_load("jalr", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x23:    //s-type
            /* YOUR CODE HERE */
            write_store(instruction);
            break;
        case 0x63:    //sb-type
            /* YOUR CODE HERE */
            write_branch(instruction);
            break;
        case 0x37:    //lui
            /* YOUR CODE HERE */
            print_utype("lui", instruction);
            break;
        case 0x17:    //auipc
            /* YOUR CODE HERE */
            print_utype("auipc", instruction);
            break;
        case 0x6F:    //jal
            /* YOUR CODE HERE */
            print_jal(instruction);
            break;
        case 0x73:    //ecall
            /* YOUR CODE HERE */
            print_ecall(instruction);
            break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_rtype(Instruction instruction) {
    /* HINT: Hmmm, it's seems that there's way more R-Type instructions that funct3 possibilities... */
    switch (instruction.rtype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("add", instruction);
                      break;
                  case 0x01:
                      print_rtype("mul", instruction);
                      break;
                  case 0x20:
                      print_rtype("sub", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x1:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("sll", instruction);
                      break;
                  case 0x01:
                      print_rtype("mulh", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x2:
            /* YOUR CODE HERE */
            print_rtype("slt", instruction);
            break;
        case 0x3:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("sltu", instruction);
                      break;
                  case 0x01:
                      print_rtype("mulhu", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x4:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("xor", instruction);
                      break;
                  case 0x01:
                      print_rtype("div", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x5:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("srl", instruction);
                      break;
                  case 0x01:
                      print_rtype("divu", instruction);
                      break;
                  case 0x20:
                      print_rtype("sra", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("or", instruction);
                      break;
                  case 0x01:
                      print_rtype("rem", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x7:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:
                      print_rtype("and", instruction);
                      break;
                  case 0x01:
                      print_rtype("remu", instruction);
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_itype_except_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            print_itype_except_load("addi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x1:
            /* YOUR CODE HERE */
            //can remove sign_extend_number, and it's ok to keep it here as the imm always starts with 0
            print_itype_except_load("slli", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x2:
            /* YOUR CODE HERE */
            print_itype_except_load("slti", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x3:
            /* YOUR CODE HERE */
            print_itype_except_load("sltiu", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x4:
            /* YOUR CODE HERE */
            print_itype_except_load("xori", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x5:
            /* HINT: What makes the immediate here special? */
            /* YOUR CODE HERE */
            //can remove sign_extend_number, and it's ok to keep it here as the imm always starts with 0
            switch (instruction.itype.imm & 0x400) {
                case 0x000:
                    print_itype_except_load("srli", instruction, sign_extend_number(instruction.itype.imm, 12));
                    break;
                case 0x400:
                    print_itype_except_load("srai", instruction, sign_extend_number((instruction.itype.imm & 0x01f), 12));
                    break;
                default:
                    handle_invalid_instruction(instruction);
                    break;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            print_itype_except_load("ori", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        case 0x7:
            /* YOUR CODE HERE */
            print_itype_except_load("andi", instruction, sign_extend_number(instruction.itype.imm, 12));
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_load(Instruction instruction) {
    switch (instruction.itype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            print_load("lb", instruction);
            break;
        case 0x1:
            /* YOUR CODE HERE */
            print_load("lh", instruction);
            break;
        case 0x2:
            /* YOUR CODE HERE */
            print_load("lw", instruction);
            break;
        case 0x4:
            /* YOUR CODE HERE */
            print_load("lbu", instruction);
            break;
        case 0x5:
            /* YOUR CODE HERE */
            print_load("lhu", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_store(Instruction instruction) {
    switch (instruction.stype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            print_store("sb", instruction);
            break;
        case 0x1:
            /* YOUR CODE HERE */
            print_store("sh", instruction);
            break;
        case 0x2:
            /* YOUR CODE HERE */
            print_store("sw", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void write_branch(Instruction instruction) {
    switch (instruction.sbtype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            print_branch("beq", instruction);
            break;
        case 0x1:
            /* YOUR CODE HERE */
            print_branch("bne", instruction);
            break;
        case 0x4:
            /* YOUR CODE HERE */
            print_branch("blt", instruction);
            break;
        case 0x5:
            /* YOUR CODE HERE */
            print_branch("bge", instruction);
            break;
        case 0x6:
            /* YOUR CODE HERE */
            print_branch("bltu", instruction);
            break;
        case 0x7:
            /* YOUR CODE HERE */
            print_branch("bgeu", instruction);
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

/* utils.c and utils.h might be useful here... */

void print_utype(char* name, Instruction instruction) {
    /* YOUR CODE HERE */
    // imm is already with sign. Do not need to sign_extend_number.
    printf(UTYPE_FORMAT, name, instruction.utype.rd, instruction.utype.imm);
}

void print_jal(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(JAL_FORMAT, instruction.ujtype.rd, get_jump_offset(instruction));
}

void print_ecall(Instruction instruction) {
    /* YOUR CODE HERE */
    printf(ECALL_FORMAT);
}

void print_rtype(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(RTYPE_FORMAT, name, instruction.rtype.rd, instruction.rtype.rs1, instruction.rtype.rs2);
}

void print_itype_except_load(char *name, Instruction instruction, int imm) {
    /* YOUR CODE HERE */
    //imm has already been sign extended if needed.
    printf(ITYPE_FORMAT, name, instruction.itype.rd, instruction.itype.rs1, imm);
}

void print_load(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    //imm: sign_extend_number or not?
    printf(MEM_FORMAT, name, instruction.itype.rd, sign_extend_number(instruction.itype.imm, 12), instruction.itype.rs1);
}

void print_store(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    //The sequence of rs1 and rs2 is different.
    printf(MEM_FORMAT, name, instruction.stype.rs2, get_store_offset(instruction), instruction.stype.rs1);
}

void print_branch(char *name, Instruction instruction) {
    /* YOUR CODE HERE */
    printf(BRANCH_FORMAT, name, instruction.sbtype.rs1, instruction.sbtype.rs2, get_branch_offset(instruction));
}
