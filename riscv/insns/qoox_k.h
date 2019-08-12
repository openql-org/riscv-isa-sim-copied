#ifdef QUEST
pauliX(*(p->get_qubits()), insn.k_qimm6());
WRITE_RD(insn.k_qimm6());
#else
WRITE_RD(4);
#endif
