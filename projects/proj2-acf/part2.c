#include <stdio.h> // for stderr
#include <stdlib.h> // for exit()
#include "types.h"
#include "utils.h"
#include "riscv.h"

void execute_rtype(Instruction, Processor *);
void execute_itype_except_load(Instruction, Processor *);
void execute_branch(Instruction, Processor *);
void execute_jal(Instruction, Processor *);
void execute_jalr(Instruction, Processor *);
void execute_load(Instruction, Processor *, Byte *);
void execute_store(Instruction, Processor *, Byte *);
void execute_ecall(Processor *, Byte *);
void execute_lui(Instruction, Processor *);
void execute_auipc(Instruction, Processor *);

void execute_instruction(uint32_t instruction_bits, Processor *processor,Byte *memory) {
    Instruction instruction = parse_instruction(instruction_bits); // Look in utils.c
    switch(instruction.opcode) {
        case 0x33:
            /* YOUR CODE HERE */
            execute_rtype(instruction, processor);
            break;
        case 0x13:
            /* YOUR CODE HERE */
            execute_itype_except_load(instruction, processor);
            break;
        case 0x3:
            /* YOUR CODE HERE */
            execute_load(instruction, processor, memory);
            break;
        case 0x67:
            /* YOUR CODE HERE */
            execute_jalr(instruction, processor);
            break;
        case 0x23:
            /* YOUR CODE HERE */
            execute_store(instruction, processor, memory);
            break;
        case 0x63:
            /* YOUR CODE HERE */
            execute_branch(instruction, processor);
            break;
        case 0x37:
            /* YOUR CODE HERE */
            execute_lui(instruction, processor);
            break;
        case 0x17:
            /* YOUR CODE HERE */
            execute_auipc(instruction, processor);
            break;
        case 0x6F:
            /* YOUR CODE HERE */
            execute_jal(instruction, processor);
            break;
        case 0x73:
            /* YOUR CODE HERE */
            execute_ecall(processor, memory);
            processor->PC = processor->PC + 4;
            break;
        default: // undefined opcode
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_rtype(Instruction instruction, Processor *processor) {
    switch (instruction.rtype.funct3){
        case 0x0:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //add
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] + processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x01:    //mul
                  {
                      ;
                      sWord s1 = processor->R[instruction.rtype.rs1];
                      sWord s2 = processor->R[instruction.rtype.rs2];
                      sWord s3 = s1 * s2;
                      processor->R[instruction.rtype.rd] = s3;
                      processor->PC = processor->PC + 4;
                  }
                      break;
                  case 0x20:    //sub
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] - processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x1:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //sll
                      if (processor->R[instruction.rtype.rs2] > 31) {     //R[rs2] is unsigned, always >= 0
                          handle_invalid_instruction(instruction);
                      } else {
                          processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] << processor->R[instruction.rtype.rs2];
                          processor->PC = processor->PC + 4;
                      }
                      break;
                  case 0x01:    //mulh
                  {
                      ;
                      sWord s1 = processor->R[instruction.rtype.rs1];
                      sWord s2 = processor->R[instruction.rtype.rs2];
                      sDouble s3 = s1 * s2;
                      s3 = s3 >> 32;
                      processor->R[instruction.rtype.rd] = s3;
                      processor->PC = processor->PC + 4;
                  }
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x2:   //slt
            /* YOUR CODE HERE */
        {
            ;
            Register r1 = processor->R[instruction.rtype.rs1];
            Register r2 = processor->R[instruction.rtype.rs2];
            Register r1_sign = (r1 & 0x80000000) >> 31;
            Register r2_sign = (r2 & 0x80000000) >> 31;
            if (r1_sign == 0 && r2_sign == 0) {
                processor->R[instruction.rtype.rd] = (r1 < r2) ? 1 : 0;
            } else if(r1_sign == 0 && r2_sign == 1) {
                processor->R[instruction.rtype.rd] = 0;
            } else if (r1_sign == 1 && r2_sign == 0) {
                processor->R[instruction.rtype.rd] = 1;
            } else {
                processor->R[instruction.rtype.rd] = (r1 < r2) ? 0 : 1;
            }
            processor->PC = processor->PC + 4;
        }
            break;
        case 0x3:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //sltu
                      processor->R[instruction.rtype.rd] = (processor->R[instruction.rtype.rs1] < processor->R[instruction.rtype.rs2]) ? 1 : 0;
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x01:    //mulhu
                  {
                      ;
                      Double ret = processor->R[instruction.rtype.rs1] * processor->R[instruction.rtype.rs2];
                      processor->R[instruction.rtype.rd] = ret >> 32;
                      processor->PC = processor->PC + 4;
                  }
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x4:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //xor
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] ^ processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x01:    //div
                  {
                      ;
                      sWord s1 = processor->R[instruction.rtype.rs1];
                      sWord s2 = processor->R[instruction.rtype.rs2];
                      sWord s3 = s1 / s2;
                      processor->R[instruction.rtype.rd] = s3;
                      processor->PC = processor->PC + 4;
                  }
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x5:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //srl   logic: fill the MSB with 0
                      if (processor->R[instruction.rtype.rs2] > 31) {     //R[rs2] is unsigned, always >= 0
                          handle_invalid_instruction(instruction);
                      } else {
                          processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] >> processor->R[instruction.rtype.rs2];
                          processor->PC = processor->PC + 4;
                      }
                      break;
                  case 0x01:   //divu
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] / processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x20:    //sra   arithmetic: fill the MSB with sign
                  {
                      ;
                      if (processor->R[instruction.rtype.rs2] > 31) {     //R[rs2] is unsigned, always >= 0
                          handle_invalid_instruction(instruction);
                      } else {
                          Register signBit = (processor->R[instruction.rtype.rs1]) & 0x80000000;   //get the sign
                          Register distance_to_shift = instruction.rtype.rs2 & 0x01f;
                          processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] >> distance_to_shift;
                          Register mask;
                          if (signBit == 0x80000000) {
                              mask = 0xffffffff << (32 - distance_to_shift);
                              processor->R[instruction.rtype.rd] |= mask;
                          }
                          processor->PC = processor->PC + 4;
                      }
                  }
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x6:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //or
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] | processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x01:    //rem
                  {
                      ;
                      sWord s1 = processor->R[instruction.rtype.rs1];
                      sWord s2 = processor->R[instruction.rtype.rs2];
                      sWord s3 = s1 % s2;
                      processor->R[instruction.rtype.rd] = s3;
                      processor->PC = processor->PC + 4;
                  }
                      break;
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x7:
            /* YOUR CODE HERE */
            switch (instruction.rtype.funct7) {
                  case 0x00:    //and
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] & processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x01:    //remu
                      processor->R[instruction.rtype.rd] = processor->R[instruction.rtype.rs1] % processor->R[instruction.rtype.rs2];
                      processor->PC = processor->PC + 4;
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

