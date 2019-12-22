#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int ret1 = 0;

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
    printf("%d\n", ret1);
    
#if 0
    asm volatile(
    " qtelep.k  qa0, qt1, qzero, 0;\
      li        %0, 0;\
      li        a7, 11;\
      qooh.k    qa0, qt1, qzero, 0;\
      qooz.k    qa0, qt1, qzero, 0;\
      qmeas.k   %0, qt1, qzero, 0;\
    "
    :"=r"(ret1)
    :
    );
    printf("%d\n", ret1);
#endif

    return 0;
}
