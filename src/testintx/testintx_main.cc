/* testintx_main SUPPORT (Test-Intx) */
/* charset=ISO8859-1 */
/* lang=C++98 */

/* test the INTX object */
/* version %I% last-modified %G% */

#define	CF_DEBUG	1		/* debugging */
#define	CF_DIVSHOW	0		/* divisions of */
#define	CF_DIVESTONE	0		/* divisions of */
#define	CF_DIVEST	0		/* divisions of */
#define	CF_DIVS		0		/* divisions of */
#define	CF_DIVSHORT	0		/* short-division */
#define	CF_DIVHONE	0		/* half-division (one) */
#define	CF_DIVHRAND	1		/* half-division (random) */
#define	CF_SZOF		0		/* size-of */
#define	CF_CARRY	0		/* carry-out */
#define	CF_PRVAR	0		/* prvar */
#define	CF_CAST		0		/* cast */
#define	CF_VALUES	0		/* values */
#define	CF_SHIFT	0		/* shift */
#define	CF_VMULONE	0		/* multiply */
#define	CF_MULTIPLY	0		/* multiply */
#define	CF_MULTIPLIER	1		/* multiplier */

/* revision history:

	= 2000-05-14, David A­D­ Morano
	Originally written for Rightcore Network Services.

*/

/* Copyright © 2000 David A­D­ Morano.  All rights reserved. */

#include	<envstandards.h>	/* ordered first to configure */
#include	<climits>		/* |CHAR_BIT| */
#include	<cstddef>		/* |nullptr_t| */
#include	<cstdlib>		/* |getenv(3c)| + |getprogname(3c)| */
#include	<cstdio>
#include	<new>			/* |nothrow| */
#include	<algorithm>		/* |min(3c++)| + |max(3c++)| */
#include	<iostream>
#include	<iomanip>
#include	<syncstream>		/* |osyncstream(3c++)| */
#include	<clanguage.h>
#include	<usysbase.h>
#include	<usyscalls.h>
#include	<usupport.h>		/* |getustime(3u)| */
#include	<usysutility.hh>	/* |snprintf(3u)| */
#include	<getfdfile.h>
#include	<strx.h>		/* |stræbbrerr(3uc)| */
#include	<localmisc.h>
#include	<libf.h>		/* LIBF */
#include	<dprint.hh>		/* debugging */

#pragma		GCC dependency		"mod/libutil.ccm"

import libutil ;			/* |lenstr(3u)| */
import intext ;				/* |uint256_t| */
import testint ;			/* |uint256_t| */
import loadvals ;			/* |loadval()| */
import varithmetic ;

/* local defines */

#ifndef	CF_DEBUG
#define	CF_DEBUG	1		/* debugging */
#endif
#ifndef	CF_DIVSHOW
#define	CF_DIVSHOW	0
#endif
#ifndef	CF_DIVESTONE
#define	CF_DIVESTONE	0
#endif
#ifndef	CF_DIVEST
#define	CF_DIVEST	0
#endif
#ifndef	CF_DIVS
#define	CF_DIVS		0
#endif
#ifndef	CF_DIVSHORT
#define	CF_DIVSHORT	0
#endif
#ifndef	CF_DIVHONE
#define	CF_DIVHONE	1		/* half-division */
#endif
#ifndef	CF_DIVHRAND
#define	CF_DIVHRAND	1		/* half-division (random) */
#endif
#ifndef	CF_SZOF
#define	CF_SZOF		0
#endif
#ifndef	CF_CARRY
#define	CF_CARRY	0
#endif
#ifndef	CF_CAST
#define	CF_CAST		0		/* cast */
#endif
#ifndef	CF_PRVAR
#define	CF_PRVAR	0		/* prvar */
#endif
#ifndef	CF_SHIFT
#define	CF_SHIFT	0		/* shift */
#endif
#ifndef	CF_VALUES
#define	CF_VALUES	0		/* values */
#endif
#ifndef	CF_VMULONE
#define	CF_VMULONE	0		/* multiply */
#endif
#ifndef	CF_MULTIPLY
#define	CF_MULTIPLY	0		/* multiply */
#endif
#ifndef	CF_MULTIPLIER
#define	CF_MULTIPLIER	1		/* multiplier */
#endif


/* local namespaces */

