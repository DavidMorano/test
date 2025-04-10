/* main SUPPORT */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cmath>
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<usyscalls.h>
#include	<localmisc.h>

using std::sqrt ;			/* overloaded-subroutine */
using std::cbrt ;			/* overloaded-subroutine */
using std::cout ;			/* variable */

template<typename T> void fun(T v) noex {
    cout << "tsz=" << szof(T) << eol ;
    cout << "v=" << v << eol ;
}

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
}
/* end subroutine (main) */

