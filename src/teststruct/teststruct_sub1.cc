/* teststruct_sub1 SUPPORT */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"teststruct_sub.hh"

constexpr substruct	s1 ;

void sub1() noex {
    printf("sub1 s1.a=%d\n",s1.a) ;
} /* end subroutine */


