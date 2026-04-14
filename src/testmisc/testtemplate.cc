/* testtemplate SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */

/* test some template behavior */
/* version %I% last-modified %G% */


/* revision history:

	= 1998-04-13, David A-D- Morano
	Originally written for Rightcore Network Services.

*/

/*******************************************************************************

	Name:
	main

	Description:
	I test some behavior of a template.

*******************************************************************************/

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cmath>
#include	<iostream>
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<localmisc.h>

using std::sqrt ;			/* overloaded-subroutine */
using std::cbrt ;			/* overloaded-subroutine */
using std::cout ;			/* variable */

template<typename T> void fun(T v) noex {
    cout << "tsz=" << szof(T) << eol ;
    cout << "v=" << v << eol ;
}

template<typename T> local void delayed(T v) noex ;

int main(int,mainv,mainv) {
    const int	vint = 1 ;
    const long	vlong = 2 ;
    fun(vint) ;
    fun(vlong) ;
    fun<long>(vint) ;
    {
	[[maybe_unused]] float	vf2{2.0} ;
	[[maybe_unused]] float	vf3{3.0} ;
	[[maybe_unused]] double	vd2{2.0} ;
	double	res ;
	res = sqrt(vf2) ;
	cout << "res=" << res << eol ;
	res = sqrt(vd2) ;
	cout << "res=" << res << eol ;
	res = cbrt(vf2) ;
	cout << "res=" << res << eol ;
    }
    delayed(2) ;
}
/* end subroutine (main) */

template<typename T> local void delayed(T v) noex {
    cout << "tsz=" << szof(T) << eol ;
    cout << "v=" << v << eol ;
} /* end subroutine (delayed) */


