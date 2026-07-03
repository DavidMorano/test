/* testvla_main SUPPORT (testvla) */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test theVLAfeature in the C language */
/* version %I% last-modified %G% */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<usyscalls.h>		/* LIBU */
#include	<localmisc.h>		/* LIBU */

#define	NA	10

/* forward */

local int	sub(int *,int) ;

int main(int,con mainv,con mainv) {
	int	a[NA + 1] ;
	int	sum ;
	int i ; /* used-afterwards */
	for (i = 0 ; i < NA ; i += 1) {
		a[i] = i ;
	}
	a[i] = 0 ;
	sum = sub(a,NA) ;
	printf("sum=%u\n",sum) ;
	return 0 ;
} /* end subroutine */


/* local subroutines */

int sub(int *a,int n) noex {
	int	sum = 0 ;
	int	as[n + 1] ;
	for (int i = 0 ; i < n ; i += 1) {
		as[i] = a[i] ;
		if (a[i] > 0) {
			as[i] -= 1 ;
		}
	} /* end for */
	for (int i = 0 ; i < n ; i += 1) {
		sum += a[i] ;
		printf("a[%u]=%u\n",i,as[i]) ;
	}
	return sum ;
} /* end subroutine (sub) */


