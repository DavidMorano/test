/* ex0div */


/*******************************************************************************

	Name:
	ex0div

	Description:
	This provides a 32-bit ÷ 32-bit division.
	This uses only a fundamental 16÷8 division operator.

*******************************************************************************/


#include <climits>
#include <cstring>

import bitmanip ;


typedef unsigned char  uchar;
typedef unsigned short ushort;

constexpr int	chlim = (UCHAR_MAX+1) ;


#ifdef	COMMENT
local int cmp(const uchar *a,const uchar *b,int n) {
    for (int i = n - 1 ; i >= 0 ; --i) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return +1;
    }
    return 0;
} /* end subroutine */
#endif /* COMMENT */

/*
 * Compare n-byte unsigned values
 * arrays are little-endian externally,
 * but comparison here is done high-byte first.
 */
local int vcmp(int n,const uchar *a,const uchar *b) {
    int res = 0 ;
    for (int i = (n-1) ; i >= 0 ; --i) {
	if (a[i] != b[i]) {
	    res = (a[i] > b[i]) ? +1 : -1 ;
	    break ;
	}
    } /* end for */
    return res ;
} /* end subroutine */

/*
 * a := a - b   over n bytes
 * little-endian
 */
local int vsub(int n,uchar *a,const uchar *b) {
    int borrow = 0;
    for (int i = 0 ; i < n ; ++i) {
        int t = int(a[i]) - int(b[i]) - borrow ;
        if (t < 0) {
            t += chlim ;
            borrow = 1 ;
        } else {
            borrow = 0 ;
	}
        a[i] = uchar(t) ;
    } /* end for */
    return borrow ;
} /* end subroutine (vsub) */

/*
 * Multiply 4-byte divisor by one byte q
 * result = 5-byte product
 * little-endian
 */
local void mul_byte(uchar *temp,const uchar *divisor,uchar q) {
    int carry = 0;
    for (int i = 0 ; i < 4 ; ++i) {
        int t = divisor[i] * q + carry;
        temp[i] = uchar(t & UCHAR_MAX) ;
        carry = t >> 8;
    } /* end for */
    temp[4] = (uchar)carry;
} /* end subroutine */

/*
 * Shift left by one byte:
 * multiply by 256
 * little-endian means move upward
 */
local void shift_left(uchar *x,int n) {
    for (int i = (n-1) ; i > 0 ; --i) {
        x[i] = x[i-1];
    } /* end for */
    x[0] = 0;
} /* end subroutine */

/*
 * + Divide 8-byte dividend by 4-byte divisor
 * + all arrays little-endian
   + n= number-of-dividend (and quotient) digits
 */
void div(int n,uchar *quotient,uchar *remainder,
         const uchar *dividend,const uchar *divisor) {
    cint	nb = nbits<uchar>
    uchar rem[(n/2)+2];
    uchar prod[(n/2)+2];
    std::memset(quotient,0,n);
    std::memset(rem,0,((n/2)+2));
    /* * Process from most-significant dividend byte downward */
    for (int i = (n-1) ; i >= 0 ; --i) {
        shift_left(rem,n);
        rem[0] = dividend[i];
        /* * Estimate quotient digit from top two bytes */
        ushort top = (ushort(rem[4]) << CHAR_BIT) | rem[3];
        uchar q = uchar(top / divisor[3]);
        /* * Correct estimate downward if needed */
        forever {
            mul_byte(prod,divisor,q);
            if (vcmp(((n/2)+1),rem,prod) >= 0) break;
            q -= 1 ;
        } /* end forever */
        quotient[i] = q;
        /* mul_byte(prod,divisor,q); */
        vsub(((n/2)+1),rem,prod) ;
    } /* end for */
    /* * final remainder: low 4 bytes */
    for (int i = 0 ; i < (n/2) ; ++i) {
        remainder[i] = rem[i] ;
    }
} /* end subroutine (div) */


