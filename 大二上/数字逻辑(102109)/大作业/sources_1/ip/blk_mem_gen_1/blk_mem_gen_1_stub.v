// Copyright 1986-2016 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2016.2 (win64) Build 1577090 Thu Jun  2 16:32:40 MDT 2016
// Date        : Wed Jan 01 21:56:00 2025
// Host        : JT-20231008PEJJ running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               e:/shuziluoji/chengxu/bighw/test_001/first_try/first_try.srcs/sources_1/ip/blk_mem_gen_1/blk_mem_gen_1_stub.v
// Design      : blk_mem_gen_1
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a100tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "blk_mem_gen_v8_3_3,Vivado 2016.2" *)
module blk_mem_gen_1(clka, addra, douta)
/* synthesis syn_black_box black_box_pad_pin="clka,addra[18:0],douta[11:0]" */;
  input clka;
  input [18:0]addra;
  output [11:0]douta;
endmodule
