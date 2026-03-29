/* bit HEADER */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* bitmanip MODULE (primary-module-interface)*/
/* version %I% last-modified %G% */


/* revision history:

	= 1998-03-85, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	BIT_INCLUDE
#define	BIT_INCLUDE
#ifdef	__cplusplus /* C++ only! */


#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |CHAR_BIT| */
#include	<cstddef>
#include	<cstdlib>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>


template<typename T>
constexpr inline bool bit(T v,int n) noex {
	return !!((v >> n) & 1) ;
} /* end subroutine (bit) */


#endif /* __cplusplus (C++ only) */
#endif /* BIT_INCLUDE */


