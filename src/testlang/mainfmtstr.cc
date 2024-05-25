/* main SUPPOER (mainfmtstr) */
/* lang=C++20 */


#include	<envstandards.h>	/* MUST be first to configure */
#include	<sys/types.h>
#include	<sys/param.h>
#include	<envstandards.h>	/* ordered first to configure */
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<clanguage.h>
#include	<localmisc.h>
#include	<exitcodes.h>
#include	<localmisc.h>


/* local defines */


/* exported variables */


/* exported subroutines */

int main(int argc,mainv,mainv) {
	bfile	outfile, *ofp = &outfile ;
	int	rs ;
	int	rs1 ;
	int	ex = EX_OK ;
	if ((rs = bopen(ofp,BFILE_STDOUT,"dwct",0666)) >= 0) {
	    unsigned long long	a, r ;
	    unsigned int	ui, uii ;
	    int	i, ii ;

	a = 0xFFFFFFFFFFFFFF01ULL ;

	i = 7 ;
	ui = i ;
	ii = (~ i) ;
	uii = (~ ui) ;

	bprintf(ofp,"ii=%016llX\n",(long long) uii) ;

	bprintf(ofp,"uii=%016llX\n",((unsigned long long) ii)) ;

	r = ((unsigned long long) ii) ;
	bprintf(ofp,"r1=%016llX\n",r) ;

	r = (long long) (~ ui) ;
	bprintf(ofp,"r2=%016llX\n",r) ;

	    rs1 = bclose(ofp) ;
	    if (rs >= 0) rs = rs1 ;
	} /* end if (bfile) */
	ex = (rs >= 0) ? EX_OK : EX_DATAERR ;
	return ex ;
}
/* end subroutine (main) */


