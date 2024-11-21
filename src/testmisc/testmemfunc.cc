/* testmemfunc SUPPORT */

#include	<iostream>
#include	<cstdio>

namespace {
    struct member ;
    typedef void (member::*member_m)() ;
    struct member {
	member_m	m ;
	void printer() {
	    printf("printer\n") ;
	} ;
	void co() {
	    (this->*m)() ;
	} ;
	member() {
	    m = &member::printer ;
	} ;
    } ; /* end struct (member) */
}

int main() {
	member	mem ;
	mem.co() ;
}
/* end subroutine (main) */


