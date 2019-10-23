#ifdef QUEST
reg_t rs2_num = insn.rs2();
uint32_t rs1_idx = insn.rs1();
uint32_t qimm6 = insn.k_qimm6();
fprintf(stderr, "hadamard : rd: %ld, rs1: %ld, rs2: %ld, qimm6: %ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
if (rs2_num == 0) {
  hadamard(p->get_qubits(rs1_idx), qimm6);
  STATE.qbit = qimm6;
} else {
  fprintf(stderr, "rs2 : %lx\n", RS2);
  for (uint8_t i = 0; i < 32; i++ ) {
    if ( ( RS2 >> i ) & 0x1 == 1 ) {
      fprintf(stderr, "q_idx = %d\n", i);
      hadamard(p->get_qubits(rs1_idx), i);
    }
  }
}
serialize();
#endif
