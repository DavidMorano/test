/* testscratch */
/* lang=C++20 */

#include	<cmath>
#include	<iostream>

using std::cout ;

static bool sub(int) ;

const bool	f_hello = true ;

constexpr char	msg[] = "goodbye" ;

constexpr double	val = 3.1415926 ;

const int	A = 1 ;
const int	B = 2 ;

int main() {
   double	v = pow(1.01,100.0) ;
	if constexpr (f_hello) {
   	    cout << msg << ' ' << v << '\n' ;
	} else {
   	    cout << "false=" << v << '\n' ;
	}
	cout << val << '\n' ;
	sub(3) ;
}
/* end subroutine (main) */

static bool sub(int v) {
	bool	f = false ;
	switch (v) {
	case A:
	case B:
	   f = true ;
	   ;;
	}
	return f ;
}

