/* cfdig HEADER */
/* charset=ISO8859-1 */
/* lang=C20 */

/* convert a decimal digit string to its binary integer value */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-11-01, David A­D­ Morano
	This subroutine was written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	CFDIG_INCLUDE
#define	CFDIG_INCLUDE


#include	<envstandards.h>	/* ordered first to configure */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<stdintx.h>		/* LIBU */


EXTERNC_begin

extern int cfdigsi	(cchar *,int,int,sint *)	noex ;
extern int cfdigsl	(cchar *,int,int,slong *)	noex ;
extern int cfdigsll	(cchar *,int,int,slonglong *)	noex ;

extern int cfdigui	(cchar *,int,int,uint *)	noex ;
extern int cfdigul	(cchar *,int,int,ulong *)	noex ;
extern int cfdigull	(cchar *,int,int,ulonglong *)	noex ;

inline int cfdigi(cchar *sp,int sl,int b,int *rp)	noex {
	return cfdigsi(sp,sl,b,rp) ;
} /* end */
inline int cfdigl(cchar *sp,int sl,int b,long *rp)	noex {
	return cfdigsl(sp,sl,b,rp) ;
} /* end */
inline int cfdigll(cchar *sp,int sl,int b,longlong *rp)	noex {
	return cfdigsll(sp,sl,b,rp) ;
} /* end */

EXTERNC_end

#if	__cplusplus

inline int cfdig(cchar *sp,int sl,int b,sint *rp)	noex {
	return cfdigsi(sp,sl,b,rp) ;
} /* end */
inline int cfdig(cchar *sp,int sl,int b,slong *rp)	noex {
	return cfdigsl(sp,sl,b,rp) ;
} /* end */
inline int cfdig(cchar *sp,int sl,int b,slonglong *rp)	noex {
	return cfdigsll(sp,sl,b,rp) ;
} /* end */

inline int cfdig(cchar *sp,int sl,int b,uint *rp)	noex {
	return cfdigui(sp,sl,b,rp) ;
} /* end */
inline int cfdig(cchar *sp,int sl,int b,ulong *rp)	noex {
	return cfdigul(sp,sl,b,rp) ;
} /* end */
inline int cfdig(cchar *sp,int sl,int b,ulonglong *rp)	noex {
	return cfdigull(sp,sl,b,rp) ;
} /* end */

#endif /* __cplusplus */


#endif /* CFDIG_INCLUDE */


