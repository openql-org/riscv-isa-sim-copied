#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "encoding.h"

// "\x82\x80\x00\x00"(0x8082) is `c.jr x1`
#define c_jr_x1 "\x82\x80\x00\x00"

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

// rd is x10
static char* qmeas  = "\x0b\x05\x00\x80" c_jr_x1;
static char* qtelep = "\x0b\x05\x00\x00" c_jr_x1;
static char* qtocx  = "\x0b\x45\x00\x80" c_jr_x1;
static char* qootdg = "\x0b\x15\x00\x00" c_jr_x1;
static char* qoosdg = "\x0b\x25\x00\x00" c_jr_x1;
static char* qooz   = "\x0b\x35\x00\x00" c_jr_x1;
static char* qoox   = "\x0b\x45\x00\x00" c_jr_x1;
static char* qoos   = "\x0b\x55\x00\x00" c_jr_x1;
static char* qoot   = "\x0b\x65\x00\x00" c_jr_x1;
char* qooh   = "\x0b\x75\x00\x00" c_jr_x1;

#define QOP(op,rd,rs1,rs2,qimm6) ((int (*)())op)()  // TODO: to use parameters

int main(int argc, char **argv) {
    char* ops[] = { qmeas, qtelep, qtocx, qootdg, qoosdg, qooz, qoox, qoos, qoot, qooh, NULL };
    for( char **p = &ops[0]; *p != NULL; p++){
        char *o = *p;
        uint32_t op = (uint8_t)*o + ((uint8_t)*(o+1) <<8) + ((uint8_t)*(o+2) <<16) + ((uint8_t)*(o+3) <<24);
        int c = QOP(*p, /*rd*/ 10, /*rs1*/ 1, /*rs2*/ 2, /*qimm6*/ 3);
        printf("%d\n", c);
    }
    return 0;
}
