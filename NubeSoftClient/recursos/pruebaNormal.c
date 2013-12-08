# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <math.h>

# include "normal.h"


void test04 ()

/**********************************************************************/
/*
  Purpose:

    TEST04 tests I8_NORMAL_AB.

  Licensing:

    This code is distributed under the GNU LGPL license. 

  Modified:

    02 July 2006

  Author:

    John Burkardt
*/
{
  double a;
  double b;
  long int i;
  long int seed;
  long int seed_init = 123456789;

  printf ( "\n" );
  printf ( "TEST04\n" );
  printf ( "  I8_NORMAL_AB computes pseudonormal integers\n" );
  printf ( "  with mean A and standard deviation B.\n" );

  a = 70.0;
  b = 10.0;
  seed = seed_init;

  printf ( "\n" );
  printf ( "  The mean A = %f\n", a );
  printf ( "  The standard deviation B = %f\n", b );
  printf ( "  The initial seed is %d\n", seed_init );
  printf ( "\n" );

  for ( i = 1; i <= 10; i++ )
  {
    printf ( "  %8d  %8d\n", i, i8_normal_ab ( a, b, &seed ) );
  }

  //return;
}




 int  main(int argc, char  *argv[]){

  timestamp ( );
  printf ( "\n" );
  printf ( "NORMAL_PRB\n" );
  printf ( "  C version\n" );
  printf ( "  Test the NORMAL library.\n" );

  //test03 ( );
  test04 ();
  printf ( "\n" );
  printf ( "NORMAL_PRB\n" );
  printf ( "  Normal end of execution.\n" );
  printf ( "\n" );
  timestamp ( );

  return 0;
}

