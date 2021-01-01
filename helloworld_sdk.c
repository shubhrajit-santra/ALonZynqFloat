#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "math.h"
#include <time.h>
#include <stdlib.h>
#include "xil_cache.h"
#include "xil_types.h"
#include "xtime_l.h"
#include <sleep.h>

#include "xlite_to_stream.h"
#include "xsort.h"

#define A 4

XLite_to_stream ls ;
XSort sort ;

int ls_init(XLite_to_stream *ptr){

	XLite_to_stream_Config *cfgPtr;
    int status;

    cfgPtr = XLite_to_stream_LookupConfig(XPAR_LITE_TO_STREAM_DEVICE_ID);
    if (!cfgPtr) {
        print("ERROR: Lookup failed.\n\r");
        return XST_FAILURE;
    }

    status = XLite_to_stream_CfgInitialize(ptr, cfgPtr);
    if (status != XST_SUCCESS) {
        print("ERROR: Could not initialize.\n\r");
        return XST_FAILURE;
    }

    return status;
}

int sort_init(XSort *ptr){

	XSort_Config *cfgPtr;
    int status;

    cfgPtr = XSort_LookupConfig(XPAR_SORT_DEVICE_ID);
    if (!cfgPtr) {
        print("ERROR: Lookup failed.\n\r");
        return XST_FAILURE;
    }

    status = XSort_CfgInitialize(ptr, cfgPtr);
    if (status != XST_SUCCESS) {
        print("ERROR: Could not initialize.\n\r");
        return XST_FAILURE;
    }

    return status;
}

void runAlgorithm();

int main()
{
    init_platform();

    int status;

    status = ls_init(&ls);
    status = sort_init(&sort);

    runAlgorithm();

    cleanup_platform();
    return 0;
}

void runAlgorithm(){

     double probs[A] = {0.1, 0.3, 0.5, 0.7} ;
    // double probs[A] = {0.65, 0.75, 0.85, 0.95} ;
	// double probs[A] = {0.2, 0.9, 0.4, 0.1} ;
	// double probs[A] = {0.4, 0.5, 0.3, 0.7} ;
	// double probs[A] = {0.4, 0.0, 0.0, 0.7} ;
	// double probs[A] = {0.3, 0.2, 0.7, 0.5} ;
	// double probs[A] = {0.51, 0.52, 0.53, 0.54} ;
	// double probs[A] = {0.11, 0.21, 0.31, 0.41} ;
	// double probs[A] = {0.38, 0.24, 0.77, 0.65} ;

    unsigned int n = 0, ctr = 0 ;

    unsigned int beta[A] = {0,0,0,0} ;
    unsigned int betaV[A] = {0,0,0,0} ;
    unsigned int indices[A] = {0,1,2,3} ;

    unsigned int X1 = 0, X2 = 0, X3 = 0, X4 = 0, T1 = 0, T2 = 0, T3 = 0, T4 = 0 ;
    unsigned int b1, b2, b3, b4, bv1, bv2, bv3, bv4 ;

    unsigned int K = 2;
    unsigned int Lt = A/K ;
    unsigned int toggle = 1 ;

    unsigned int arms, vacant, occupied, order, armnum, tau = 0 ;
    double r = 0 ;

    uint32_t inform = 0 ;

	XLite_to_stream_Set_inform_in_V(&ls,inform) ;

	XTime tprocessorStart, tprocessorEnd ;
	XTime_GetTime(&tprocessorStart);

    for(int i=1; i<=10000 ; i++){

    	// usleep(100);
    	// selected = XCompare_Get_maxQ(&compare);

    	    if (i <= Lt)
    	    {
    	        if (toggle==1)
    	        {
    	        	indices[0] = 0 ;
    	        	indices[1] = 1 ;
    	        	toggle = 0 ;
    	        }
    	        else
    	        {
    	        	indices[0] = 2 ;
					indices[1] = 3 ;
					toggle = 1 ;
    	        }
    	        arms = K ;
    	    }
    	    else
    	    {
    	    	order = XSort_Get_order_V(&sort) ;

    	    	indices[0] = order & 3 ;
    	    	indices[1] = (order>>2) & 3 ;
    	    	indices[2] = (order>>4) & 3 ;
    	    	indices[3] = (order>>6) & 3 ;
    	    	arms = (order>>8) ;

    	    	//if(arms==4)
    	    		//ctr++ ;
    	    }

		    r = (double) rand()/ (double) RAND_MAX;
		    // r = 0.55 ;

	    	beta[0] = 0 ;
	    	beta[1] = 0 ;
	    	beta[2] = 0 ;
	    	beta[3] = 0 ;

	    	betaV[0] = 0 ;
	    	betaV[1] = 0 ;
	    	betaV[2] = 0 ;
	    	betaV[3] = 0 ;

    	    vacant = 0 ;
    	    for (int k = 0; k < arms ; k++)
    	    {
    	        armnum = indices[k] ;
    	        beta[armnum] = 1 ;
    	        if( r < probs[armnum] )
    	        {
    	        	betaV[armnum] = 1 ;
    	        	vacant++ ;
    	        }
    	    }

    	    occupied = arms - vacant ;

    	    if(occupied > K)
			{
    	    	betaV[0] = 0 ;
    	    	betaV[1] = 0 ;
    	    	betaV[2] = 0 ;
    	    	betaV[3] = 0 ;
				vacant = 0 ;
			}

    	    b1 = beta[0] ;
    	    b2 = beta[1] ;
    	    b3 = beta[2] ;
    	    b4 = beta[3] ;

    	    bv1 = betaV[0] ;
    	    bv2 = betaV[1] ;
    	    bv3 = betaV[2] ;
    	    bv4 = betaV[3] ;

    	    tau += vacant ;
    	    X1 += bv1 ;
    	    X2 += bv2 ;
    	    X3 += bv3 ;
    	    X4 += bv4 ;

    	    T1 += b1 ;
    	    T2 += b2 ;
    	    T3 += b3 ;
    	    T4 += b4 ;

			inform  = 1 ;
			inform = ((((((((((((((((inform<<1)|bv4)<<1)|b4)<<1)|bv3)<<1)|b3)<<1)|bv2)<<1)|b2)<<1)|bv1)<<1)|b1) ;

			XLite_to_stream_Set_inform_in_V(&ls,inform) ;

    	    n = n + 1 ;
    }

    XTime_GetTime(&tprocessorEnd);

    printf("X1 = %u		T1 = %u \r\n", X1, T1) ;
    printf("X2 = %u		T2 = %u \r\n", X2, T2) ;
    printf("X3 = %u		T3 = %u \r\n", X3, T3) ;
    printf("X4 = %u		T4 = %u \r\n", X4, T4) ;

    printf("Total Reward: %u",tau) ;
    // printf("\nNon-4 arms: %u",ctr) ;

    printf("\nPS took %.2f us.\n\n", 1.0 * (tprocessorEnd - tprocessorStart) / (COUNTS_PER_SECOND/1000000));

}
