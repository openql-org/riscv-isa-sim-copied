#ifdef QUEST
sdgGate(*(p->get_qubits()), insn.k_qimm6());
WRITE_RD(insn.k_qimm6());
#else
WRITE_RD(2);
#endif
