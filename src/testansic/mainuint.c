/* main (TESTUINT) */
/* lang=C20 */

/* see if you have an ANSI compiler or the K&R compiler */
/* version %I% last-modified %G% */


/* revision history:

	= 1999-03-01, David A­D­ Morano

*/

#include	<sys/types.h>
#include	<limits.h>
#include	<stdio.h>


int main(int,const char **,const char **) {
	const int	ui = 0xff000000 ;
	if (ui > UCHAR_MAX) {
	    printf("greater\n") ;
	} else {
	    printf("less-or-equal\n") ;
	}
	return 0 ;
}
/* end subroutine (main) */


