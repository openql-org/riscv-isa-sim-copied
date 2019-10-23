#ifdef QUEST
uint32_t rs1_idx = insn.rs1();
int qbit_measure = measure(p->get_qubits(rs1_idx), insn.k_qimm6());
// WRITE_RD(qbit_measure);
// here is debug output.
fprintf(stderr, "qmeas : rd: %ld, rs1: %ld, rs2: %ld, qimm6: %ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
WRITE_RD(qbit_measure);
#endif

