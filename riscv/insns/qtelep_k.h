#ifdef QUEST
uint32_t rs2_num = insn.rs2();    // reference c-register number
uint32_t rs1_num = insn.rs1();    // target q-register number
uint32_t target = insn.rd();      // target qubit index
uint32_t qimm6 = insn.k_qimm6() & 0b011111;  // control qubit index
bool qimm6_flag = ((insn.k_qimm6() & 0b100000) == 0);
uint8_t nqregisters = p->get_nqregisters();
uint8_t nqubits = p->get_nqubits();
bool gnuradio =  p->get_gnuradio();

fprintf(stderr, "qtelep.k (rd)%ld, (rs1)%ld, (rs2)%ld, (qimm6)%ld\n", insn.rd(), insn.rs1(), insn.rs2(), insn.k_qimm6());

#define OUT_BUF_SIZE 1024
if (gnuradio) {
  uint32_t rs2_val = RS2;
  const char *sendipaddr = p->get_osc_sendip();
  size_t osc_sendport = p->get_osc_sendport();
  UdpTransmitSocket transmitSocket( IpEndpointName(sendipaddr, osc_sendport ) );
  char buffer[OUT_BUF_SIZE];
  osc::OutboundPacketStream p( buffer, OUT_BUF_SIZE );
  if (rs1_num == 0 && rs2_num > 0 && rs2_num <= nqregisters) {
    if (!qimm6_flag) {  // qimm6(30) == 1
      for (uint8_t i = 0; i < nqubits ; i++ ) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/InitZero" )
            << (int)rs2_num << (int)i << osc::EndMessage
          << osc::EndBundle;
      }
    } else if (qimm6 >= 0 && qimm6 < nqubits) {
      p << osc::BeginBundleImmediate
        << osc::BeginMessage( "/InitZero" )
          << (int)rs2_num << (int)qimm6 << osc::EndMessage
        << osc::EndBundle;
    }
  } else if (rs1_num > 0 && rs1_num <= nqregisters && rs2_num > 0 && rs2_num <= nqregisters) {
    if (!qimm6_flag) {  // qimm6(30) == 1
      for (uint8_t i = 0; i < nqubits ; i++ ) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/InitZero" )
            << (int)0 << (int)i << osc::EndMessage
          << osc::BeginMessage( "/InitZero" )
            << (int)rs2_num << (int)i << osc::EndMessage
          << osc::BeginMessage( "/H" )
            << (int)0 << (int)i << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)rs2_num << (int)i << (int)0 << (int)i << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)0 << (int)i << (int)rs1_num << (int)i << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)rs1_num << (int)i << (int)rs2_num << (int)i << osc::EndMessage
          << osc::BeginMessage( "/H" )
            << (int)rs1_num << (int)i << osc::EndMessage
          << osc::BeginMessage( "/Mz" )
            << (int)rs1_num << (int)i << osc::EndMessage
          << osc::BeginMessage( "/Mz" )
            << (int)0 << (int)i << osc::EndMessage
          << osc::EndBundle;
      }
    } else {
      if (qimm6 >= 0 && qimm6 < nqubits && target >=0 && target < nqubits) {
        p << osc::BeginBundleImmediate
          << osc::BeginMessage( "/InitZero" )
            << (int)0 << (int)qimm6 << osc::EndMessage
          << osc::BeginMessage( "/InitZero" )
            << (int)rs2_num << (int)qimm6 << osc::EndMessage
          << osc::BeginMessage( "/H" )
            << (int)0 << (int)qimm6 << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)rs2_num << (int)qimm6 << (int)0 << (int)qimm6 << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)0 << (int)qimm6 << (int)rs1_num << (int)target << osc::EndMessage
          << osc::BeginMessage( "/CX" )
            << (int)rs1_num << (int)target << (int)rs2_num << (int)qimm6 << osc::EndMessage
          << osc::BeginMessage( "/H" )
            << (int)rs1_num << (int)target << osc::EndMessage
          << osc::BeginMessage( "/Mz" )
            << (int)rs1_num << (int)target << osc::EndMessage
          << osc::BeginMessage( "/Mz" )
            << (int)0 << (int)qimm6 << osc::EndMessage
          << osc::EndBundle;
      }
    }
  }
  transmitSocket.Send( p.Data(), p.Size() );
}

Qureg qubits = p->get_qubits();
if (rs1_num == 0 && rs2_num > 0 && rs2_num <= nqregisters) {
  if (!qimm6_flag) {  // qimm6(30) == 1
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      fprintf(stderr, "qbit_idx : %d\n", rs2_num * nqubits + i);
      initZeroStateOfSingleQubit(qubits, rs2_num * nqubits + i);
    } 
  } else if (qimm6 >= 0 && qimm6 < nqubits) {
    fprintf(stderr, "qbit_idx : %d\n", rs2_num * nqubits + qimm6);
    initZeroStateOfSingleQubit(qubits, rs2_num * nqubits + qimm6);
  } else {
    // TODO: qimm6 error
    fprintf(stderr, "out of order [qimm6]\n");
    STATE.qstatus |= 1;
  }
} else if (rs1_num > 0 && rs1_num <= nqregisters && rs2_num > 0 && rs2_num <= nqregisters) {
  if (!qimm6_flag) {  // qimm6(30) == 1
    for (uint8_t i = 0; i < nqubits ; i++ ) {
      uint32_t alice = rs1_num * nqubits + i;
      uint32_t bob = rs2_num * nqubits + i;
      fprintf(stderr, "qbit_idx_of_alice : %d\n", alice);
      fprintf(stderr, "qbit_idx_of_bob   : %d\n", bob);
      initZeroStateOfSingleQubit(qubits, i);  // initialize the ancilla
      initZeroStateOfSingleQubit(qubits, bob);  // initialize the qubit of bob
      hadamard(qubits, i);
      controlledNot(qubits, i, bob);  // entangled between ancilla and bob
      controlledNot(qubits, alice, i);
      controlledNot(qubits, i, bob);
      controlledNot(qubits, bob, alice);
      hadamard(qubits,alice);
      measure(qubits, alice);
      measure(qubits, i);
    }
  } else {
    if (qimm6 >= 0 && qimm6 < nqubits && target >=0 && target < nqubits) {
      uint32_t alice = rs1_num * nqubits + target;
      uint32_t bob = rs2_num * nqubits + qimm6;
      fprintf(stderr, "qbit_idx_of_alice : %d\n", alice);
      fprintf(stderr, "qbit_idx_of_bob   : %d\n", bob);
      initZeroStateOfSingleQubit(qubits, qimm6);  // initialize the ancilla
      initZeroStateOfSingleQubit(qubits, bob);  // initialize the qubit of bob
      hadamard(qubits, qimm6);
      controlledNot(qubits, qimm6, bob);  // entangled between ancilla and bob
      controlledNot(qubits, alice, qimm6);
      controlledNot(qubits, qimm6, bob);
      controlledNot(qubits, bob, alice);
      hadamard(qubits, alice);
      measure(qubits, alice);
      measure(qubits, qimm6);
    } else {
      // TODO: qimm6 error
      fprintf(stderr, "out of order [qimm6]\n");
      STATE.qstatus |= 1;
    }
  }
} else {
  // TODO: rs1 error
  fprintf(stderr, "out of order [rs1 or rs2]\n");
  STATE.qstatus |= 1;
}
serialize();
#endif
