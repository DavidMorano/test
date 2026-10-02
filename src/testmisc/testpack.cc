/* testpack SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 */

/* test program */
/* version %I% last-modified %G% */

#define	CF_CPYSTRX	0		/* |cpystrx()| */

/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */
/* Use is subject to license terms. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<concepts>		/* C++STD */
#include	<typetraits>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<utypedefs.h>		/* LIBU */
#include	<utypealiases.h>	/* LIBU */
#include	<usysdefs.h>		/* LIBU */
#include	<usysrets.h>		/* LIBU */
#include	<sncpyx.h>		/* LIBUC */
#include	<sncpyxw.h>		/* LIBUC */
#include	<localmisc.h>		/* LIBU */

#ifndef	CF_CPYSTRX
#define	CF_CPYSTRX	0		/* |cpystrx()| */
#endif

using std::nullptr_t ;			/* type */
using std::cout ;			/* variable */

template <typename T>
concept ConCharPtr = std::is_same_v<T,const char *> ;

template <typename T>
concept IntType = std::is_same_v<T,int> ;

template<typename ... A>
int thingx(cchar *,int,A ... arg,int) noex {
    return 0 ;
} /* end */
int thingx(cchar *,int,int,ccp,ccp,int) noex {
    return 0 ;
} /* end */

template<typename ... Args>
local int magic(Args ... args) noex {
	return (args && ...) ;
} /* end */

template<typename ... Args>
local int thingw(char *dp,int dl,Args ... args,int other) noex {
	cnullptr	np{} ;
	cint		na = npack(Args) ;
	int		rs = SR_OK ;
	switch (na) {
	case 0:
	    rs = thingx(dp,dl,na,args ...,np,np,np,other) ;
	    break ;
	case 1:
	    rs = thingx(dp,dl,na,args ...,np,np,other) ;
	    break ;
	case 2:
	    rs = thingx(dp,dl,na,args ...,np,other) ;
	    break ;
	case 3:
	    rs = thingx(dp,dl,na,args ...,other) ;
	    break ;
	} /* end switch */
	return rs ;
} /* end */

template<ConCharPtr ... Args,IntType T>
local int cpystrx(char *dp,int dl,Args ... args,T other) noex {
    	cint na = npack(Args) ;
	cout << "strcpyx: o=" << other << " na=" << na << eol ;
	return na ;
} /* end subroutine-template (cpystrx) */

cint		rlen = TIMEBUFLEN ;


/* exported subroutines */

int main(int,con mainv,con mainv) {
	int	ex = EXIT_SUCCESS ;
	int	rs = SR_OK ;
	{
	    int	v1 = 1 ;
	    int	v2 = 2 ;
	    ex = magic(v1,v2) ;
	    if (ex) {
	        cout << "yes\n" ;
	    } else {
	        cout << "no\n" ;
	    }
	} /* end */
	{
		constexpr int dlen = 100 ;
		cint	other = 12 ;
		cchar	*s1 = "Hello " ;
		cchar	*s2 = "world!" ;
		char	dbuf[dlen+1] ;
		sncpy(dbuf,dlen,s1,s2) ;
		cout << dbuf << eol ;
		sncpyw(dbuf,dlen,s1,s2,other) ;
		cout << dbuf << eol ;
	} /* end */
#if	CF_CPYSTRX
	{
	    char rbuf[rlen + 1] ;
	    {
	    cint rs = cpystrx(rbuf,rlen,"Hello"," ","world!","\n",42) ;
	    cout << "main-cpystrx: rs=" << rs << " rbuf=" << rbuf << eol ;
	    }
	} /* end */
#endif /* CF_CPYSTRX */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	} /* end if (error) */
	return ex ;
} /* end subroutine (main) */


