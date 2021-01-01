#include <hls_math.h>
#include <math.h>
#include <ap_int.h>

// inform N_T_X_VACANT_ARMS
void machine(ap_uint<3> inform, float *R, float *Q){
#pragma HLS INTERFACE axis register both port=R
#pragma HLS INTERFACE axis register both port=Q
#pragma HLS INTERFACE axis register both port=inform

	static float X ;
	static float T ;
	static float N ;

	if(inform[0]==0){
		X = 1;
		T = 1;
		N = 4;
	}
	else{
		N += 1;

		if(inform[1]==1)
		{
			T += 1 ;

			if(inform[2]==1)
				X += 1;
		}
	}

	float R_in, Q_in;
	R_in = float(X/T) ;
	Q_in = R_in + (float) hls::sqrt((float)hls::log(N)/T);

	*R = R_in ;
	*Q = Q_in ;
}
