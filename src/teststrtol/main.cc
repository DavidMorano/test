/* main (teststrtol) */


#include	<sys/types.h>
#include	<cstdlib>
#include	<cstring>



int main()
{
	long	val = 0 ;

	const char	*a = "  -21 b6" ;


	val = strtol(a,NULL,10) ;

	printf("val=%ld\n",val) ;

	return 0 ;
}
/* end subroutine (main) */


