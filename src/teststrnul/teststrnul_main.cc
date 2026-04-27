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
#include	<cstdlib>
#include	<cstdio>
#include	<string>
#include	<string_view>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<strnul.hh>
#include	<localmisc.h>


using std::cout ;
using std::string_view ;

typedef std::string_view	strview ;

int main(int,con mainv,con mainv) {
	int		ex = 0 ;
	int		c = 0 ;
	constexpr cchar	sp1[] = "Hello world!" ;
	constexpr cchar	sp2[] = "Muck raker                   long!" ;
	{
	    strnul	s(sp1,11) ;
	    cchar	*rp ;
	    printf("s=>%s<\n",ccp(s)) ;
	    cout << c++ << " " << sp1 << eol ;
	    rp = s ;
	    cout << c++ << " " << rp << eol ;
	    s(sp2,7) ;
	    rp = s ;
	    cout << c++ << " " << rp << eol ;
	    rp = s(sp1,3) ;
	    cout << c++ << " " << rp << eol ;
	    cout << c++ << " " << s(sp1,9) << eol ;
	    cout << c++ << " " << sp1 << eol ;
	    cout << c++ << " " << s(sp1,40) << eol ;
	    cout << c++ << " " << sp2 << eol ;
	    cout << c++ << " " << s(sp2,8) << eol ;
	    if (s) {
		strview	sv(sp2,10) ;
	        cout << c++ << " " << sv << eol ;
	    }
	} /* end block */
	return ex ;
}
/* end subroutine (main) */


