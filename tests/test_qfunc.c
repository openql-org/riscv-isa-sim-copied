#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int ret1 = 0;

    /***
    // call qooh
    asm volatile(
    "qooh.k  qa0,qt1,qzero,1"
    );

    // call qmeas
    asm volatile(
     "qmeas.k  %0,qt1,qzero,1"
    :"=r"(ret1)
    :
    );
    ***/
    
    asm volatile(
    " qtelep.k  qa0, qt1, qzero, 0;\
      mv        a6, a0;\
      mv        a5, a0;\
      addi      a6, a6, 11;\
      qooh.k    qa0, qt1, qa6, 0;\
      qtocx.k   qt1, qt1, qzero, 2;\
      qmeas.k   %0, qt1, qa6, 0;\
    "
    :"=r"(ret1)
    :
    );
    printf("%d\n", ret1);

    return 0;
}
