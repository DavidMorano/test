/* teststrnul SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* tes the |strnul(3u)| subroutine */
/* version %I% last-modified %G% */


/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<string>		/* C++STD */
#include	<string_view>		/* C++STD */
#include	<iostream>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<strnul.hh>		/* LIBU */
#include	<localmisc.h>		/* LIBU */


using std::string_view ;		/* type */
using std::cout ;			/* variable */

typedef std::string_view	strview ;

int main(int,con mainv,con mainv) {
	int		ex = 0 ;
	int		c = 0 ;
	cchar	str1[] = "Hello world!" ;
	cchar	str2[] = "Muck raker                   long!" ;
	{
	    strnul	ns ;
	    printf("addr=%p fok=%u\n",ccp(ns),uint(ns.fok)) ;
	}
	{
	    strnul	s(str1,11) ;
	    cchar	*rp ;
	    printf("s=>%s<\n",ccp(s)) ;
	    cout << c++ << " " << str1 << eol ;
	    rp = s ;
	    cout << c++ << " " << rp << eol ;
	    s(str2,7) ;
	    rp = s ;
	    cout << c++ << " " << rp << eol ;
	    rp = s(str1,3) ;
	    cout << c++ << " " << rp << eol ;
	    cout << c++ << " " << s(str1,9) << eol ;
	    cout << c++ << " " << str1 << eol ;
	    cout << c++ << " " << s(str1,40) << eol ;
	    cout << c++ << " " << str2 << eol ;
	    cout << c++ << " " << s(str2,8) << eol ;
	    if (s) {
		strview	sv(str2,10) ;
	        cout << c++ << " " << sv << eol ;
	    } /* end */
	} /* end block */
	return ex ;
} /* end subroutine (main) */


