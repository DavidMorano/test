/* testqsort_main SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* version %I% last-modified %G% */
/* test the |qsort(3c)| subroutine */

#define	CF_DEBUGS	1
#define	CF_VSTRSORT	0	/* use 'vstrsort()' instead of 'qsort(3c)' */
#define	CF_VSTRCMP	0	/* which sort function */

/******************************************************************************

  	Description:
	This little program shows a bad (core-dump quality) bug in
	the Solaris |qsort(3c)| subroutine!

******************************************************************************/

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| */
#include	<cstdio>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<cfdec.h>
#include	<vstrcmp.h>
#include	<vstrkeycmp.h>
#include	<localmisc.h>


/* external variables */


/* local variables */

constexpr cpcchar	kstrs[] = {
	"_=/bin/cat",
	"PATH=/bin",
	nullptr
} ; /* end array (kstrs) */

cbool		f_vstrsort = false ;


/* exported variables */


/* exported subroutines */

int main(int,mainv,mainv) neox {
    	cnullptr	np{} ;
	cnithrow	nt{} ;
	int	rs = SR_OK ;
	int	fd_debug = -1 ;
	int	(*fn)(cvoid *,cvoid *) ;
	char	*cp ;

#if	CF_DEBUGS
	if ((cp = getenv(VARDEBUGFD1)) == nullptr) {
	    cp = getenv(VARDEBUGFD2) ;
	}
	if (cp && (cfdeci(cp,-1,&fd_debug) >= 0)) {
	    debugsetfd(fd_debug) ;
	}
#endif /* CF_DEBUGS */

	fprintf(stdout,"unsorted\n") ;
	for (int i = 0 ; kstrs[i] != nullptr ; i += 1) {
		fprintf(stdout,"a[%d]=>%s<\n",i,kstrs[i]) ;
	}

#if	CF_VSTRCMP
	fn = vstrcmp ;
#else
	fn = vstrkeycmp ;
#endif

	cint dlen = lenstrarr(kstrs) ;
	if (char *datarr ; (datarr = new(nt) char [dlen + 1]) != np) {
	    for (int i = 0 ; kstrs[i] ; i += 1) {
		datarr[i] = kstrs[i] ;
	    }
#if	CF_VSTRSORT
	vstrsort(datarr,dlen,fn) ;
#else
	qsort(dataerr,dlen,sizeof(char *),fn) ;
#endif
	fprintf(stdout,"sorted\n") ;
	for (int i = 0 ; array[i] != nullptr ; i += 1) {
		fprintf(stdout,"a[%d]=>%s<\n",i,kstrs[i]) ;
	}

	    delete [] datarr ;
	} /* end if (new-char) */
}
/* end subroutine (main) */