void execute_itype_except_load(Instruction instruction, Processor *processor) {
    switch (instruction.itype.funct3) {
        case 0x0:   //addi
            /* YOUR CODE HERE */
            //When operated with unsigned, signed converts to unsigned automatically
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] + sign_extend_number(instruction.itype.imm, 12);
            processor->PC = processor->PC + 4;
            break;
        case 0x1:   //slli    //will always ensure imm < 32  //bits to shift is always positive
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] << instruction.itype.imm;
            processor->PC = processor->PC + 4;
            break;
        case 0x2:   //slti
            /* YOUR CODE HERE */
            //maybe encapsulated in a function compare_signed()
        {
            ;
            Register r1 = processor->R[instruction.itype.rs1];
            Register r2 = sign_extend_number(instruction.itype.imm, 12);  //implicitly cast to unsigned
            Register r1_sign = (r1 & 0x80000000) >> 31;
            Register r2_sign = (r2 & 0x80000000) >> 31;
            if (r1_sign == 0 && r2_sign == 0) {
                processor->R[instruction.itype.rd] = (r1 < r2) ? 1 : 0;
            } else if(r1_sign == 0 && r2_sign == 1) {
                processor->R[instruction.itype.rd] = 0;
            } else if (r1_sign == 1 && r2_sign == 0) {
                processor->R[instruction.itype.rd] = 1;
            } else {
                processor->R[instruction.itype.rd] = (r1 < r2) ? 0 : 1;
            }
            processor->PC = processor->PC + 4;
        }
            break;
        case 0x3:   //sltiu
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = (processor->R[instruction.itype.rs1] < instruction.itype.imm) ? 1 : 0;
            processor->PC = processor->PC + 4;
            break;
        case 0x4:   //xori
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] ^ sign_extend_number(instruction.itype.imm, 12);
            processor->PC = processor->PC + 4;
            break;
        case 0x5:
            /* YOUR CODE HERE */
            switch (instruction.itype.imm & 0x400) {
                  case 0x000:    //srli---bits to shift is always positive   logic: fill the MSB with 0
                      processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] >> instruction.itype.imm;
                      processor->PC = processor->PC + 4;
                      break;
                  case 0x400:    //srai---bits to shift is always positive   arithmetic: fill the MSB with sign
                  {
                      ;
                      Register signBit = (processor->R[instruction.itype.rs1]) & 0x80000000;   //get the sign
                      Register distance_to_shift = instruction.itype.imm & 0x01f;
                      processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] >> distance_to_shift;
                      Register mask;
                      if (signBit == 0x80000000) {
                          mask = 0xffffffff << (32 - distance_to_shift);
                          processor->R[instruction.itype.rd] |= mask;
                      }
                      processor->PC = processor->PC + 4;
                      break;
                  }
                  default:
                      handle_invalid_instruction(instruction);
                      break;
            }
            break;
        case 0x6:   //ori
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] | sign_extend_number(instruction.itype.imm, 12);
            processor->PC = processor->PC + 4;
            break;
        case 0x7:   //andi
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = processor->R[instruction.itype.rs1] & sign_extend_number(instruction.itype.imm, 12);
            processor->PC = processor->PC + 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_ecall(Processor *p, Byte *memory) {

    Register i;

    switch(/* YOUR CODE HERE */p->R[10]) {    //judge the value in a0
        case 1: // print an integer
            printf("%d",p->R[11]);
            break;
        case 4: // print a string
            for(i = p->R[11]; i < MEMORY_SPACE && load(memory, i, LENGTH_BYTE); i++) {
                printf("%c",load(memory,i,LENGTH_BYTE));
            }
            break;
        case 10: // exit
            printf("exiting the simulator\n");
            exit(0);
            break;
        case 11: // print a character
            printf("%c",p->R[11]);
            break;
        default: // undefined ecall
            printf("Illegal ecall number %d\n", p->R[10]);
            exit(-1);
            break;
    }
}

