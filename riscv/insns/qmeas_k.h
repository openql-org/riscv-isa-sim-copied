#ifdef QUEST
reg_t rs2_reg = insn.rs2();       // reference c-register
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qbit_idx = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();
const char *sendipaddr = p->get_osc_sendip();
size_t osc_sendport = p->get_osc_sendport();

fprintf(stderr, "qmeas (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());
if (gnuradio) {
    UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
    char buffer[1024];
    osc::OutboundPacketStream p( buffer, 1024 );
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/test1" )
            << true << 23 << (float)3.1415 << "hello" << osc::EndMessage
        << osc::BeginMessage( "/test2" )
            << true << 24 << (float)10.8 << "world" << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send( p.Data(), p.Size() );
}

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

