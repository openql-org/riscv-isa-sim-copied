# memo build with LLVM-RISCV
# [source code] => [clang]byte code => [clang]assembly code => [riscv64-unknown-elf-gcc]execute code
# clang -target riscv64-unknown-linux-gnu -I../riscv/ -c test_qisa.c -emit-llvm -o test_qisa.bc
# llc -march=riscv64 -relocation-model=pic -filetype=asm test_qisa.bc  -o test_qisa.s
# riscv64-unknown-elf-gcc test_qisa.s -o test_qisa -march=rv64imac -mabi=lp64
# or
# [source code] => [clang]object code => [riscv64-unknown-elf-gcc]execute code
# clang -O -I../riscv/ -c test_qisa.c
# riscv64-unknown-elf-gcc test_qisa.o -o test_qisa -march=rv64imac -mabi=lp64
#
all:
	riscv64-unknown-elf-gcc -I../riscv -O0 test_qisa.c -o test_qisa

dis:
	riscv64-unknown-elf-objdump --disassemble=main test_qisa
	
exec:
	spike -q16 pk test_qisa
