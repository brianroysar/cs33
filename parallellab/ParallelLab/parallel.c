//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Brian Roysar
 * UCLA ID : 205394798
 * Email : brianroysar@ucla.edu
 */

#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#include "utils.h"

double work_it_par(long *old, long *new, long *super, long *simple, long *fibonacci) {
  int i, j, k;
  int u, v, w;
  int ton = 0;
  long compute_it, moving_average = 0;
  double pi, pi2, x , y, sum, step = 0.0;
  long dot_product=0;
  long nCirc=0;
  long aggregate=1.0;
  double r=1.0;
  int was_smart = 16;

  for(i=0; i<DIM-1;i++)
  {
    super[i] += simple[i];
  }

  for(i=0; i<DIM-1;i++)
  {
    dot_product += super[i]*simple[i];
    
//    for(ton=i;ton<DIM-1-WINDOW_SIZE;ton++)
//    {
//      moving_average += simple[ton];
//    }
  }

  fibonacci[0] = 1;
  fibonacci[1] = 1;
  for(i=2; i<DIM-1;i++)
  {
    fibonacci[i]=fibonacci[i-1]+fibonacci[i-2];
  }
    
    int a_secret = 5;
    printf("\n A secret is: %d",obfuscate_obfuscate_obfuscate(a_secret));

  step = 1.0 / NUM_STEPS;
  for (i=0;i<NUM_STEPS; i++)
  {
    x = (i+0.5)*step;
    sum = sum + 4.0/(1.0+x*x);
  }
  pi = step * sum;
  printf("\n %d trials, Riemann flavored pi is %f \n",NUM_STEPS, pi); 
  
  for(i=0;i<NUM_TRIALS; i++)
  {
    x = (random()%10000000)/10000000.0; 
    y = (random()%10000000)/10000000.0;
    if (( x*x + y*y) <= r*r) {
      nCirc++;
    }
  } 
  pi2 = 4.0 * ((double)nCirc/(double)NUM_TRIALS);
  printf("\n %d trials, Monte-Carlo flavored pi is %f \n",NUM_TRIALS, pi2); 


    int dimsquared = DIM*DIM;
    int dimMinusOne = DIM-1;
    
    int master = dimsquared+DIM+1;
    int wntf = we_need_the_func();
    int gtf = gimmie_the_func();
  for (i=1; i<dimMinusOne; i++) {
    for (j=1; j<dimMinusOne; j++) {
      for (k=1; k<dimMinusOne; k++) {
        aggregate += (old[master] * wntf) / gtf;
        master++;
      }
        master+=2;
    }
      master+=DIM*2;
  }

  printf("AGGR:%ld\n",aggregate);

    int id = dimsquared;
    int jd = DIM;
    int idpos, idneg, jdpos, jdneg;
  for (i=1; i<dimMinusOne; i++) {
      idpos = id+dimsquared;
      idneg = id-dimsquared;
    for (j=1; j<dimMinusOne; j++) {
        jdpos = jd+DIM;
        jdneg = jd-DIM;
      for (k=1; k<dimMinusOne; k++) {
          new[id+jd+k] = (old[id + jd + k] + old[id + jd + k+1] + old[id + jd + k-1]);
          new[id+jd+k] += (old[id + jdpos + k] + old[id + jdpos + k+1] + old[id + jdpos + k-1]);
          new[id+jd+k] += (old[id + jdneg + k] + old[id + jdneg + k+1] + old[id + jdneg + k-1]);
          
          new[id+jd+k] += (old[idpos + jd + k] + old[idpos + jd + k+1] + old[idpos + jd + k-1]);
          new[id+jd+k] += (old[idpos + jdpos + k] + old[idpos + jdpos + k+1] + old[idpos + jdpos + k-1]);
          new[id+jd+k] += (old[idpos + jdneg + k] + old[idpos + jdneg + k+1] + old[idpos + jdneg + k-1]);
          
          new[id+jd+k] += (old[idneg + jd + k] + old[idneg + jd + k+1] + old[idneg + jd + k-1]);
          new[id+jd+k] += (old[idneg + jdpos + k] + old[idneg + jdpos + k+1] + old[idneg + jdpos + k-1]);
          new[id+jd+k] += (old[idneg + jdneg + k] + old[idneg + jdneg + k+1] + old[idneg + jdneg + k-1]);
          
          new[id+jd+k]/=27;
      }
        jd += DIM;
    }
      id += dimsquared;
      jd = DIM;
  }

  for (i=1; i<DIM-1; i++) {
    for (j=1; j<DIM-1; j++) {
      for (k=1; k<DIM-1; k++) {
        u=(new[i*DIM*DIM+j*DIM+k]/100);
        if (u<=0) u=0;
        if (u>=9) u=9;
        histogrammy[u]++;
      }
    }
  }
  return (double) (dot_product+moving_average+pi+pi2);


}
