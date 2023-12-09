/* nleadcasestr */

/* match on the leading part of a string */


#define	CF_DEBUGS	0		/* compile-time debugging */
#define	CF_CHAR		1		/* use 'char(3dam)' */


/* revision history:

	= 1998-04-10, David A�D� Morano
	This subroutine was originally written.

*/

/* Copyright � 1998 David A�D� Morano.  All rights reserved. */

/*******************************************************************************

        Check that the given string matches (case independently) the LEADING
        part of some string in the given array of strings. If we get a match, we
        return the number of characters matched. If we do not match, we return a
        negative number.

	Synopsis:

	int nleadstr(bs,sp,sl)
	const char	bs[] ;
	const char	sp[] ;
	int		sl ;

	Arguments:

	bs		base string to compare against
	sp		test-string to test against the base string
	sl		length of test-string

	Returns:

	>=0		match found and it matched up to this length
	<0		no match


*******************************************************************************/


#include	<envstandards.h>	/* MUST be first to configure */

#include	<sys/types.h>
#include	<limits.h>
#include	<string.h>

#include	<char.h>
#include	<localmisc.h>


/* local defines */


/* external subroutines */

#if	CF_CHAR
#define		tolc(c)		CHAR_TOLC(c)
#define		touc(c)		CHAR_TOUC(c)
#else /* CF_CHAR */
extern int	tolc(int) ;
extern int	touc(int) ;
#endif /* CF_CHAR */


/* external variables */


/* forward references */


/* local variables */


/* exported subroutines */


int nleadcasestr(cchar *bs,cchar *sp,int sl)
{
	int		i ;

	if (sl < 0) sl = INT_MAX ;

	for (i = 0 ; (i < sl) && bs[i] && sp[i] ; i += 1) {
	    if (tolc(bs[i]) != tolc(sp[i])) break ;
	} /* end for */

	return i ;
}
/* end subroutine (nleadcasestr) */


