/* testpromotion SUPPORT (main_promotion) */
/* charset=ISO8859-1 */
/* lang=C++20 */


#include	<envstandards.h>	/* ordered first to configure */
#include	<sys/types.h>
#include	<cstddef>		/* |unllptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<localmisc.h>



int main() {
	uchar	uc ;
	uchar	u1c, u2c ;

	schar	sc = 0xff ;


	int	si ;


	uc = 0xFF ;

	si = uc - 1 ;
	si += 1 ;

	fprintf(stdout,"uc=%02X si=%08x\n",
		((uint) uc),si) ;

	if (uc == si)
		fprintf(stdout,"equal\n") ;

	else
		fprintf(stdout,"not_equal\n") ;

	si = sc ;
	fprintf(stdout,"sc=%02X si=%08x\n",
		((uint) sc),si) ;

	u1c = 10 ;
	u2c = 5 ;
	si = (u2c - u1c) ;
	fprintf(stdout,"subtraction si=%08x\n",si) ;

	return 0 ;
}
/* end subroutine (main) */


