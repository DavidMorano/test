/* testscratch */
/* lang=C++20 */

#include	<cmath>
#include	<iostream>

using std::cout ;

const bool	f_hello = true ;

constexpr char	msg[] = "goodbye" ;

constexpr double	val = 3.1415926 ;

int main() {
   double	v = pow(1.01,100.0) ;
	if constexpr (f_hello) {
   	    cout << msg << ' ' << v << '\n' ;
	} else {
   	    cout << "false=" << v << '\n' ;
	}
	cout << val << '\n' ;
}

