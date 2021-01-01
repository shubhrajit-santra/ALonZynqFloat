#include <ap_int.h>

void lite_to_stream(ap_uint<9> inform_in, ap_uint<3> *inform1,
		ap_uint<3> *inform2, ap_uint<3> *inform3, ap_uint<3> *inform4) ;

int main()
{
	ap_uint<9> inform_in ;
	ap_uint<3> inform1, inform2, inform3, inform4 ;

	inform_in = 0;
	lite_to_stream(inform_in, &inform1, &inform2, &inform3, &inform4) ;
	printf("inform1 = %u\n",(unsigned int)inform1) ;
	printf("inform2 = %u\n",(unsigned int)inform2) ;
	printf("inform3 = %u\n",(unsigned int)inform3) ;
	printf("inform4 = %u\n\n",(unsigned int)inform4) ;

	inform_in = 511 ;
	lite_to_stream(inform_in, &inform1, &inform2, &inform3, &inform4) ;
	printf("inform1 = %u\n",(unsigned int)inform1) ;
	printf("inform2 = %u\n",(unsigned int)inform2) ;
	printf("inform3 = %u\n",(unsigned int)inform3) ;
	printf("inform4 = %u\n\n",(unsigned int)inform4) ;

	inform_in = 473 ;
	lite_to_stream(inform_in, &inform1, &inform2, &inform3, &inform4) ;
	printf("inform1 = %u\n",(unsigned int)inform1) ;
	printf("inform2 = %u\n",(unsigned int)inform2) ;
	printf("inform3 = %u\n",(unsigned int)inform3) ;
	printf("inform4 = %u\n\n",(unsigned int)inform4) ;

	inform_in = 278 ;
	lite_to_stream(inform_in, &inform1, &inform2, &inform3, &inform4) ;
	printf("inform1 = %u\n",(unsigned int)inform1) ;
	printf("inform2 = %u\n",(unsigned int)inform2) ;
	printf("inform3 = %u\n",(unsigned int)inform3) ;
	printf("inform4 = %u\n\n",(unsigned int)inform4) ;

	return 0 ;
}