using std::min ;			/* subroutine-template */
using std::max ;			/* subroutine-template */
using libu::snprintf ;			/* subroutine */
using std::cout ;			/* variable */
using std::nothrow ;			/* constant */


/* local typedefs */


/* external subroutines */


/* external variables */


/* local structures */

struct looksz {
    	inline static cint 	a = 1 ;
	int		b ;
} ;


/* forward references */

local int	test_vmuluone() noex ;
local int	test_multiply() noex ;
local int	test_divshow() noex ;
local int	test_divshow1() noex ;
local int	test_divshow2() noex ;
local int	test_divestone() noex ;
local int	test_divest() noex ;
local int	test_divs() noex ;
local int	test_divshort() noex ;
local int	test_divhone() noex ;
local int	test_divhrand() noex ;
local int	test_carry() noex ;
local int	test_prvar() noex ;
local int	test_cast() noex ;
local int	test_values() noex ;
local int	test_shift() noex ;

#if	CF_MULTIPLIER
local int	test_multiplier() noex ;
#endif /* CF_MULTIPLIER */


/* local variables */

static time_t	now		= time(nullptr) ;
cint		fd_err		= FD_STDERR ;
cbool		f_debug		= CF_DEBUG ;
cbool		f_divshow	= CF_DIVSHOW ;
cbool		f_divestone	= CF_DIVESTONE ;
cbool		f_divest	= CF_DIVEST ;
cbool		f_divestprt	= true ;
cbool		f_divs		= CF_DIVS ;
cbool		f_divshort	= CF_DIVSHORT ;
cbool		f_divhone	= CF_DIVHONE ;
cbool		f_divhrand	= CF_DIVHRAND ;
cbool		f_szof		= CF_SZOF ;
cbool		f_carry		= CF_CARRY ;
cbool		f_prvar		= CF_PRVAR ;
cbool		f_cast		= CF_CAST ;
cbool		f_values	= CF_VALUES ;
cbool		f_shift		= CF_SHIFT ;
cbool		f_vmuluone	= CF_VMULONE ;
cbool		f_multiply	= CF_MULTIPLY ;
cbool		f_multiplier	= CF_MULTIPLIER ;


/* exported variables */


/* exported subroutines */

template <typename T> local int printvar(T vv) noex {
    	cint olen = LINEBUFLEN ;
    	cint usz = szof(ulong) ;
    	cint nb = (szof(ulong) * CHAR_BIT) ;
	cint sz = szof(T) ;
	int		rs = SR_NOMEM ;
	(void) vv ;
	(void) olen ;
	(void) usz ;
	(void) sz ;
	(void) nb ;
	if (char *obuf = new(nothrow) char [olen + 1] ; obuf) {
	    cchar *fmt = "%02d %016lX-%016lX" ;
	    ulong lo ;
	    ulong hi ;
	    for (int i = 0 ; i < (sz / usz / 2) ; i += 1) {
	        lo = ulongconv(vv) ;
	        vv >>= nb ;
	        hi = ulongconv(vv) ;
	        vv >>= nb ;
		if ((rs = snprintf(obuf,olen,fmt,i,hi,lo)) >= 0) {
	            rs = printf("prvar: %s\n",obuf) ;
		}
		if (rs < 0) break ;
	    } /* end for */
	    delete [] obuf ;
	    obuf = nullptr ;
	} /* end if (m-a-f) */
	return rs ;
} /* end subroutine (printvar) */

