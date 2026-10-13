/* main */


#include	<sys/types.h>
#include	<math.h>
#include	<bfile.h>
#include	<localmisc.h>


/* local defines */

#include	<bfile.h>


/* local variables */

local int	b[4][4] ;


/* exported subroutines */

int main(int argc,cchar **argv,cchar **envv) {
	bfile		ofile, *ofp = &ofile ;
	double		value = HUGE ; /* an official define! */
	int		rs ;
	int		i = 1 ;
	cchar	*str = "stringer" ;

	if ((rs = nprintf("here.err","main: str=%t\n",str,5)) >= 0) {
	    cchar	*ofn = BFILE_STDOUT ;
	    if ((rs = bopen(ofp,ofn,"wct",0666)) >= 0) {

	        bprintf(ofp,"%6.2f\n",value) ;
	        bprintf(ofp,"outside\n") ;

		{
		int i = 0 ;
		bprintf(ofp,"i=%d\n",i) ;
		}

	        bclose(ofp) ;
	    } /* end if (file) */
	} /* end if (nprintf) */

	return 0 ;
}
/* end subroutine (main) */


