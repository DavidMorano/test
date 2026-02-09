/* teststruct SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<bfile.h>
#include	<localmisc.h>


/* external subroutines */

extern struct thing	sub() ;


/* private module data structures */

struct thing {
	int	a, b ;
} ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) {
	bfile	outfile, *ofp = &outfile ;
	thing	mine = { 0, 0 } ;
	thing	yours = { 0, 0 } ;
	int	rs = SR_OK  ;

	(void) bopen(ofp,BFILE_STDOUT,"dwct",0666) ;

	bprintf(ofp,"entered\n") ;

	mine = sub(1,2) ;

	bprintf(ofp,"mine= %d %d \n",mine.a,mine.b) ;

	yours = sub(3,4) ;

	bprintf(ofp,"mine= %d %d \n",mine.a,mine.b) ;


	bclose(ofp) ;

	return 0 ;
}
/* end subroutine (main) */