int mainsub(int,con mainv,con mainv) noex {
    	looksz		thing{} ;
    	int		ex = EXIT_SUCCESS ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	if_constexpr (f_szof) {
	    	printf("szof(thing)=%d\n",szof(thing)) ;
	    	printf("thing.a=%d\n",thing.a) ;
	    	printf("thing.b=%d\n",thing.b) ;
	}
	if (rs >= 0) {
	    if_constexpr (f_vmuluone) {
	        rs = test_vmuluone() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_multiply) {
	        rs = test_multiply() ;
	    }
	}
	if_constexpr (f_carry) if (rs >= 0) {
	    rs = test_carry() ;
	} /* end if */
	if_constexpr (f_divshow) if (rs >= 0) {
	    rs = test_divshow() ;
	} /* end if */
	if_constexpr (f_divestone) if (rs >= 0) {
	    rs = test_divestone() ;
	} /* end if */
	if_constexpr (f_divest) if (rs >= 0) {
	    rs = test_divest() ;
	} /* end if */
	if_constexpr (f_divs) if (rs >= 0) {
	    rs = test_divs() ;
	} /* end if */
	if_constexpr (f_divshort) if (rs >= 0) {
	    rs = test_divshort() ;
	} /* end if */
	if_constexpr (f_divhone) if (rs >= 0) {
	    rs = test_divhone() ;
	} /* end if */
	if_constexpr (f_divhrand) if (rs >= 0) {
	    rs = test_divhrand() ;
	} /* end if */
	if (rs >= 0) {
	    if_constexpr (f_prvar) {
	        rs = test_prvar() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_cast) {
	        rs = test_cast() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_values) {
	        rs = test_values() ;
	    }
	}
	if (rs >= 0) {
	    if_constexpr (f_shift) {
	        rs = test_shift() ;
	    }
	}
#if	CF_MULTIPLIER
	if (rs >= 0) {
	    if_constexpr (f_multiplier) {
	        rs = test_multiplier() ;
	    }
	}
#endif /* CF_MULTIPLIER */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	DPRINTF("ret ex=%d rs=%d\n",ex,rs) ;
	return ex ;
} /* end subroutine (mainsub) */

int main(int argc,con mainv argv,con mainv envv) {
    	cnothrow	nt{} ;
    	cint		sl = MINSIGSTKSZ +  SIGSTKSZ ;
    	int		ex = EXIT_FAILURE ;
	int		rs ;
	int		rs1 ;
	if (char *sp = new(nt) char [sl] ; sp) {
	    stack_t stk{} ;
	    stk.ss_sp = sp ;
	    stk.ss_size = sl ;
            stk.ss_flags = 0 ;
	    if ((rs = u_sigaltstack(&stk,nullptr)) >= 0) {
	        {
                    ex = mainsub(argc,argv,envv) ;
	        }
                stk.ss_flags = SS_DISABLE ;
	        rs1 = u_sigaltstack(&stk,nullptr) ;
		if (rs >= 0) rs = rs1 ;
	    } /* end if u_sigaltstack) */
	    delete [] sp ;
	    sp = nullptr ;
	} /* end if (m-a-f) */
	if ((ex == EXIT_SUCCESS) && (rs < 0)) {
	    ex = EXIT_FAILURE ;
	}
	return ex ;
} /* end subroutine (main) */


/* local subroutines */

local int test_divshow() noex {
    int		rs = SR_OK ;
    if_constexpr (false) {
    if (rs >= 0) rs = test_divshow1() ;
    }
    if (rs >= 0) rs = test_divshow2() ;
    return rs ;
} /* end subroutine (test_divshow) */

local int test_divshow1() noex {
    int		rs = SR_OK ;
    DPRINTF("ent\n") ;
    for (int i = 0 ; i < 4 ; i += 1) {
	uint u = i ;
	uint res ;
	uint rem ;
        for (int j = 1 ; j < 4 ; j += 1) {
	    uint v = j ;
	    res = u / v ;
	    rem = u % v ;
	    printf("%02X %02X %02X %02X\n",u,v,res,rem) ;
	} /* end for */
    } /* end for */
    DPRINTF("ret rs=%d\n",rs) ;
    return rs ;
} /* end subroutine (test_divshow1) */

#ifdef	COMMENT
local void vclear(int n,uchar *v) noex {
    for (int i = 0 ; i < n ; i += 1) {
	v[i] = 0 ;
    } /* end for */
} /* end subroutine (vclear) */

    template<typename Dig>
    constexpr void vcopy(int n,Dig *r,const Dig *o = nullptr) noex {
	if (o) {
	    for (int i = 0 ; i < n ; i += 1) {
	        r[i] = o[i] ;
	    }
	} else {
	    vclear(n,r) ;
	}
    } /* end subroutine (vcopy) */
#endif /* COMMENT */

local void vload(int n,mut uchar *v,con uint val) noex {
    cint nd = szof(val) ;
    for (int i = 0 ; i < min(n,nd) ; i += 1) {
	uint	vv = (val >> (i * CHAR_BIT)) ;
	v[i] = uchar(vv & UCHAR_MAX) ;
    } /* end for */
    if (nd < n) {
    	int nr = (n - nd) ;
        vclear(nr,(v + nd)) ;
    }
} /* end subroutine (vload) */

