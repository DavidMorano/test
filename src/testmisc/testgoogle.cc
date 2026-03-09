/* test of 'constexpr' */

#include	<cstddef>
#include	<cstdlib>
#include	<cstdio>


consteval int addone(int v) {
    	return v + 1 ;
}

consteval int testone() {
    	constexpr int a[] = { 1, 2, 3 } ;
	int sum = 0 ;
	for (int i = 0 ; i < 3 ; i += 1) {
	    sum += addone(a[i]) ;
	}
	return sum ;
}

int main() {
	    constexpr int val = testone() ;
	    printf("sum=%d\n",val) ;
}

