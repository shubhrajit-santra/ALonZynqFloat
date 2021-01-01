
#include "ap_int.h"

void sort(float R1, float R2, float R3, float R4, float Q1, float Q2, float Q3, float Q4, ap_uint<11> *order)
{
#pragma HLS INTERFACE s_axilite port=order
#pragma HLS INTERFACE axis register both port=R1
#pragma HLS INTERFACE axis register both port=R2
#pragma HLS INTERFACE axis register both port=R3
#pragma HLS INTERFACE axis register both port=R4
#pragma HLS INTERFACE axis register both port=Q1
#pragma HLS INTERFACE axis register both port=Q2
#pragma HLS INTERFACE axis register both port=Q3
#pragma HLS INTERFACE axis register both port=Q4

	unsigned int indices[4] = {0,1,2,3} ;
	unsigned int temp1 ;
	float Q[4] ;
	float R[4] ;
	float temp, temp2 ;

	Q[0] = Q1 ;
    Q[1] = Q2 ;
	Q[2] = Q3 ;
    Q[3] = Q4 ;

	for( int i = 0 ; i < 3 ; i++ )
	{
		for( int j = 0 ; j < 3-i ; j++ )
		{
			if(Q[j]<Q[j+1])
			{
				temp = Q[j] ;
				Q[j] = Q[j+1] ;
				Q[j+1] = temp ;

				temp1 = indices[j] ;
				indices[j] = indices[j+1] ;
				indices[j+1] = temp1 ;
			}
		}
	}

	R[0] = R1 ;
	R[1] = R2 ;
	R[2] = R3 ;
	R[3] = R4 ;

	for( int k = 0 ; k < 3 ; k++ )
	{
		for( int l = 0 ; l < 3-k ; l++ )
		{
			if(R[l]<R[l+1])
			{
				temp2 = R[l] ;
				R[l] = R[l+1] ;
				R[l+1] = temp2 ;
			}
		}
	}

	unsigned int arms = 0 ;
	float P1, P2, P3, w1, w2, w3, w4 ;

	w1 = R[0] ;
	w2 = R[1] ;
	w3 = R[2] ;
	w4 = R[3] ;

	P1 =  w1 + w2 ;
	P2 =  P1 + w3 ;

	float m12, m13, m14, m23, m24, m34, sum1, sum2, sum3 ;

	m12 = w1*w2 ;
	m13 = w1*w3 ;
	m14 = w1*w4 ;
	m23 = w2*w3 ;
	m24 = w2*w4 ;
	m34 = w3*w4 ;

	sum1 = m12*m34 ;
	sum2 = m12 + m13 + m14 + m23 + m24 + m34 ;
	sum3 = (m12*(w3 + w4)) + (m34*(w1 + w2)) ;

	P3 = (4*sum1) + (2*sum2) - (3*sum3) ;

	if(P1>=P2 && P1>=P3)
		arms = 2 ;
	else if(P2>=P1 && P2>=P3)
		arms = 3 ;
	else
		arms = 4 ;

	ap_uint<11> order_in ;
	order_in = (((((((arms<<2)|indices[3])<<2)|indices[2])<<2)|indices[1])<<2)|indices[0] ;

	*order = order_in ;
}