local uint vjoin(int n,con uchar *q) noex {
    uint	res = 0 ;
    for (int i = (n - 1) ; i >= 0 ; --i) {
	uint v = q[i] ;
	res <<= CHAR_BIT ;
	res |= v ;
    } /* end for */
    return res ;
} /* end subroutine (vjoin) */

local bool divest(mut uchar *q,mut uchar *r,con uchar *u,con uchar *v) noex {
	udiv<uint>	res{} ;
	cint		n = 4 ;
    	cint		ndiv = nsigdig(2,v) ;
	uint		num = vjoin(4,u) ;
	uint		den = vjoin(2,v) ;
	uint		tden = 0 ;
	bool		fz = true ;	/* divide-by-zero */
	if_constexpr (f_divestprt) {
    DPRINTF("ent\n") ;
    DPRINTF("u=%02X:%02X:%02X:%02X\n",u[3],u[2],u[1],u[0]) ;
    DPRINTF("v=%02X:%02X\n",v[1],v[0]) ;
    DPRINTF("num=%08X den=%04X\n",num,den) ;
	}
    	res(num,den) ;
	if_constexpr (f_divestprt) {
    DPRINTF("answer quo=%08X rem=%04X\n",res.quo,res.rem) ;
	}
	if (ndiv == 1) {
	    tden = v[0] ;
	    res(num,tden) ;
	    fz = false ;
	    vload(4,q,res.quo) ;
	    vload(2,r,res.rem) ;
	} else if (ndiv > 1) {
	    cint	nu = nsigdig(n,u) ;
	    uint	estden = v[1] ;
	    uchar	uu[n+2] ;
	if_constexpr (f_divestprt) {
	    DPRINTF("for-before\n") ;
	}
	    fz = false ;
	    vcopy(n,uu,u) ;
	    uu[n+0] = 0 ;
	    uu[n+1] = 0 ;
	    vclear(n,q) ;
	    vclear(2,r) ;
	    for (int i = (nu - 1 - 1) ; i >= 0 ; --i) {
		uint	estnum ;
		uint	estrem ;
		uint	estpro{} ;
	        uint	estend = vjoin(2,(uu + i + 1)) ;
	        estden = v[1] ;
	if_constexpr (f_divestprt) {
    	        DPRINTF("i=%d estden=%02X\n",i,estden) ;
    	    	    DPRINTF("estend=%08X\n",estend) ;
	}
		    estnum = vjoin(4,(uu + i)) ;
	if_constexpr (f_divestprt) {
    	    	    DPRINTF("estnum=%08X\n",estnum) ;
	            DPRINTF("while-before\n") ;
	}
		while (estden > 0) {
	            res(estend,estden) ;
	            estpro = res.quo * den ;
	if_constexpr (f_divestprt) {
		    DPRINTF("estpro=%08X\n",estpro) ;
	}
	            if (estpro <= estnum) break ;
	            estend -= 1 ;
	if_constexpr (f_divestprt) {
	            DPRINTF("dec estend=%02X\n",estend) ;
	}
		} /* end while */
	if_constexpr (f_divestprt) {
	        DPRINTF("while-end\n") ;
	        DPRINTF("estnum=%08X estpro=%08X\n",estnum,estpro) ;
	        DPRINTF("estrem=%08X\n",(estnum-estpro)) ;
	}
		estrem = (estnum - estpro) ;
	if_constexpr (false) {
	        DPRINTF("quo=%08X rem=%04X\n",res.quo,estrem) ;
	}
		q[i + 0] = uchar(res.quo >> 0) ;
		if_constexpr (f_divestprt) {
		    const uint xq = vjoin(8,q) ;
		    DPRINTF("xq=%08X\n",xq) ;
		}
		uu[i + 3] = 0 ;
		uu[i + 2] = 0 ;
		uu[i + 1] = uchar(estrem >> CHAR_BIT) ; /* always zero */
		uu[i + 0] = uchar(estrem >> 0) ;
		if_constexpr (f_divestprt) {
		    const uint nuu = vjoin(4,uu) ;
		    DPRINTF("nuu=%08X\n",nuu) ;
		}
	    } /* end for */
	if_constexpr (f_divestprt) {
	    DPRINTF("for-after\n") ;
	}
	    r[1] = uu[1] ;
	    r[0] = uu[0] ;
	} /* end if (zero-divisor detect) */
	if_constexpr (f_divestprt) {
	DPRINTF("ret fz=%u\n",uint(fz)) ;
	}
    	return fz ;
} /* end subroutine (divest) */

