#ifdef QUEST
reg_t rs2_reg = insn.rs2();       // reference c-register
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qbit_idx = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
fprintf(stderr, "qoox (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
if (rs2_reg == 0) {
  pauliX(p->get_qubits(rs1_num), qbit_idx);
  STATE.qbit = qbit_idx;
} else {
  fprintf(stderr, "rs2 : %lx\n", RS2);
  for (uint8_t i = 0; i < nqubits ; i++ ) {
    if ( (( RS2 >> i ) & 0x1) == 1 ) {
      fprintf(stderr, "q_idx = %d\n", i);
      pauliX(p->get_qubits(rs1_num), i);
    }
  }
}
reportState(p->get_qubits(rs1_num));
serialize();
#endif
