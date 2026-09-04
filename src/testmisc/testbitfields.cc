/* testbitfields SUPPORT */
/* charset=ISO8859-1 */
/* lang=C99 */

/* test program */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */



struct bitfields {
	unsigned int	a[50]:1 ;
} ;

int main(int argc,con mainv argv,con mainv envv) {
	struct bitfields	bf ;
	(void) argc ;
	(void) argv ;
	(void) envv ;


	return 0 ;
} /* end subroutine (main) */


