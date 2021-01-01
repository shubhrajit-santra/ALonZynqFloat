#include <ap_int.h>

void lite_to_stream(ap_uint<9> inform_in, ap_uint<3> *inform1,
		ap_uint<3> *inform2, ap_uint<3> *inform3, ap_uint<3> *inform4)
{
#pragma HLS INTERFACE s_axilite port=inform_in
#pragma HLS INTERFACE axis register both port=inform1
#pragma HLS INTERFACE axis register both port=inform2
#pragma HLS INTERFACE axis register both port=inform3
#pragma HLS INTERFACE axis register both port=inform4

	ap_uint <3> inform_temp1, inform_temp2, inform_temp3, inform_temp4 ;

	inform_temp1 = (inform_in.range(1,0)<<1) | inform_in[8] ;
	inform_temp2 = (inform_in.range(3,2)<<1) | inform_in[8] ;
	inform_temp3 = (inform_in.range(5,4)<<1) | inform_in[8] ;
	inform_temp4 = (inform_in.range(7,6)<<1) | inform_in[8] ;

	*inform1 = inform_temp1 ;
	*inform2 = inform_temp2 ;
	*inform3 = inform_temp3 ;
	*inform4 = inform_temp4 ;
}
