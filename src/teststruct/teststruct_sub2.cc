/* teststruct_sub2 SUPPORT */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#include	"teststruct_sub.hh"

constexpr substruct	s2 ;

void sub2() noex {
    printf("sub2 s2.a=%d\n",s2.a) ;
} /* end strict */