local void vdivufull(int n,uchar *q,uchar *r,uchar *u,uchar *v) noex {
    udiv<uint>	res{} ;
    uchar	tmp[n+4] ;
    uchar	*t ;
    DPRINTF("ent\n") ;
    vclear((n+4),tmp) ;
    t = (tmp + 2) ;
    vcopy(4,t,u) ;
    (void) n ;
    (void) q ;
    (void) r ;
    (void) u ;
    (void) v ;
    DPRINTF("u=%02X:%02X:%02X:%02X\n",u[3],u[2],u[1],u[0]) ;
    DPRINTF("t=%02X:%02X:%02X:%02X\n",t[3],t[2],t[1],t[0]) ;
    DPRINTF("v=%02X:%02X\n",v[1],v[0]) ;
    for (int i = (n-1) ; i >= 0 ; --i) {
	{
	    cuint num = vjoin(4,u) ;
	    cuint den = vjoin(2,v) ;
            DPRINTF("num=%08X den=%04X\n",num,den) ;
	}
	{
            cc *fmt = "i=%d t=%02X:%02X:%02X:%02X\n" ;
	    cint ti = (i - 2) ;
            DPRINTF(fmt,i,t[ti+3],t[ti+2],t[ti+1],t[ti+0]) ;
	}
	/* divest(&res,(t+i-2),v) ; */
        DPRINTF("q=%08X r=%04X\n",res.quo,res.rem) ;
	q[i+1] = uchar(res.quo) ;
	t[i+0] = uchar(res.rem) ;
    } /* end for */
    DPRINTF("ret\n") ;
} /* end subroutine (vdivufull) */

local int test_divshow2() noex {
    int		rs = SR_OK ;
    uchar	u[7] = {} ;
    uchar	v[] = {} ;
    uchar	q[6] = {} ;
    uchar	r[2] = {} ;
    DPRINTF("ent\n") ;
    vload(4,u,0x03040506) ;
    for (int i = 1 ; i < 2 ; i += 1) {
	uint den = (i * 0x01020304) ;
        DPRINTF("i=%d\n",i) ;
    	vload(2,v,den) ;
        DPRINTF("den=%02X:%02X\n",v[1],v[0]) ;
	vdivufull(4,q,r,u,v) ;
	{
	    const uint uu = vjoin(4,u) ;
	    const uint vv = vjoin(2,v) ;
	    const uint qq = vjoin(4,q) ;
	    const uint rr = vjoin(2,r) ;
	    printf("%08X %04X %08X %04X\n",uu,vv,qq,rr) ;
	}
    } /* end for */
    DPRINTF("ret rs=%d\n",rs) ;
    return rs ;
} /* end subroutine (test_divshow2) */

local int test_divestone() noex {
    udiv<uint>	res = {} ;
    cint	n = 4 ; /* quotient digits */
    uchar	u[4] ;
    uchar	v[2] ;
    uchar	q[6] = {} ;
    uchar	r[4] = {} ;
    int		rs = SR_OK ;
    bool	fz = false ;
    DPRINTF("ent\n") ;
    {
        uint dividend = 0x03040506 ;
	{
	    ushort divisor = 0x0102 ;
            vload(n,u,dividend) ;
            vload(2,v,divisor) ;
            (void) q ;
            (void) r ;
            {
	        fz = divest(q,r,u,v) ;
	        res.quo = vjoin(n,q) ;
	        res.rem = vjoin(2,r) ;
	        {
	            udiv<uint> check ;
	            uint num = vjoin(n,u) ;
	            uint den = vjoin(2,v) ;
    	            check(num,den) ;
	            if ((res.quo != check.quo) || (res.rem != check.rem)) {
			const cchar *fmt0 = "test q=%08X r=%04X\n" ;
			const cchar *fmt1 = "answ q=%08X r=%04X\n" ;
                        DPRINTF(fmt0,res.quo,res.rem) ;
                        DPRINTF(fmt1,check.quo,check.rem) ;
	                rs = SR_BADFMT ;
	            } /* end if */
	        } /* end block */
            } /* end block */
	}
    }
    DPRINTF("ret rs=%d fz=%u\n",rs,uint(fz)) ;
    return rs ;
} /* end subroutine (test_divestone) */

