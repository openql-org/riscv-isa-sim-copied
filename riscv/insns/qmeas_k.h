#ifdef QUEST
reg_t rs2_reg = insn.rs2();       // reference c-register
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qbit_idx = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
fprintf(stderr, "qmeas (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
int qbit_measure = -1;
reportState(p->get_qubits(rs1_num));
if (rs2_reg == 0) {
  qbit_measure = measure(p->get_qubits(rs1_num), qbit_idx);
  STATE.qbit = qbit_idx;
} else {
  fprintf(stderr, "rd : %lx\n", RD);
  fprintf(stderr, "rs2 : %lx\n", RS2);
  qbit_measure = RD;
  for (uint8_t i = 0; i < nqubits ; i++ ) {
    if ( (( RS2 >> i ) & 0x1) == 1 ) {
      fprintf(stderr, "q_idx = %d\n", i);
      qbit_measure |= (measure(p->get_qubits(rs1_num), i) << i);
    }
  }
}
WRITE_RD(qbit_measure);
#endif

