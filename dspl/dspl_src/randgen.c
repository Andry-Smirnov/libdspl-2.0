/*
* Copyright (c) 2015-2019 Sergey Bakhurin
* Digital Signal Processing Library [http://dsplib.org]
*
* This file is part of libdspl-2.0.
*
* is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser  General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* DSPL is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*/


#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "dspl.h"
#include "dspl_internal.h"
#include "mt19937.h"



/******************************************************************************
random generator initialization
*******************************************************************************/
int DSPL_API random_init(random_t* prnd, int type)
{
  srand(time(NULL));
  switch(type)
  {
    case RAND_TYPE_MRG32K3A:
      /* MRG32k3a init */  
      prnd->mrg32k3a_x[0] = prnd->mrg32k3a_x[1] = 1.0;
      prnd->mrg32k3a_y[0] = prnd->mrg32k3a_y[1] = prnd->mrg32k3a_y[2] = 1.0;
      prnd->mrg32k3a_x[2] = rand();
      break;
    case RAND_TYPE_MT19937:
      mt19937_init_genrand64((unsigned long long)rand()*rand(), prnd);
      break;
    default:
      return ERROR_RAND_TYPE;
  }
  prnd->type = type;
  return RES_OK;  
}




/******************************************************************************
Uniform random  generator mrg32k3a
*******************************************************************************/
int randu_mrg32k3a (double* u, int n, random_t* prnd)
{
  
  if(!u || !prnd)
    return ERROR_PTR;
  if(n < 1)
    return ERROR_SIZE;

  long z;
  double xn, yn, *x, *y;
  int k;
  
  x = prnd->mrg32k3a_x;
  y = prnd->mrg32k3a_y;
  for(k = 0; k < n; k++)
  {
    /* Component x[n] */
    xn = MRG32K3A_A12 * x[1] - MRG32K3A_A13 * x[2];
    
    z = (long)(xn / MRG32K3A_M1);
    xn -= (double)z * MRG32K3A_M1;
    if (xn < 0.0)
      xn += MRG32K3A_M1;
    
    x[2] = x[1];
    x[1] = x[0];
    x[0] = xn;
    
    /* Component y[n] */
    yn = MRG32K3A_A21 * y[0] - MRG32K3A_A23 * y[2];
    z = (long)(yn / MRG32K3A_M2);
    yn -= (double)z * MRG32K3A_M2;
    if (yn < 0.0)
       yn += MRG32K3A_M2;
     
    y[2] = y[1];
    y[1] = y[0];
    y[0] = yn;
    
    /* Combination */
    u[k] = (xn <= yn) ? ((xn - yn + MRG32K3A_M1) * MRG32K3A_NORM):
                         (xn - yn) * MRG32K3A_NORM;
  }
  return RES_OK;
}







/******************************************************************************
Uniform random numbers generator
*******************************************************************************/
int DSPL_API randu(double* x, int n, random_t* prnd)
{
  int i;
  
  if(!x || !prnd)
    return ERROR_PTR;
  if(n < 0)
    return ERROR_SIZE;
  
  if(prnd)
  {
    switch(prnd->type)
    {
      case RAND_TYPE_MRG32K3A:
        return randu_mrg32k3a(x, n, prnd);
      case RAND_TYPE_MT19937:
        for(i = 0; i < n; i++)
          x[i] = mt19937_genrand64_real1(prnd);        
        return RES_OK;
      default:
        return ERROR_RAND_TYPE;
    }
  }
  else
  {
    if(!x)
      return ERROR_PTR;
    if(n<1)
      return ERROR_SIZE;
    for(i = 0; i < n; i++)
      x[n] = (double)rand()/RAND_MAX;    
  }
  
  return RES_OK;
}




/*******************************************************************************
Gaussian random numbers generator
*******************************************************************************/
int DSPL_API randn(double* x, int n, double mu, double sigma, random_t* prnd)
{
  int k, m;
  double x1[128], x2[128];
  int res;
  if(!x)
    return ERROR_PTR;

   if(n<1)
    return ERROR_SIZE;

  if(sigma < 0.0)
    return ERROR_RAND_SIGMA;

  k=0;
  
  while(k+128 < n)
  {
    if((res = randu(x1, 128, prnd)) != RES_OK)
      goto exit_label;
    if((res = randu(x2, 128, prnd)) != RES_OK)
      goto exit_label;
      
    for(m = 0; m < 128; m++)
    {
      if(x1[m] != 0.0)
      {
        x[k] = sqrt(-2.0*log(x1[m]))*cos(M_2PI*x2[m])*sigma + mu;
        k++;
      }
    }
  }
  
  while(k < n)
  {
    if((res = randu(x1, 1, prnd)) != RES_OK)
      goto exit_label;
    if((res = randu(x2, 1, prnd)) != RES_OK)
      goto exit_label;
    if(x1[1] != 0.0)
    {
      x[k] = sqrt(-2.0*log(x1[1]))*cos(M_2PI*x2[1])*sigma + mu;
      k++;
    }
  }
  
  res = RES_OK;
exit_label:
  return res;
}

