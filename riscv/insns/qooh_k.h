#ifdef QUEST
hadamard(*(p->get_qubits()), insn.k_qimm6());
STATE.qbit = insn.k_qimm6();
int old = STATE.qbit;
WRITE_RD(sext_xlen(old));
serialize();
#else
WRITE_RD(7);
#endif
