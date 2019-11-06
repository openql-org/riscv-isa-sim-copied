#ifdef QUEST
reg_t rs2_num = insn.rs2();
uint32_t rs1_idx = insn.rs1();
uint32_t qimm6 = insn.k_qimm6();
fprintf(stderr, "qmeas : rd: %ld, rs1: %ld, rs2: %ld, qimm6: %ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
int qbit_measure = -1;
if (rs2_num == 0) {
  qbit_measure = measure(p->get_qubits(rs1_idx), insn.k_qimm6());
} else {
  fprintf(stderr, "rd : %lx\n", RD);
  fprintf(stderr, "rs2 : %lx\n", RS2);
  qbit_measure = RD;
  for (uint8_t i = 0; i < 32; i++ ) {
    if ( (( RS2 >> i ) & 0x1) == 1 ) {
      fprintf(stderr, "q_idx = %d\n", i);
      qbit_measure |= (measure(p->get_qubits(rs1_idx), i) << i);
    }
  }
}
WRITE_RD(qbit_measure);
#endif

