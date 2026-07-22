/* testfunmode SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++98 */

#include	<envstandards.h>	/* MUST be first to configure */
#include	<cstddef>		/* CSTD */
#include	<cstdlib>		/* CSTD */
#include	<cstdio>		/* CSTD */
#include	<string>		/* C++STD */
#include	<clanguage.h>		/* LIBU */
#include	<usysbase.h>		/* LIBU */
#include	<funmode.hh>		/* LIVDAM */
#include	<localmisc.h>		/* LIBU */

using std::cout ;			/* variable */

int main(int argc,con mainv argv,con mainv envv) {
    	funmode	fc{} ;
	cout << "fc=" << int(fc) << eol ;
	cout << "funmode::rd=" << int(funmode::rd) << eol ;

} /* end subroutine (main) */


