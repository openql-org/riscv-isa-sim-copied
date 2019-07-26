#include <stdio.h>
#include <stdlib.h>

// const char* opcode4 = "\x7b\x05\xb5\x00\x82\x80";
// const char* opcode3 = "\x5b\x05\xb5\x00\x82\x80";
// const char* opcode2 = "\x2b\x05\xb5\x00\x82\x80";
const char* opcode1    = "\x0b\x05\xb5\x00\x82\x80";
/*
opcodeは以下の命令に対応する。
test_i a0,a0,a1
ret

0111 10 : 1E
0101 10 : 16
0000 10 : 02
0010 10 : 0A
*/

int main(int argc, char* argv[]) {
    int ret = ((int (*)(int, int))opcode2)(1, 3);
    printf("%d\n", ret);

    return 0;
}
