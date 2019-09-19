#ifdef QUEST
hadamard(p->get_qubits(), insn.k_qimm6());
STATE.qbit = insn.k_qimm6();
int old = STATE.qbit;
//WRITE_RD(sext_xlen(old));
//WRITE_RD(RS1);
// here is debug output.
fprintf(stderr, "hadamard : rd: %ld, rs1: %ld, rs2: %ld, qimm6: %ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
serialize();
#else
WRITE_RD(7);
#endif
