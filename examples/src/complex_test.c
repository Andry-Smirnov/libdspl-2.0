#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dspl.h"

int main()
{
  void* handle;           // DSPL handle
  handle = dspl_load();   // Load DSPL function
  
  complex_t x[3] = {{1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}};
  complex_t y[3];
  int k;
  
  printf("\n\nacos_cmplx\n---------------------------------\n");
  acos_cmplx(x, 3, y);  
  for(k = 0; k < 3; k++)
    printf("acos_cmplx(%.1f%+.1fj) = %.3f%+.3fj\n", 
            RE(x[k]), IM(x[k]), RE(y[k]), IM(y[k]));

  printf("\n\nasin_cmplx\n---------------------------------\n");
  asin_cmplx(x, 3, y);  
  for(k = 0; k < 3; k++)
    printf("asin_cmplx(%.1f%+.1fj) = %.3f%+.3fj\n", 
            RE(x[k]), IM(x[k]), RE(y[k]), IM(y[k]));

  printf("\n\ncos_cmplx\n---------------------------------\n");
  cos_cmplx(x, 3, y);  
  for(k = 0; k < 3; k++)
    printf("cos_cmplx(%.1f%+.1fj) = %9.3f%+9.3fj\n", 
            RE(x[k]), IM(x[k]), RE(y[k]), IM(y[k]));
  
  
  dspl_free(handle);      // free dspl handle
  
  return 0;
}


