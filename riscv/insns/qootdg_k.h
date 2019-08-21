#ifdef QUEST
tdgGate(*(p->get_qubits()), insn.k_qimm6());
WRITE_RD(insn.k_qimm6());
#else
WRITE_RD(1);
#endif
