/* testfunmode SUPPORT */
/* encoding=ISO8859-1 */
/* lang=C++98 */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<string>
#include	<usystem.h>
#include	<funmode.hh>
#include	<localmisc.h>

using std::cout ;			/* variable */

int main(int argc,mainv argv,mainv envv) {
    	funmode	fc{} ;

	cout << "fc=" << int(fc) << eol ;
	cout << "funmode::rd=" << int(funmode::rd) << eol ;

}
/* end subroutine (main) */

