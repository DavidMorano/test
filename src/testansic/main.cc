/* main */
/* lang=C20 */

/* see if you have an ANSI compiler or the K&R compiler */
/* version %I% last-modified %G% */


/* revision history:

	= 1989-03-01, David A­D­ Morano
	This was written way back when the ANSI-standardized C-language compiler
	first came out. I am testing how the new compiler messes up integral
	promotions in the case of signed inetegers meeting unsigned-integers.

*/


#include	<cstdio>

int main(int,const char **,const char **) {
	int		iw = -1 ;
	unsigned short	us = 1 ;
	const char	*fmt ;
	if (us < iw) {
	    fmt = "you have the correct K&R compiler\n" ;
	    printf(fmt) ;
	} else {
	    fmt = "you have the bad ANSI conforming compiler\n" ;
	    printf(fmt) ;
	}
	return 0 ;
}
/* end subroutine (main) */


