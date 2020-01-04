#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int ret1 = 0;
    int ret2 = 0;

    // call qooh
    asm volatile( "qooh.k qzero,qt1,qzero,1");
    asm volatile( "qtocx.k qzero,qt1,qt1,1");
#if 0
    asm volatile( "qooh.k qzero,qt1,qzero,0");
    asm volatile( "qooh.k qzero,qt2,qzero,0");
    asm volatile( "qooh.k qzero,qt2,qzero,1");
    asm volatile( "qooh.k qzero,qt3,qzero,0");
    asm volatile( "qooh.k qzero,qt3,qzero,1");
    asm volatile( "qooh.k qzero,qt4,qzero,0");
    asm volatile( "qooh.k qzero,qt4,qzero,1");

    asm volatile( "qooh.k qzero,qt1,qzero,0");
    asm volatile( "qooh.k qzero,qt1,qzero,1");
    asm volatile( "qooh.k qzero,qt1,qzero,2");
    asm volatile( "qooh.k qzero,qt1,qzero,3");
    asm volatile( "qooh.k qzero,qt1,qzero,4");
    asm volatile( "qooh.k qzero,qt1,qzero,5");
    asm volatile( "qooh.k qzero,qt1,qzero,6");
    asm volatile( "qooh.k qzero,qt1,qzero,7");
    asm volatile( "qooh.k qzero,qt1,qzero,8");
    asm volatile( "qooh.k qzero,qt1,qzero,9");
    asm volatile( "qooh.k qzero,qt1,qzero,10");
    asm volatile( "qooh.k qzero,qt1,qzero,11");
    asm volatile( "qooh.k qzero,qt1,qzero,12");
    asm volatile( "qooh.k qzero,qt1,qzero,13");
    asm volatile( "qooh.k qzero,qt1,qzero,14");
    asm volatile( "qooh.k qzero,qt1,qzero,15");
    asm volatile( "qooh.k qzero,qt1,qzero,16");
    asm volatile( "qooh.k qzero,qt1,qzero,17");
    asm volatile( "qooh.k qzero,qt1,qzero,18");
    asm volatile( "qooh.k qzero,qt1,qzero,19");
    asm volatile( "qooh.k qzero,qt1,qzero,20");
    asm volatile( "qooh.k qzero,qt1,qzero,21");
    asm volatile( "qooh.k qzero,qt1,qzero,22");
    asm volatile( "qooh.k qzero,qt1,qzero,23");
    asm volatile( "qooh.k qzero,qt1,qzero,24");
    asm volatile( "qooh.k qzero,qt1,qzero,25");
    asm volatile( "qooh.k qzero,qt1,qzero,26");
    asm volatile( "qooh.k qzero,qt1,qzero,27");
    asm volatile( "qooh.k qzero,qt1,qzero,28");
    asm volatile( "qooh.k qzero,qt1,qzero,29");
    asm volatile( "qooh.k qzero,qt1,qzero,30");
    asm volatile( "qooh.k qzero,qt1,qzero,31");
    asm volatile( "qooh.k qzero,qt1,qzero,32");

    asm volatile( "qooh.k qzero,qt2,qzero,0");
    asm volatile( "qooh.k qzero,qt2,qzero,1");
    asm volatile( "qooh.k qzero,qt2,qzero,7");
    asm volatile( "qooh.k qzero,qt2,qzero,8");
    asm volatile( "qooh.k qzero,qt2,qzero,9");
    asm volatile( "qooh.k qzero,qt2,qzero,15");
    asm volatile( "qooh.k qzero,qt2,qzero,16");
    asm volatile( "qooh.k qzero,qt2,qzero,17");
    asm volatile( "qooh.k qzero,qt2,qzero,23");
    asm volatile( "qooh.k qzero,qt2,qzero,24");
    asm volatile( "qooh.k qzero,qt2,qzero,25");
    asm volatile( "qooh.k qzero,qt2,qzero,31");
    asm volatile( "qooh.k qzero,qt2,qzero,32");

    asm volatile( "qooh.k qzero,qt3,qzero,0");
    asm volatile( "qooh.k qzero,qt3,qzero,1");
    asm volatile( "qooh.k qzero,qt3,qzero,7");
    asm volatile( "qooh.k qzero,qt3,qzero,8");
    asm volatile( "qooh.k qzero,qt3,qzero,9");
    asm volatile( "qooh.k qzero,qt3,qzero,15");
    asm volatile( "qooh.k qzero,qt3,qzero,16");
    asm volatile( "qooh.k qzero,qt3,qzero,17");
    asm volatile( "qooh.k qzero,qt3,qzero,23");
    asm volatile( "qooh.k qzero,qt3,qzero,24");
    asm volatile( "qooh.k qzero,qt3,qzero,25");
    asm volatile( "qooh.k qzero,qt3,qzero,31");
    asm volatile( "qooh.k qzero,qt3,qzero,32");

    asm volatile( "qooh.k qzero,qt4,qzero,0");
    asm volatile( "qooh.k qzero,qt4,qzero,1");
    asm volatile( "qooh.k qzero,qt4,qzero,7");
    asm volatile( "qooh.k qzero,qt4,qzero,8");
    asm volatile( "qooh.k qzero,qt4,qzero,9");
    asm volatile( "qooh.k qzero,qt4,qzero,15");
    asm volatile( "qooh.k qzero,qt4,qzero,16");
    asm volatile( "qooh.k qzero,qt4,qzero,17");
    asm volatile( "qooh.k qzero,qt4,qzero,23");
    asm volatile( "qooh.k qzero,qt4,qzero,24");
    asm volatile( "qooh.k qzero,qt4,qzero,25");
    asm volatile( "qooh.k qzero,qt4,qzero,31");
    asm volatile( "qooh.k qzero,qt4,qzero,32");

    asm volatile( "qooh.k qzero,qt5,qzero,0");
    asm volatile( "qooh.k qzero,qt5,qzero,1");
    asm volatile( "qooh.k qzero,qt5,qzero,7");
    asm volatile( "qooh.k qzero,qt5,qzero,8");
    asm volatile( "qooh.k qzero,qt5,qzero,9");
    asm volatile( "qooh.k qzero,qt5,qzero,15");
    asm volatile( "qooh.k qzero,qt5,qzero,16");
    asm volatile( "qooh.k qzero,qt5,qzero,17");
    asm volatile( "qooh.k qzero,qt5,qzero,23");
    asm volatile( "qooh.k qzero,qt5,qzero,24");
    asm volatile( "qooh.k qzero,qt5,qzero,25");
    asm volatile( "qooh.k qzero,qt5,qzero,31");
    asm volatile( "qooh.k qzero,qt5,qzero,32");

    asm volatile( "qooh.k qzero,qt6,qzero,0");
    asm volatile( "qooh.k qzero,qt6,qzero,1");
    asm volatile( "qooh.k qzero,qt6,qzero,7");
    asm volatile( "qooh.k qzero,qt6,qzero,8");
    asm volatile( "qooh.k qzero,qt6,qzero,9");
    asm volatile( "qooh.k qzero,qt6,qzero,15");
    asm volatile( "qooh.k qzero,qt6,qzero,16");
    asm volatile( "qooh.k qzero,qt6,qzero,17");
    asm volatile( "qooh.k qzero,qt6,qzero,23");
    asm volatile( "qooh.k qzero,qt6,qzero,24");
    asm volatile( "qooh.k qzero,qt6,qzero,25");
    asm volatile( "qooh.k qzero,qt6,qzero,31");
    asm volatile( "qooh.k qzero,qt6,qzero,32");

    asm volatile( "qooh.k qzero,qt7,qzero,0");
    asm volatile( "qooh.k qzero,qt7,qzero,1");
    asm volatile( "qooh.k qzero,qt7,qzero,7");
    asm volatile( "qooh.k qzero,qt7,qzero,8");
    asm volatile( "qooh.k qzero,qt7,qzero,9");
    asm volatile( "qooh.k qzero,qt7,qzero,15");
    asm volatile( "qooh.k qzero,qt7,qzero,16");
    asm volatile( "qooh.k qzero,qt7,qzero,17");
    asm volatile( "qooh.k qzero,qt7,qzero,23");
    asm volatile( "qooh.k qzero,qt7,qzero,24");
    asm volatile( "qooh.k qzero,qt7,qzero,25");
    asm volatile( "qooh.k qzero,qt7,qzero,31");
    asm volatile( "qooh.k qzero,qt7,qzero,32");

    asm volatile( "qooh.k qzero,qs0,qzero,0");
    asm volatile( "qooh.k qzero,qs0,qzero,1");
    asm volatile( "qooh.k qzero,qs0,qzero,7");
    asm volatile( "qooh.k qzero,qs0,qzero,8");
    asm volatile( "qooh.k qzero,qs0,qzero,9");
    asm volatile( "qooh.k qzero,qs0,qzero,15");
    asm volatile( "qooh.k qzero,qs0,qzero,16");
    asm volatile( "qooh.k qzero,qs0,qzero,17");
    asm volatile( "qooh.k qzero,qs0,qzero,23");
    asm volatile( "qooh.k qzero,qs0,qzero,24");
    asm volatile( "qooh.k qzero,qs0,qzero,25");
    asm volatile( "qooh.k qzero,qs0,qzero,31");
    asm volatile( "qooh.k qzero,qs0,qzero,32");

    asm volatile( "qooh.k qzero,qs1,qzero,0");
    asm volatile( "qooh.k qzero,qs1,qzero,1");
    asm volatile( "qooh.k qzero,qs1,qzero,7");
    asm volatile( "qooh.k qzero,qs1,qzero,8");
    asm volatile( "qooh.k qzero,qs1,qzero,9");
    asm volatile( "qooh.k qzero,qs1,qzero,15");
    asm volatile( "qooh.k qzero,qs1,qzero,16");
    asm volatile( "qooh.k qzero,qs1,qzero,17");
    asm volatile( "qooh.k qzero,qs1,qzero,23");
    asm volatile( "qooh.k qzero,qs1,qzero,24");
    asm volatile( "qooh.k qzero,qs1,qzero,25");
    asm volatile( "qooh.k qzero,qs1,qzero,31");
    asm volatile( "qooh.k qzero,qs1,qzero,32");

    asm volatile( "qooh.k qzero,qa0,qzero,0");
    asm volatile( "qooh.k qzero,qa0,qzero,1");
    asm volatile( "qooh.k qzero,qa0,qzero,7");
    asm volatile( "qooh.k qzero,qa0,qzero,8");
    asm volatile( "qooh.k qzero,qa0,qzero,9");
    asm volatile( "qooh.k qzero,qa0,qzero,15");
    asm volatile( "qooh.k qzero,qa0,qzero,16");
    asm volatile( "qooh.k qzero,qa0,qzero,17");
    asm volatile( "qooh.k qzero,qa0,qzero,23");
    asm volatile( "qooh.k qzero,qa0,qzero,24");
    asm volatile( "qooh.k qzero,qa0,qzero,25");
    asm volatile( "qooh.k qzero,qa0,qzero,31");
    asm volatile( "qooh.k qzero,qa0,qzero,32");
#endif

    // call qmeas
    asm volatile( "qmeas.k  %0,qt1,qzero,0" :"=r"(ret1));
    printf("%d\n", ret1);
    asm volatile( "qmeas.k  %0,qt1,qzero,1" :"=r"(ret2));
    printf("%d\n", ret2);
    
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
