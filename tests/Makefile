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
	# riscv64-unknown-elf-objdump --disassemble=main test_qisa
	riscv64-unknown-elf-objdump -D test_qisa > test_qisa.dis
	
exec:
	spike -q8 -r32 pk test_qisa

qfunc-clang:
	clang -target riscv64-unknown-linux-gnu -c test_qfunc.c -emit-llvm -o test_qfunc.bc
	llvm-dis test_qfunc.bc
	llc -march=riscv64 -relocation-model=pic -filetype=asm test_qfunc.bc  -o test_qfunc.s
	riscv64-unknown-elf-gcc test_qfunc.s -o test_qfunc -march=rv64imafdkc

qfunc:
	riscv64-unknown-elf-gcc test_qfunc.c -march=rv64imafdkc -o test_qfunc

qfunc-dis:
	riscv64-unknown-elf-objdump -D test_qfunc > test_qfunc.dis

qfunc-exec:
	spike -q2 -r4 pk test_qfunc

qfunc-exec-4x5:
	spike -q4 -r5 pk test_qfunc

qfunc-exec-5x4:
	spike -q5 -r4 pk test_qfunc

qfunc-exec-8x2:
	spike -q8 -r2 pk test_qfunc

qfunc-exec-12x1:
	spike -q12 -r1 pk test_qfunc

qfunc-exec-2x12:
	spike -q2 -r12 pk test_qfunc

qfunc-exec-1x24:
	spike -q1 -r24 pk test_qfunc

qfunc-test:
	clang -target riscv64-unknown-linux-gnu -emit-llvm -S -O3 -o  test_q_test.ll test_q_test.c
	clang -target riscv64-unknown-linux-gnu -O3 -c test_qfunc_test.c -emit-llvm -o test_qfunc_test.bc
	llvm-dis test_qfunc_test.bc
	clang -target riscv64-unknown-linux-gnu -emit-llvm -S -O -o  test_q_test.ll test_q_test.c
	llvm-link test_qfunc_test.ll test_q_test.ll -S -o link.ll
	opt -O3 -S -mem2reg  link.ll > out.ll
	llc -march=riscv64 -relocation-model=pic -filetype=asm out.ll -o test_qfunc_test.s
	riscv64-unknown-elf-gcc test_qfunc_test.s -o test_qfunc_test -march=rv64imafdkc

clean: 
	@rm -f test_qisa test_qisa.dis test_qisa.o test_qisa.i test_qisa.s
