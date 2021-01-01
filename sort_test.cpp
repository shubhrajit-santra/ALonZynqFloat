#include "stdio.h"
#include "ap_int.h"

void sort(float R1, float R2, float R3, float R4, float Q1, float Q2, float Q3, float Q4, ap_uint <11> *order) ;

int main()
{
	unsigned int val ;
	ap_uint <11> sim_out ;

	float Q1 = 7.479, Q2 = 7.351, Q3 = 7.4903, Q4 = 7.352 ;
	float R1 = 0.9, R2 = 0.1, R3 = 0.0, R4 = 0.8 ;

 	sort(R1,R2,R3,R4,Q1,Q2,Q3,Q4,&sim_out) ;

 	val = sim_out.range(1,0) ;
 	printf("Simulation Output = %u\n",val) ;
 	val = sim_out.range(3,2) ;
	printf("Simulation Output = %u\n",val) ;
	val = sim_out.range(5,4) ;
	printf("Simulation Output = %u\n",val) ;
	val = sim_out.range(7,6) ;
	printf("Simulation Output = %u\n",val) ;
	val = sim_out.range(10,8) ;
	printf("arms = %u\n",val) ;

	printf("NO Error\n") ;

	return 0;
}