local int test_divest() noex {
    udiv<uint>	res = {} ;
    uint	seed = uint(now) ;
    cint	n = 4 ;
    uchar	u[4] ;
    uchar	v[2] ;
    uchar	q[6] = {} ;
    uchar	r[4] = {} ;
    int		rs = SR_OK ;
    bool	fz = false ;
    DPRINTF("ent\n") ;
    for (int i = 0 ; i < 1000 ; ++i) {
        uint dividend = rand_r(&seed) ;
	for (int j = 1 ; j < USHORT_MAX ; ++j) {
	    ushort divisor = ushort(j) ;
            vload(n,u,dividend) ;
            vload(2,v,divisor) ;
            (void) q ;
            (void) r ;
            {
	        fz = divest(q,r,u,v) ;
	        res.quo = vjoin(4,q) ;
	        res.rem = vjoin(2,r) ;
	        {
	            udiv<uint> check ;
	            uint num = vjoin(n,u) ;
	            uint den = vjoin(2,v) ;
    	            check(num,den) ;
	            if ((res.quo != check.quo) || (res.rem != check.rem)) {
			const cchar *fmt0 = "test q=%08X r=%04X\n" ;
			const cchar *fmt1 = "answ q=%08X r=%04X\n" ;
                        DPRINTF(fmt0,res.quo,res.rem) ;
                        DPRINTF(fmt1,check.quo,check.rem) ;
	                rs = SR_BADFMT ;
	            } /* end if */
	        } /* end block */
            } /* end block */
	} /* end for */
    } /* end for */
    DPRINTF("ret rs=%d fz=%u\n",rs,uint(fz)) ;
    return rs ;
} /* end subroutine (test_divest) */

constexpr int	dds[] = { 0xFF, 0x01, 0x10 } ;

struct divs_stat {
    int		rem ;
    int		quo ;
    int		div ;
} ;

local int test_divs() noex {
    	divs_stat	stat = {} ;
    	int		rs = SR_OK ;
	int		remax{} ;
	int		quo{} ;
	int		rem{} ;
	for (cauto &e : dds) {
	    for (int d = 1 ; d < (UCHAR_MAX + 1) ; ++d) {
		quo = e / d ;
		rem = e % d ;
		if (rem > remax) {
		    remax = rem ;
		    stat.rem = rem ;
		    stat.quo = quo ;
		    stat.div = d ;
		}
	    } /* end for */
	} /* end for */
	printf("remax=%d\n",remax) ;
	printf("stat quo=%d rem=%d div=%d\n",stat.quo,stat.rem,stat.div) ;
	{
	    divs_stat ds{} ;
	    for (int d = 1 ; d < (UCHAR_MAX + 1) ; ++d) {
		int end = ((232 * 256) + 255) ;
	        div_t	res = div(end,d) ;
		if (res.rem > ds.rem) {
		    ds.rem = res.rem ;
		    ds.quo = res.quot ;
		    ds.div = d ;
		}
	    } /* end for */
	    printf("ds quo=%d rem=%d div=%d\n",ds.quo,ds.rem,ds.div) ;
	} /* end block */
	return rs ;
} /* end subroutine (test_divs) */

