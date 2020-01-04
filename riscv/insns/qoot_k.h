#ifdef QUEST
uint32_t rs2_num = insn.rs2();    // reference c-register number
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qimm6 = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();

fprintf(stderr, "qoot.k (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());

#define OUT_BUF_SIZE 1024
if (gnuradio) {
  uint32_t rs2_val = RS2;
  const char *sendipaddr = p->get_osc_sendip();
  size_t osc_sendport = p->get_osc_sendport();
  UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
  char buffer[OUT_BUF_SIZE];
  osc::OutboundPacketStream p( buffer, OUT_BUF_SIZE );
  if (rs1_num > 0 && rs1_num <= nqregisters) {
    if (rs2_num == 0) {
      if (qimm6 >= 0 && qimm6 < nqubits) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/T" )
            << (int)rs1_num << (int)qimm6 << osc::EndMessage
          << osc::EndBundle;
      }
    }
  } else {
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      if ( (( rs2_val >> i ) & 0x1) == 1 ) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/T" )
            << (int)rs1_num << (int)i << osc::EndMessage
          << osc::EndBundle;
      }
    }
  transmitSocket.Send( p.Data(), p.Size() );
  }
}

Qureg qubits = p->get_qubits();
if (rs1_num > 0 && rs1_num <= nqregisters) {
  if (rs2_num == 0) {
    if (qimm6 >= 0 && qimm6 < nqubits) {
      fprintf(stderr, "qbit_idx : %d\n", rs1_num * nqubits + qimm6);
      tGate(qubits, rs1_num * nqubits + qimm6);
    } else {
      // TODO: qimm6 error
      fprintf(stderr, "out of order [qimm6]\n");
      STATE.qstatus |= 1;
    }
  } else {
    fprintf(stderr, "rs2 : %x\n", RS2);
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      if ( (( RS2 >> i ) & 0x1) == 1 ) {
        fprintf(stderr, "qbit_idx : %d / %d\n", rs1_num * nqubits + i, i);
        tGate(qubits, rs1_num * nqubits + i);
      }
    }
  }
} else {
  // TODO: rs1 error
  fprintf(stderr, "out of order [rs1]\n");
  STATE.qstatus |= 1;
}
serialize();
#endif
