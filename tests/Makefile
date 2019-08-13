
all:
	riscv64-unknown-elf-gcc -I../riscv -O0 test_qisa.c -o test_qisa

dis:
	riscv64-unknown-elf-objdump --disassemble=main test_qisa
	
exec:
	spike -q16 pk test_qisa
