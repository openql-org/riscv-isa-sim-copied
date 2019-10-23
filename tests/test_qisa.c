#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encoding.h"

// qmeas.k   rd rs1 rs2 qimm6 31=1 14..12=0 6..2=0x02 1..0=3  # quantum measurement
// qtelep.k  rd rs1 rs2 qimm6 31=0 14..12=0 6..2=0x02 1..0=3  # quantum teleportation
// qtocx.k   rd rs1 rs2 qimm6 31=1 14..12=4 6..2=0x02 1..0=3  # quantum two-qubit operator CX-gate
// qootdg.k  rd rs1 rs2 qimm6 31=0 14..12=1 6..2=0x02 1..0=3  # quantum one-qubit operator T^{\dag}-gate
// qoosdg.k  rd rs1 rs2 qimm6 31=0 14..12=2 6..2=0x02 1..0=3  # quantum one-qubit operator S^{\dag}-gate
// qooz.k    rd rs1 rs2 qimm6 31=0 14..12=3 6..2=0x02 1..0=3  # quantum one-qubit operator Z-gate
// qoox.k    rd rs1 rs2 qimm6 31=0 14..12=4 6..2=0x02 1..0=3  # quantum one-qubit operator X-gate
// qoos.k    rd rs1 rs2 qimm6 31=0 14..12=5 6..2=0x02 1..0=3  # quantum one-qubit operator S-gate
// qoot.k    rd rs1 rs2 qimm6 31=0 14..12=6 6..2=0x02 1..0=3  # quantum one-qubit operator T-gate
// qooh.k    rd rs1 rs2 qimm6 31=0 14..12=7 6..2=0x02 1..0=3  # quantum one-qubit operator H-gate

#define c_jr_x1 "\x82\x80\x00\x00"   // 0x8082 is `c.jr x1`

#define qtelep_rd5_q1_q0 "\x0b\x85\x00"
#define qmeas_rd5_q1_q0  "\x0b\x85\x00"  // should be qimm7
#define qtocx_rd5_q1_q0  "\x0b\xc5\x00"  // should be qimm7
#define qootdg_rd5_q1_q0 "\x0b\x15\x00"
#define qoosdg_rd5_q1_q0 "\x0b\x25\x00"
#define qooz_rd5_q1_q0   "\x0b\xb5\x00"
#define qoox_rd5_q1_q0   "\x0b\xc5\x00"
#define qoos_rd5_q1_q0   "\x0b\xd5\x00"
#define qoot_rd5_q1_q0   "\x0b\xf5\x00"
#define qooh_rd5_q1_q0   "\x0b\xf5\x00"
#define qimm6_0 "\x00"
#define qimm6_1 "\x02"
#define qimm6_2 "\x04"
#define qimm6_3 "\x06"
#define qimm6_4 "\x08"
#define qimm6_5 "\x0a"
#define qimm6_6 "\x0c"
#define qimm6_7 "\x0e"
#define qimm6_8 "\x10"
#define qimm6_9 "\x12"
#define qimm6_a "\x14"
#define qimm6_b "\x16"
#define qimm6_c "\x18"
#define qimm6_d "\x1a"
#define qimm6_e "\x1c"
#define qimm6_f "\x1e"
#define qimm7_0 "\x80"
#define qimm7_1 "\x82"
#define qimm7_2 "\x84"
#define qimm7_3 "\x86"
#define qimm7_4 "\x88"
#define qimm7_5 "\x8a"
#define qimm7_6 "\x8c"
#define qimm7_7 "\x8e"
#define qimm7_8 "\x90"
#define qimm7_9 "\x92"
#define qimm7_a "\x94"
#define qimm7_b "\x96"
#define qimm7_c "\x98"
#define qimm7_d "\x9a"
#define qimm7_e "\x9c"
#define qimm7_f "\x9e"
#define qooh_   "\x0b\xf5\xf0"
#define set_a5_0 "\xaa\x87"
#define addi_a5_ "\xad\x07" // = 11

#define SuperpositionAndMeasure(qop,pos) ((int (*)())qop)()  // TODO: to use parameters
static char* test_prog[] = { 
qtelep_rd5_q1_q0 qimm6_0 \
set_a5_0 addi_a5_ \
qooh_ qimm6_0 \
qmeas_rd5_q1_q0 qimm7_1 \
c_jr_x1,
      NULL };

int main(int argc, char **argv) {

      char **ops = &test_prog[0];

        //for( int i = 0; i < 16; i++) {
          int qreg;

          #pragma oql quantum private(qreg)
          {
            qreg = SuperpositionAndMeasure(*ops, 0);
          }

        printf("Result => %d\n",qreg);
        // printf("[%.3d] Result => %d\n",i, qreg);
        //}
    
    return 0;
}



