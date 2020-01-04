#ifdef QUEST
uint32_t rs2_num = insn.rs2();    // control q-register number
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t target = insn.rd();      // target qubit index
uint32_t qimm6 = insn.k_qimm6() & 0b011111;  // control qubit index
bool qimm6_flag = ((insn.k_qimm6() & 0b100000) == 0);
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();

fprintf(stderr, "qtocx.k (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());

#define OUT_BUF_SIZE 1024
if (gnuradio) {
  const char *sendipaddr = p->get_osc_sendip();
  size_t osc_sendport = p->get_osc_sendport();
  UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
  char buffer[OUT_BUF_SIZE];
  osc::OutboundPacketStream p( buffer, OUT_BUF_SIZE );
  if (rs1_num > 0 && rs1_num <= nqregisters && rs2_num > 0 && rs2_num <= nqregisters) {
    if (qimm6_flag) {
      if (qimm6 >= 0 && qimm6 < nqubits && target >=0 && target < nqubits) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/CX" )
            << (int)rs1_num << (int)target << (int)rs1_num << (int)qimm6 << osc::EndMessage
          << osc::EndBundle;
      }
    } else {
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/CX" )
          << (int)rs1_num << (int)i << (int)rs2_num << (int)i << osc::EndMessage
        << osc::EndBundle;
      }
    }
  transmitSocket.Send( p.Data(), p.Size() );
  }
}

Qureg qubits = p->get_qubits();
if (rs1_num > 0 && rs1_num <= nqregisters && rs2_num > 0 && rs2_num <= nqregisters) {
  if (qimm6_flag) {
    if (qimm6 >= 0 && qimm6 < nqubits && target >=0 && target < nqubits) {
      uint32_t ctrl = rs2_num * nqubits + qimm6;
      uint32_t targ = rs1_num * nqubits + target;
      if( ctrl != targ ) {
        fprintf(stderr, "qbit_idx_of_control : %d\n", ctrl);
        fprintf(stderr, "qbit_idx_of_target  : %d\n", targ);
        controlledNot(qubits, ctrl, targ);
      } else {
        fprintf(stderr, "the target equals the control.\n");
        STATE.qstatus |= 1;
      }
    } else {
      // TODO: qimm6 error
      fprintf(stderr, "out of order [qimm6 or rd]\n");
      STATE.qstatus |= 1;
    }
  } else {
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      uint32_t ctrl = rs2_num * nqubits + i;
      uint32_t targ = rs1_num * nqubits + i;
      fprintf(stderr, "qbit_idx_of_control : %d\n", ctrl);
      fprintf(stderr, "qbit_idx_of_target  : %d\n", targ);
      controlledNot(qubits, ctrl, targ);
    }
  }
} else {
  // TODO: rs1 error
  fprintf(stderr, "out of order [rs1]\n");
  STATE.qstatus |= 1;
}
serialize();
#endif
