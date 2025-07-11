/* testcase SUPPORT */
/* charset=ISO8859-1 */
/* lang=C++20 (conformance reviewed) */


#include	<envstandards.h>	/* must be ordered first to configure */
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
#include	<strn.h>		/* |strnsub(3uc)| */
#include	<localmisc.h>

using std::cout ;			/* variable */

cchar		strmain[] = "Héllo" ;
cchar		strsub[] = "HÉl" ;

int main(int,mainv,mainv) {
    	cnullptr	np{} ;
    if (cc *tp ; (tp = strstr(strmain,strsub)) != np) {
	cout << "strstr" << eol ;
    }
    if (cc *tp ; (tp = strcasestr(strmain,strsub)) != np) {
	cout << "strcasestr" << eol ;
    }
    if (cc *tp ; (tp = strncasesub(strmain,-1,strsub)) != np) {
	cout << "strncasesub" << eol ;
    }
    if (cc *tp ; (tp = strnfoldsub(strmain,-1,strsub)) != np) {
	cout << "strnfoldsub" << eol ;
    }
} /* end subroutine (main) */


