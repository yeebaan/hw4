#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
#include <cmath>
#include <iomanip>
using namespace sc_core;

#include <tlm>
#include <tlm_utils/simple_target_socket.h>

#include "filter_def.h"

struct SobelFilter : public sc_module {
  tlm_utils::simple_target_socket<SobelFilter> tsock;

  using tb_to_dut_t = sc_bv<5*3*8>;
  using dut_to_tb_t = sc_bv<8>;
  sc_fifo<tb_to_dut_t> i_tb_to_dut;
  sc_fifo<dut_to_tb_t> o_dut_to_tb;

  SC_HAS_PROCESS(SobelFilter);

  SobelFilter(sc_module_name n): 
    sc_module(n), 
    tsock("t_skt"), 
    base_offset(0) 
  {
    tsock.register_b_transport(this, &SobelFilter::blocking_transport);
    SC_THREAD(do_filter);
  }

  ~SobelFilter() {
	}

  int val[MASK_N];
  unsigned int base_offset;

  auto do_filter() {
      wait(CLOCK_PERIOD * 1, SC_NS);
      std::array<sc_uint<8>, 25> buffer{};
      while (true) {
          tb_to_dut_t input{i_tb_to_dut.read()};
          for (auto i{}; i < 20; i++) {
              buffer[i] = buffer[i + 5];
          }
          for (auto i{}; i < 5; i++) {
              buffer[20 + i] =
                  (sc_uint<8>(sc_bv<8>(input.range(24 * i + 23, 24 * i + 16))) +
                  sc_uint<8>(sc_bv<8>(input.range(24 * i + 15, 24 * i + 8))) +
                  sc_uint<8>(sc_bv<8>(input.range(24 * i + 7, 24 * i)))) /
                  3;
          }
          o_dut_to_tb.write((buffer[0] * 1 + buffer[1] * 4 + buffer[2] * 7 +
                            buffer[3] * 4 + buffer[4] * 1 + buffer[5] * 4 +
                            buffer[6] * 16 + buffer[7] * 26 + buffer[8] * 16 +
                            buffer[9] * 4 + buffer[10] * 7 + buffer[11] * 26 +
                            buffer[12] * 41 + buffer[13] * 26 + buffer[14] * 7 +
                            buffer[15] * 4 + buffer[16] * 16 + buffer[17] * 26 +
                            buffer[18] * 16 + buffer[19] * 4 + buffer[20] * 1 +
                            buffer[21] * 4 + buffer[22] * 7 + buffer[23] * 4 +
                            buffer[24] * 1) /
                            273);
          wait(CLOCK_PERIOD * 1, SC_NS);
      }
  }

  void blocking_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay){
    if (tlm::TLM_READ_COMMAND == payload.get_command()) {
      payload.get_data_ptr()[0] = o_dut_to_tb.read();
    }
    if (tlm::TLM_READ_COMMAND == payload.get_command()) {
      
    }
    tlm::tlm_command cmd = payload.get_command();
    sc_dt::uint64 addr = payload.get_address();
    unsigned char *data_ptr = payload.get_data_ptr();

    addr -= base_offset;


    // cout << (int)data_ptr[0] << endl;
    // cout << (int)data_ptr[1] << endl;
    // cout << (int)data_ptr[2] << endl;
    word buffer;

    switch (cmd) {
      case tlm::TLM_READ_COMMAND:
        // cout << "READ" << endl;
        switch (addr) {
          case SOBEL_FILTER_RESULT_ADDR:
            buffer.uint = o_result.read();
            break;
          default:
            std::cerr << "READ Error! SobelFilter::blocking_transport: address 0x"
                      << std::setfill('0') << std::setw(8) << std::hex << addr
                      << std::dec << " is not valid" << std::endl;
          }
        data_ptr[0] = buffer.uc[0];
        data_ptr[1] = buffer.uc[1];
        data_ptr[2] = buffer.uc[2];
        data_ptr[3] = buffer.uc[3];
        break;
      case tlm::TLM_WRITE_COMMAND:
        // cout << "WRITE" << endl;
        switch (addr) {
          case SOBEL_FILTER_R_ADDR:
            i_r.write(data_ptr[0]);
            i_g.write(data_ptr[1]);
            i_b.write(data_ptr[2]);
            break;
          default:
            std::cerr << "WRITE Error! SobelFilter::blocking_transport: address 0x"
                      << std::setfill('0') << std::setw(8) << std::hex << addr
                      << std::dec << " is not valid" << std::endl;
        }
        break;
      case tlm::TLM_IGNORE_COMMAND:
        payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
      default:
        payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return;
      }
      payload.set_response_status(tlm::TLM_OK_RESPONSE); // Always OK
  }
};
#endif