local int test_divshort() noex {
    	cint		n = 4 ;
	uint		seed = uint(now) ;
    	uchar		dd[4] ;
    	uchar		q[4] = {} ;
    	int		rs = SR_OK ;
	uint		quo0{}, quo1{} ;
	uchar		rem0{}, rem1{} ;
	DPRINTF("ent\n") ;
	for (int i = 0 ; i < 100000 ; ++i) {
	    const uint	dividend = rand_r(&seed) ;
	    for (int j = 1 ; j < (UCHAR_MAX + 1) ; ++j) {
	        uchar d = uchar(j) ;
	        loadval(n,dd,dividend) ;
    	        rem0 = vdivushort(n,q,dd,d) ;
	        mkv(&quo0,q) ;
	        quo1 = dividend / d ;
	        rem1 = uchar(dividend % d) ;
	        if ((quo0 != quo1) || (rem0 != rem1)) {
	            printf("mismatch\n") ;
	            printf("%u quo=%d rem=%d\n",d,quo0,rem0) ;
	            printf("%u quo=%d rem=%d\n",d,quo1,rem1) ;
		    rs = SR_BADFMT ;
	        }
	        if (rs < 0) break ;
	    } /* end for */
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_divshort) */

local int test_divhone() noex {
    udiv<uint>	res = {} ;
    cint	n = 8 ; /* quotient digits */
    uchar	u[8] ;
    uchar	v[4] ;
    uchar	q[8] = {} ;
    uchar	r[4] = {} ;
    int		rs = SR_OK ;
    bool	fz = false ;
    DPRINTF("ent\n") ;
    {
	cint nh = (n/2) ;
        uint dividend = 0x03040506 ;
	{
	    ushort divisor = 0x0102 ;
            vload(n,u,dividend) ;
            vload(2,v,divisor) ;
            (void) q ;
            (void) r ;
            if ((fz = vdivuh(n,q,r,u,v)) == false) {
                res.quo = vjoin(nh,q) ;
                res.rem = vjoin(nh,r) ;
                {
                    udiv<uint> check ;
                    uint num = vjoin(nh,u) ;
                    uint den = vjoin(nh,v) ;
                    check(num,den) ;
                    if ((res.quo != check.quo) || (res.rem != check.rem)) {
                        const cchar *fmt0 = "test q=%08X r=%04X\n" ;
                        const cchar *fmt1 = "answ q=%08X r=%04X\n" ;
                        DPRINTF(fmt0,res.quo,res.rem) ;
                        DPRINTF(fmt1,check.quo,check.rem) ;
                        rs = SR_BADFMT ;
                    } /* end if */
                } /* end block */
            } else {
                rs = SR_DOM ;       /* divide-by-zero error */
            } /* end if (non-zero divisor) */
	} /* end block */
    }
    DPRINTF("ret rs=%d (%s) fz=%u\n",rs,strabbrerr(rs),uint(fz)) ;
    return rs ;
} /* end subroutine (test_divhone) */

local int test_divhrand() noex {
    udiv<uint>	res = {} ;
    uint	seed = uint(now) ;
    cint	n = 8 ; /* quotient digits */
    uchar	u[8] ;
    uchar	v[4] ;
    uchar	q[8] = {} ;
    uchar	r[4] = {} ;
    int		rs = SR_OK ;
    int		c = 0 ;
    bool	fz = false ;
    DPRINTF("ent\n") ;
    vclear((n/2),v) ;
    for (int i = 0 ; i < 20 ; i += 1) {
	cint nh = (n/2) ;
        uint dividend = rand_r(&seed) ;
        vload(n,u,dividend) ;
	for (int j = 1 ; j <= USHORT_MAX ; j += 1) {
	    ushort divisor = ushort(j) ;
            vload(2,v,divisor) ; 
            if ((fz = vdivuh(n,q,r,u,v)) == false) {
                res.quo = vjoin(nh,q) ;
                res.rem = vjoin(nh,r) ;
                {
                    udiv<uint> check ;
                    uint num = vjoin(nh,u) ;
                    uint den = vjoin(nh,v) ;
                    check(num,den) ;
                    if ((res.quo != check.quo) || (res.rem != check.rem)) {
                        const cchar *fmt0 = "test q=%08X r=%04X\n" ;
                        const cchar *fmt1 = "answ q=%08X r=%04X\n" ;
                        DPRINTF("test-error\n") ;
                        DPRINTF("u=%08X v=%08X\n",num,den) ;
                        DPRINTF(fmt0,res.quo,res.rem) ;
                        DPRINTF(fmt1,check.quo,check.rem) ;
                        rs = SR_BADFMT ;
                    } /* end if */
                } /* end block */
		c += 1 ;
            } else {
		    cchar *fmt = "v=%02X:%02X:%02X:%02X\n" ;
		    DPRINTF(fmt,v[3],v[2],v[1],v[0]) ;
                rs = SR_DOM ;       /* divide-by-zero error */
            } /* end if (non-zero divisor) */
	    if (rs < 0) break ;
	} /* end for */
	if (rs < 0) break ;
    } /* end for */
    DPRINTF("ret rs=%d (%s) c=%d fz=%u\n",rs,strabbrerr(rs),c,uint(fz)) ;
    return (rs >= 0) ? c : rs ;
} /* end subroutine (test_divhrand) */

local int test_carry() noex {
    	int		rs = SR_OK ;
	    uint	r, co ;
	    cchar	*fmt = 
	    	        "%02x %02x = %02x + %02x %02x\n" ;
	    printf("co  r    j    i ci\n") ;
	    for (uint ci = 0 ; ci < 2 ; ci += 1) {
	        for (uint i = 0 ; i < 4 ; i += 1) {
	            for (uint j = 0 ; j < 4 ; j += 1) {
		        r = j + i + ci ;
		        co = (r >> 2) ;
	    	        printf(fmt,co,(r & 3),j,i,ci) ;
		    }
	        }
	    }
	return rs ;
} /* end subroutine (test_carry) */

local int test_prvar() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	{
	    rs = printvar(a) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_prvar) */

local int test_cast() noex {
    	uint256_t	a = 0x21 ;
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	{
	    cint vv = int(a) ;
	    printf("cast=%d\n",vv) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_cast) */

constexpr int		values[] = {
    -2, 3
} ; /* end array */

local int test_values() noex {
	int		rs = SR_OK ;
	DPRINTF("ent\n") ;
	for (cauto &e : values) {
	    uint256_t	vx = e ;
	    {
	        cint vv = int(vx) ;
	        printf("cast=%d\n",vv) ;
	        rs = printvar(vx) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_values) */

local int test_shift() noex {
	int		rs = SR_OK ;
	uint256_t	v = 3 ;
	DPRINTF("ent\n") ;
	v <<= (128 + 20) ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
	        rs = printvar(v) ;
		v = v.ashr(20) | uint256_t(0) ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_shift) */

local int test_vmuluone() noex {
	int		rs = SR_OK ;
	uchar		u[4] ;
	uchar		v[4] ;
	uchar		r[8] ;
	uchar v0 = 0xFF ;
	DPRINTF("ent\n") ;
	    vload(4,u,0x0102) ;
	    vload(4,v,v0) ;
    DPRINTF("u=%02X:%02X:%02X:%02X\n",u[3],u[2],u[1],u[0]) ;
    DPRINTF("v=%02X:%02X:%02X:%02X\n",v[3],v[2],v[1],v[0]) ;
	{
	    uint uu = 0x0102 ;
	    uint qq = uu * v0 ;
            DPRINTF("qq=%08X\n",qq) ;
	}
	{
	    vmulu(8,r,u,v) ;
    DPRINTF("r=%02X:%02X:%02X:%02X\n",r[3],r[2],r[1],r[0]) ;
	} /* end block */
	{
	    vmuluone(8,r,u,v0) ;
    DPRINTF("r=%02X:%02X:%02X:%02X\n",r[3],r[2],r[1],r[0]) ;
	}
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_vmuluone) */

local int test_multiply() noex {
	int		rs = SR_OK ;
	uint256_t	m = (16 * 5) ;
	uint256_t	v = 0x0303 ;
	DPRINTF("ent\n") ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
	        rs = printvar(v) ;
		v = v * m ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_multiply) */

#if	CF_MULTIPLIER
local int test_multiplier() noex {
    	int		rs = SR_OK ;
	utest64_t	m = (16 * 5) ;
	utest64_t	v = 0x0303 ;
	ulong		vcheck = 0x0303 ;
	DPRINTF("ent\n") ;
	for (int i = 0 ; i < 8 ; i += 1) {
	    {
		culong pv = v ;
	        printf("a=%018lx\n",pv) ;
		rs = (pv != vcheck) ? SR_BADFMT : 0 ;
		v = v * m ;
		vcheck *= (16 * 5)  ;
	    }
	    if (rs < 0) break ;
	} /* end for */
	DPRINTF("ret rs=%d\n",rs) ;
	return rs ;
} /* end subroutine (test_multiplier) */
#endif /* CF_MULTIPLIER */


