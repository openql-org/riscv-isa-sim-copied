#ifdef QUEST
int qbit_measure = measure(p->get_qubits(), insn.k_qimm6());
WRITE_RD(qbit_measure);
#endif

