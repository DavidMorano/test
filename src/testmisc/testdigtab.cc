/* main SUPPORT (testdigtab) */
#include	<envstandards.h>	/* must be ordered fist to configure */
#include	<climits>		/* |UCHAR_MAX| */
#include	<iostream>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysdefs.h>
#include	<localmisc.h>		/* |eol| */
using std::cout ;
import digtab ;				/* |getdig(3u)| */
int main() {
    for (int i = 0 ; i < 64 ; i += 1) {
	if (uchar uch = getdig(i) ; (uch >= '0') && (uch <= uchar('ÿ'))) {
	    cout << "dig[" << i << "]=" << uch << eol ;
	} else {
	    cout << "dig[" << i << "]=" << "invalid" << eol ;
	}
    }
}
