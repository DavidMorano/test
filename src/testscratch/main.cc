/* main SUPPORT (testscratch) */
/* lang=C++20 */

#include	<cmath>
#include	<iostream>

using std::cout ;

static void sub1() ;
static void sub2() ;

struct finder ;
typedef void (finder::*finder_m)(int)  ;
struct finder {
	finder_m	m ;
	finder() ;
	void sub1(int v)  {
	   cout << "sub1=" << v << '\n' ;
	} ;
	void sub2(int v)  {
	   cout << "sub2=" << v << '\n' ;
	} ;
	void choose(int v) {
	   cout << "choose=" << v << '\n' ;
	   (this->*m)(v) ;
	   m = &finder::sub2 ;
	} ;
} ;

finder::finder() {
	m = &finder::sub1 ;
}

int main() {
	sub1() ;
	sub2() ;
}
/* end subroutine (main) */

static void sub1() {
	cout << "sub1" << '\n' ;
}

static void sub2() {
	finder	fd ;
	cout << "sub2" << '\n' ;
	fd.choose(2) ;
}

