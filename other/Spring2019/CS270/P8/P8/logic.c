/** @file logic.c
 *  @brief Implementation of the logic.h interface
 *  @details This is a skeleton implementation of the interface that you will write
 *  for the assignment. The skeleton provides functions to fetch, decode, and execute 
 *  instructions as well as the ADD immediate and ST instructions.  This allows you
 *  to run the simulator with a simple test program before starting to verify your
 *  setup. You must complete the remainder of the instructions.
 *  <p>
 *  @author <b>your name here</b>
 */

#include "lc3.h"
#include "hardware.h"
#include "logic.h"

static int not_implemented() {
  return (! OK);
}


/* Instruction fetch, decode, and execution functions already provided. 
 *
 * logic_fetch_instruction completes the first 3 clock cycles of each
 * instruction that load the IR from PC address and increments PC.
 *
 * logic_decode_instruction verifies instruction and extracts components 
 * from the IR used by the instructions and performs appropriate sign extensions.
 *
 * logic_execute_instruction calls the appropriate routine to complete
 * the remaining cycles for the specified opcode.  
 */

void logic_fetch_instruction (instruction_t* inst) {
  /* clock cycle 1 */
  hardware_gate_PC();             /* put PC onto BUS   */
  hardware_load_MAR();            /* load MAR from BUS */
  hardware_set_PC(*lc3_BUS+1);    /* increment PC      */
  inst->addr = *lc3_BUS;          /* save PC for inst  */
  /* clock cycle 2 */
  hardware_memory_enable(0);      /* read memory       */
  /* clock cycle 3 */
  hardware_gate_MDR();            /* put MDR on BUS    */
  inst->bits = *lc3_BUS;          /* load IR from BUS  */

}

int logic_decode_instruction (instruction_t* inst) {
  int valid   = OK; /* valid instruction */
  int instVal = inst->bits;

  /*  Extract the components from the instruction (instVal) */

  inst->opcode              = (instVal >> 12) & 0xF;

  /*
  inst->DR                  = 0;
  inst->SR1                 = 0;
  inst->SR2                 = 0;
  inst->bit5                = 0;
  inst->bit11               = 0;
  inst->trapvect8           = 0;
  inst->imm5                = 0;
  inst->offset6             = 0;
  inst->PCoffset9           = 0;
  inst->PCoffset11          = 0;
  */
   
  /* check for invalid instructions (i.e. fields which must be all 0's or 1's */

  switch (inst->opcode) {
    /*
    case OP_BR:
      if ( ? )
        valid = !OK;
      break;
    
    case OP_ADD:
    case OP_AND: 
      if ( ? )
        valid = !OK;
      break;

    case OP_JSR_JSRR:
      if ( ? )
        valid = !OK;
      break;

    case OP_RTI:
      if ( ? )
        valid = !OK;
      break;

    case OP_NOT:
      if ( ? )
        valid = !OK;
      break;

    case OP_JMP_RET:
      if ( ? )
        valid = !OK;
      break;

    case OP_RESERVED:
      valid = !OK; // RESERVED not used
      break;

    case OP_TRAP:
      if ( ? )
        valid = !OK;
      break;
    */
    default: /* LEA, LD, LDI, LDR, ST, STI STR, ... have no additional checks */
      break;
  }

  return valid;
}


/** @todo implement each instruction */

int logic_execute_instruction (instruction_t* inst) {
  switch (inst->opcode) {
    case OP_BR:       return not_implemented();
    case OP_ADD:      return not_implemented();
    case OP_LD:       return not_implemented();
    case OP_ST:       return not_implemented();
    case OP_JSR_JSRR: return not_implemented();
    case OP_AND:      return not_implemented();
    case OP_LDR:      return not_implemented();
    case OP_STR:      return not_implemented();
    case OP_RTI:      return not_implemented();
    case OP_NOT:      return not_implemented();
    case OP_LDI:      return not_implemented();
    case OP_STI:      return not_implemented();
    case OP_JMP_RET:  return not_implemented();
    case OP_RESERVED: return not_implemented();
    case OP_LEA:      return not_implemented();
    case OP_TRAP:     return not_implemented();
    default:          return not_implemented();
  }

  return (! OK);
}


