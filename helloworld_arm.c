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

#define A 4

void runAlgorithm();

int main()
{
    init_platform();

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
    unsigned int n = 0 ;

    unsigned int X1 = 1, X2 = 1, X3 = 1, X4 = 1, T1 = 1, T2 = 1, T3 = 1, T4 = 1 ;

    //double pr[A] = {1,1,1,1} ;
    double prs[A] = {1,1,1,1} ;
    unsigned int beta[A] = {0,0,0,0} ;
    unsigned int betaV[A] = {0,0,0,0} ;
    unsigned int indices[A] = {0,1,2,3} ;
    float Q[A], swapQ, logn, Q1, Q2, Q3, Q4 ;

    unsigned int K = 2;
    unsigned int Lt = A/K ;
    unsigned int toggle = 1 ;

    unsigned int arms, vacant, occupied, armnum, temp1, tau = 0 ;
    double r = 0, temp ;
    float P1, P2, P3 ;

    float m12, m13, m14, m23, m24, m34, sum1, sum2, sum3, w1, w2, w3, w4 ;

    XTime tprocessorStart, tprocessorEnd ;
	XTime_GetTime(&tprocessorStart);

    for(int i=1; i<=10000 ; i++){

    	// usleep(100);
    	// selected = XCompare_Get_maxQ(&compare);

    	if (i <= Lt)
    	{
    		arms = K ;

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
    	}
    	else
    	{
			for (int p = 0 ; p<A-1 ; p++)
			{
				for (int q = 0; q < A-1-p; q++)
				{
					if (prs[q] < prs[q+1])
					{
						temp = prs[q] ;
						prs[q] = prs[q+1] ;
						prs[q+1] = temp ;
					}
				}
			}

			w1 = prs[0] ;
			w2 = prs[1] ;
			w3 = prs[2] ;
			w4 = prs[3] ;

			P1 = w1 + w2 ;
			P2 = P1 + w3 ;

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

			logn = log(n) ;
			Q1 = (float)X1/(float)T1 + (float)sqrt(logn/(float)T1) ;
			Q2 = (float)X2/(float)T2 + (float)sqrt(logn/(float)T2) ;
			Q3 = (float)X3/(float)T3 + (float)sqrt(logn/(float)T3) ;
			Q4 = (float)X4/(float)T4 + (float)sqrt(logn/(float)T4) ;

			Q[0] = Q1 ;
			Q[1] = Q2 ;
			Q[2] = Q3 ;
			Q[3] = Q4 ;

			indices[0] = 0 ;
			indices[1] = 1 ;
			indices[2] = 2 ;
			indices[3] = 3 ;

			for( int p = 0 ; p < A-1 ; p++ )
			{
				for( int q = 0 ; q < A-1-p ; q++ )
				{
					if(Q[q]<Q[q+1])
					{
						swapQ = Q[q] ;
						Q[q] = Q[q+1] ;
						Q[q+1] = swapQ ;

						temp1 = indices[q] ;
						indices[q] = indices[q+1] ;
						indices[q+1] = temp1 ;
					}
				}
			}
    	}

		    r = (double) rand()/ (double) RAND_MAX;

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

    	    tau += vacant ;
    	    X1 += betaV[0] ;
    	    X2 += betaV[1] ;
    	    X3 += betaV[2] ;
    	    X4 += betaV[3] ;

    	    T1 += beta[0] ;
    	    T2 += beta[1] ;
    	    T3 += beta[2] ;
    	    T4 += beta[3] ;

    	    prs[0] = (double)X1/(double)T1 ;
    	    prs[1] = (double)X2/(double)T2 ;
    	    prs[2] = (double)X3/(double)T3 ;
    	    prs[3] = (double)X4/(double)T4 ;

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