void execute_branch(Instruction instruction, Processor *processor) {
    switch (instruction.sbtype.funct3) {
        case 0x0:   //beq
            /* YOUR CODE HERE */
            if (processor->R[instruction.sbtype.rs1] == processor->R[instruction.sbtype.rs2]) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
            break;
        case 0x1:   //bne
            /* YOUR CODE HERE */
            if (processor->R[instruction.sbtype.rs1] != processor->R[instruction.sbtype.rs2]) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
            break;
        case 0x4:   //blt
            /* YOUR CODE HERE */
        {
            ;
            Byte flag = 0;
            if (processor->R[instruction.sbtype.rs1] < processor->R[instruction.sbtype.rs2]) {  //signs are the same
                flag = 1;
            } else if (((processor->R[instruction.sbtype.rs1] & 0x80000000) == 0x80000000)
                && ((processor->R[instruction.sbtype.rs2] & 0x80000000) == 0x0)) {
                //R[rs1] is negative and the other is positive
                flag = 1;
            }
            if (flag) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
        }
            break;
        case 0x5:   //bge
            /* YOUR CODE HERE */
        {
            ;
            Byte flag1 = 0;
            if (processor->R[instruction.sbtype.rs1] >= processor->R[instruction.sbtype.rs2]) {  //signs are the same
                flag1 = 1;
            } else if (((processor->R[instruction.sbtype.rs1] & 0x80000000) == 0x0)
                && ((processor->R[instruction.sbtype.rs2] & 0x80000000) == 0x80000000)) {
                //R[rs1] is positive and the other is negative
                flag1 = 1;
            }
            if (flag1) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
        }
            break;
        case 0x6:   //bltu
            /* YOUR CODE HERE */
            if (processor->R[instruction.sbtype.rs1] < processor->R[instruction.sbtype.rs2]) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
            break;
        case 0x7:   //bgeu
            /* YOUR CODE HERE */
            if (processor->R[instruction.sbtype.rs1] >= processor->R[instruction.sbtype.rs2]) {
                processor->PC = processor->PC + get_branch_offset(instruction);
            } else {
                processor->PC = processor->PC + 4;
            }
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_load(Instruction instruction, Processor *processor, Byte *memory) {
    Address addr = processor->R[instruction.itype.rs1] + instruction.itype.imm;   //need to sign_extend? offset can be negative?
    switch (instruction.itype.funct3) {
        case 0x0:   //lb
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = load(memory, addr, LENGTH_BYTE);
            processor->R[instruction.itype.rd] = sign_extend_number(processor->R[instruction.itype.rd], 8);
            processor->PC = processor->PC + 4;
            break;
        case 0x1:   //lh
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = load(memory, addr, LENGTH_HALF_WORD);
            processor->R[instruction.itype.rd] = sign_extend_number(processor->R[instruction.itype.rd], 16);
            processor->PC = processor->PC + 4;
            break;
        case 0x2:   //lw
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = load(memory, addr, LENGTH_WORD);
            processor->PC = processor->PC + 4;
            break;
        case 0x4:   //lbu
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = load(memory, addr, LENGTH_BYTE);
            processor->R[instruction.itype.rd] &= 0x000000ff;
            processor->PC = processor->PC + 4;
            break;
        case 0x5:   //lhu
            /* YOUR CODE HERE */
            processor->R[instruction.itype.rd] = load(memory, addr, LENGTH_HALF_WORD);
            processor->R[instruction.itype.rd] &= 0x0000ffff;
            processor->PC = processor->PC + 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_store(Instruction instruction, Processor *processor, Byte *memory) {
    Address addr = processor->R[instruction.stype.rs1] + get_store_offset(instruction);
    switch (instruction.stype.funct3) {
        case 0x0:
            /* YOUR CODE HERE */
            store(memory, addr, LENGTH_BYTE, processor->R[instruction.stype.rs2]);
            processor->PC = processor->PC + 4;
            break;
        case 0x1:
            /* YOUR CODE HERE */
            store(memory, addr, LENGTH_HALF_WORD, processor->R[instruction.stype.rs2]);
            processor->PC = processor->PC + 4;
            break;
        case 0x2:
            /* YOUR CODE HERE */
            store(memory, addr, LENGTH_WORD, processor->R[instruction.stype.rs2]);
            processor->PC = processor->PC + 4;
            break;
        default:
            handle_invalid_instruction(instruction);
            break;
    }
}

void execute_jal(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */
    processor->R[instruction.ujtype.rd] = processor->PC + 4;
    processor->PC = processor->PC + get_jump_offset(instruction);
}

void execute_jalr(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */
    processor->R[instruction.itype.rd] = processor->PC + 4;
    processor->PC = processor->R[instruction.itype.rs1] + sign_extend_number(instruction.itype.imm, 12);
}

void execute_lui(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */
    processor->R[instruction.utype.rd] = (instruction.utype.imm << 12);
    processor->PC = processor->PC + 4;
}

void execute_auipc(Instruction instruction, Processor *processor) {
    /* YOUR CODE HERE */
    processor->R[instruction.utype.rd] = processor->PC + (instruction.utype.imm << 12);
    processor->PC = processor->PC + 4;
}

/*Methods below are related to litte endian of RISC-V. */
void store(Byte *memory, Address address, Alignment alignment, Word value) {
    /* YOUR CODE HERE */
    /*Byte byte0 = value & 0xff;
    Byte byte1 = (value & 0xff00) >> 8;
    Byte byte2 = (value & 0xff0000) >> 16;
    Byte byte3 = (value & 0xff000000) >> 24;
    Byte *p = memory + address;
    if (alignment == LENGTH_BYTE) {
        *p = byte0;
    } else if (alignment == LENGTH_HALF_WORD) {
        *p = byte0;
        *(p + 1) = byte1;
    } else if (alignment == LENGTH_WORD) {
        *p = byte0;
        *(p + 1) = byte1;
        *(p + 2) = byte2;
        *(p + 3) = byte3;
    } else {
        exit(-1);
    }*/

    Byte *p = memory + address;
    if (alignment == LENGTH_BYTE) {
        Byte my_byte = value & 0xff;
        *p = my_byte;
    } else if (alignment == LENGTH_HALF_WORD) {
        Half my_half = value & 0xffff;
        Half *p1 = (Half *)p;
        *p1 = my_half;
    } else if (alignment == LENGTH_WORD) {
        Word *p2 = (Word *)p;
        *p2 = value;
    } else {
        exit(-1);
    }
}

Word load(Byte *memory, Address address, Alignment alignment) {
    /* YOUR CODE HERE */
    Word ret_value;
    Byte *p = memory + address;
    if (alignment == LENGTH_BYTE) {
        ret_value = *p;
    } else if (alignment == LENGTH_HALF_WORD) {
        Half *p1 = (Half *)p;
        ret_value = *p1;
    } else if (alignment == LENGTH_WORD){
        Word *p2 = (Word *)p;
        ret_value = *p2;
    } else {
        exit(-1);
    }
    return ret_value;
}
