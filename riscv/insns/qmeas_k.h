#ifdef QUEST
uint32_t rs2_num = insn.rs2();    // reference c-register number
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qimm6 = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();

fprintf(stderr, "qooh.k (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());

#define OUT_BUF_SIZE 1024
if (gnuradio) {
  uint32_t rs2_val = RS2;
  const char *sendipaddr = p->get_osc_sendip();
  size_t osc_sendport = p->get_osc_sendport();
  size_t osc_recvport = p->get_osc_recvport();
  UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
  UdpReceiveSocket recvSocket( IpEndpointName(sendipaddr, osc_recvport ) );
  char buffer[OUT_BUF_SIZE];
  osc::OutboundPacketStream p( buffer, OUT_BUF_SIZE );

  if (rs1_num > 0 && rs1_num <= nqregisters) {
    if (rs2_num == 0) {
      if (qimm6 >= 0 && qimm6 < nqubits) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/Mz" )
            << (int)rs1_num << (int)qimm6 << osc::EndMessage
          << osc::EndBundle;
      }
    }
  } else {
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      if ( (( rs2_val >> i ) & 0x1) == 1 ) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/Mz" )
            << (int)rs1_num << (int)i << osc::EndMessage
          << osc::EndBundle;
      }
    }
  }

  // send
  transmitSocket.Send( p.Data(), p.Size() );

  // recv(IO block!!)
  IpEndpointName fromEndPoint;
  int rlen = recvSocket.ReceiveFrom(fromEndPoint, buffer, OUT_BUF_SIZE);
  osc::ReceivedPacket recvPacket(buffer, rlen);
  osc::ReceivedMessage recvMessage(recvPacket);

  // this is sample.
  if (std::strcmp(recvMessage.AddressPattern(), "/Mz") == 0) {
    osc::ReceivedMessageArgumentStream args = recvMessage.ArgumentStream();
    osc::int32 a1;
    float a2;
    args >> a1 >> a2 >> osc::EndMessage;

    fprintf(stderr, "qmeas.k from gnuradio result: %d, %f\n", a1, a2);
  }

}

Qureg qubits = p->get_qubits();
reportState(qubits);
int qbit_measure = -1;
if (rs1_num > 0 && rs1_num <= nqregisters) {
  if (rs2_num == 0) {
    if (qimm6 >= 0 && qimm6 < nqubits) {
      fprintf(stderr, "qbit_idx : %d\n", rs1_num * nqubits + qimm6);
      qbit_measure = measure(qubits, rs1_num * nqubits + qimm6);
    } else {
      // TODO: qimm6 error
      fprintf(stderr, "out of order [qimm6]\n");
      STATE.qstatus |= 1;
    }
    WRITE_RD(qbit_measure);
  } else {
    fprintf(stderr, "rs2 : %x\n", RS2);
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      if ( (( RS2 >> i ) & 0x1) == 1 ) {
        fprintf(stderr, "qbit_idx : %d / %d\n", rs1_num * nqubits + i, i);
        qbit_measure |= (measure(qubits, rs1_num * nqubits + i) << i);
      }
    }
    WRITE_RD(qbit_measure);
  }
} else {
  // TODO: rs1 error
  fprintf(stderr, "out of order [rs1]\n");
  STATE.qstatus |= 1;
}
serialize();
#endif
