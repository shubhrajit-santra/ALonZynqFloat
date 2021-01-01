#include <stdio.h>
#include <ap_int.h>

void machine(ap_uint<3> inform, float *R, float *Q) ;

int main()
{
	float Qval, Rval ;

	ap_uint<3> inform = 0 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
 	printf("Simulation Output R = %f\n",Rval) ;

 	inform = 0<<2 | 1<<1 | 1 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

 	inform = 0<<2 | 0<<1 | 1 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

 	inform = 0<<2 | 0<<1 | 1 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

 	inform = 1<<2 | 1<<1 | 1 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

 	inform = 0<<2 | 1<<1 | 1 ;
 	machine(inform,&Rval, &Qval) ;
 	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

	inform = 0<<2 | 0<<1 | 1 ;
	machine(inform,&Rval, &Qval) ;
	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

	inform = 0<<2 | 1<<1 | 1 ;
	machine(inform,&Rval, &Qval) ;
	printf("Simulation Output Q = %f\n",Qval) ;
	printf("Simulation Output R = %f\n",Rval) ;

	printf("\nNo Error\n") ;

	return 0;
}
