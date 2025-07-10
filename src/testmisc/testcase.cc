/* testcase SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered first to configure */
#include	<unistd.h>		/* |sysconf(2)| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>
#include	<cstdio>
#include	<cstring>		/* |strcasecmp(3c)| */
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<usysrets.h>
#include	<localmisc.h>

using std::cout ;			/* variable */

cchar		strmain[] = "Héllo" ;
cchar		strsub[] = "Hél" ;

int main(int,mainv,mainv) {
    if (int rc ; (rc = strcasecmp(strmain,strsub)) == 0) {
	cout << "yes" << eol ;
    }
} /* end subroutine (main) */


