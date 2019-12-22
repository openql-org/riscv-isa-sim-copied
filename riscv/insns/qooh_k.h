#ifdef QUEST
reg_t rs2_reg = insn.rs2();       // reference c-register
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t qbit_idx = insn.k_qimm6();  // qubit index of the target q-register
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();
const char *sendipaddr = p->get_osc_sendip();
size_t osc_sendport = p->get_osc_sendport();

fprintf(stderr, "qooh (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());

if (gnuradio) {
    UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
    char buffer[1024];
    osc::OutboundPacketStream p( buffer, 1024 );
    p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/hadamard" )
            << 1 << (int)qbit_idx << osc::EndMessage
        << osc::EndBundle;
    transmitSocket.Send( p.Data(), p.Size() );
}

if (rs2_reg == 0) {
  hadamard(p->get_qubits(rs1_num), qbit_idx);
  STATE.qbit = qbit_idx;
} else {
  fprintf(stderr, "rs2 : %lx\n", RS2);
  for (uint8_t i = 0; i < nqubits ; i++ ) {
    if ( (( RS2 >> i ) & 0x1) == 1 ) {
      fprintf(stderr, "q_idx = %d\n", i);
      hadamard(p->get_qubits(rs1_num), i);
    }
  }
}
serialize();
#endif
