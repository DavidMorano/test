/* addrset HEADER */
/* lang=C++20 */

/* implement a map container of blocks (of a given structure) */
/* version %I% last-modified %G% */


/* revision history:

	= 2011-04-12, David A­D­ Morano
	This subroutine was originally written.  Only the introduction
	of C++11 has allowed this (finally), due to the addition
	(in C++11) of |unordered_map(3c++)|.

*/

/* Copyright © 2011 David A­D­ Morano.  All rights reserved. */

/*******************************************************************************

	Name:
	addrset

	Description:
	This object implements a map from a "key" type (|K|)
	to a given "block" type (|B|).

	Symopsis:
	int addrset_start<typename K,typename B>(int n = 0) noex

	Arguments:
	n		suggested starting possible number of elements

	Returns:
	>=0		ok
	<0		error (system-return)

*******************************************************************************/

#ifndef	MAPBLOCK_INCLUDE
#define	MAPBLOCK_INCLUDE
#ifdef	__cplusplus /* everything is C++ only */


#include	<envstandards.h>	/* MUST be ordered first to configure */
#include	<new>
#include	<utility>
#include	<functional>
#include	<clanguage.h>
#include	<utypedefs.h>
#include	<utypealiases.h>
#include	<usysrets.h>


class addrset_iter {
	std::pair<addrset_iter,bool>	retit ;
	void		*itp = nullptr ;
public:
	addrset_iter() noex { } ;
	addrset_iter(const addrset_iter &oit) noex {
	    if (this != &oit) {
	        itp = oit.itp ;
	    }
	} ;
	addrset_iter(addrset_iter &&oit) noex {
	    if (this != &oit) {
	        itp = oit.itp ;
		oit.itp = nullptr ;
	    }
	} ;
	addrset_iter &operator = (const addrset_iter &oit) noex {
	    if (this != &oit) {
	        itp = oit.itp ;
	    }
	    return *this ;
	} ;
	addrset_iter &operator = (addrset_iter &&oit) noex {
	    if (this != &oit) {
	        itp = oit.itp ;
		oit.itp = nullptr ;
	    }
	    return *this ;
	} ;
	addrset_iter &operator = (const addrset_iter *oip) noex {
	    if (this != oip) {
	        itp = oip->itp ;
	    }
	    return *this ;
	} ;
	std::pair<const K,B> &operator * () const noex {
	    return *mit ;
	} ;
	addrset_iter<K,B> &operator ++ () noex { /* pre-increment */
	    ++mit ;
	    return *this ;
	} ;
	addrset_iter<K,B> operator ++ (int) noex { /* post-increment */
	    addrset_iter<K,B>	tmp = *this ;
	    mit++ ;
	    return tmp ; /* returns previous PRVALUE */
	} ;
	addrset_iter<K,B> &operator += (int inc) noex {
	    mit += inc ;
	    return *this ;
	} ;
	addrset_iter<K,B> &operator + (int inc) const noex {
	    addrset_iter<K,B>	tmp = *this ;
	    tmp.mit + inc ;
	    return tmp ;
	} ;
	friend bool operator == (const addrset_iter<K,B> &i1,
		const addrset_iter<K,B> &i2) noex {
	    return (i1.mit == i2.mit) ;
	} ;
	friend addrset<K,B> ;
} ; /* end class (addrset_iter) */

enum addrsetmems {
	addrsetmem_start,
	addrsetmem_finish,
	addrsetmem_count,
	addrsetmem_overlast
} ;

template<typename K,typename B>
struct addrset_co {
	typedef addrset<K,B>	mb_t ;
	mb_t		*op = nullptr ;
	int		w = -1 ;
	constexpr void operator () (mb_t *p,int m) noex {
	    op = p ;
	    w = m ;
	} ;
	int operator () (int = 0) noex ;
	operator int () noex {
	    return operator () () ;
	} ;
} ; /* end struct (addrset_co) */

template<typename K,typename B>
class addrset {
	std::unordered_map<K,B>			*mp = nullptr ;
	typedef std::unordered_map<K,B>		maptype ;
	typedef addrset_co<K,B>		mbco_type ;
public:
	typedef K				key_type ;
	typedef B				mapped_type ;
	typedef std::pair<const K,B>		value_type ;
	typedef addrset_iter<K,B>		iterator ;
	typedef const addrset_iter<K,B>	const_iterator ;
	addrset(const addrset &) = delete ;
	addrset &operator = (const addrset &) = delete ;
	mbco_type	start ;
	mbco_type	finish ;
	mbco_type	count ;
	int		ins(K,const B &) noex ;
	int		rem(K) noex ;
	int		present(K &) noex ;
	int		get(K,B *) noex ;
	int		istart(int) noex ;
	int		ifinish() noex ;
	int		icount() noex ;
	iterator begin() noex {
	    iterator	it(this,false) ;
	    return it ;
	} ;
	iterator end() noex {
	    iterator	it(this,true) ;
	    return it ;
	} ;
	constexpr addrset() noex {
	    start(this,addrsetmem_start) ;
	    finish(this,addrsetmem_finish) ;
	    count(this,addrsetmem_count) ;
	} ; /* end ctor) */
	~addrset() noex {
	    if (mp) {
	        delete mp ;
		mp = nullptr ;
	    }
	} ; /* end dtor */
	friend iterator ;
} ; /* end class (addrset) */

template<typename K,typename B>
int addrset<K,B>::istart(int n) noex {
	typedef decltype(std::nothrow)	nothrow_t ;
	int		rs = SR_INVALID ;
	if (n >= 0) {
	    rs = SR_NOMEM ;
	    try {
		const nothrow_t		nt = std::nothrow ;
		const nullptr_t		np{} ;
	        if ((mp = new(nt) maptype(n)) != np) {
	            rs = SR_OK ;
	        }
	    } catch (...) {
		rs = SR_NOMEM ;
	    }
	}
	return rs ;
}
/* end method (addrset::istart) */

template<typename K,typename B>
int addrset<K,B>::ifinish() noex {
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    delete mp ;
	    mp = nullptr ;
	    rs = SR_OK ;
	}
	return rs ;
}


template<typename K,typename B>
int addrset<K,B>::ins(K k,const B &v) noex {
	typedef	typename maptype::iterator	mit_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = SR_OK ;
	    try {
	        std::pair<mit_t,bool>	r = mp->insert({k,v}) ;
	        if (!r.second) rs = SR_EXISTS ;
	    } catch (...) {
	        rs = SR_NOMEM ;
	    }
	} /* end if (non-null) */
	return rs ;
}
/* end method (addrset::ifinish) */

template<typename K,typename B>
int addrset<K,B>::rem(K k) noex {
	typedef typename maptype::size_type	mitsize_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = SR_OK ;
	    try {
	        mitsize_t	r = mp->erase(k) ;
	        if (!r) rs = SR_NOENT ;
	    } catch (...) {
	        rs = SR_NOMEM ;
	    }
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int addrset<K,B>::present(K &k) noex {
	typedef typename maptype::iterator	mit_t ;
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    const mit_t	itend = mp->end() ;
	    mit_t	it = mp->find(k) ;
	    rs = (it != itend) ? SR_OK : SR_NOENT ;
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int addrset<K,B>::get(K k,B *vp) noex {
	typedef typename maptype::iterator	mit_t ;
	int		rs = SR_FAULT ;
	if (vp) {
	    rs = SR_BUGCHECK ;
	    if (mp) {
	        typedef typename maptype::value_type	v_t ;
	        const mit_t		it_end = mp->end() ;
	        const mit_t		it = mp->find(k) ;
	        rs = SR_NOENT ;
	        if (it != it_end) {
		    const v_t	r = *it ;
		    *vp = r.second ;
		    rs = SR_OK ;
	        }
	    } /* end if (non-null) */
	} /* end if (non-null) */
	return rs ;
}

template<typename K,typename B>
int addrset<K,B>::icount() noex {
	int		rs = SR_BUGCHECK ;
	if (mp) {
	    rs = mp->size() ;
	} /* end if (non-null) */
	return rs ;
}
/* end method (addrset::icount) */

template<typename K,typename B>
int addrset_co<K,B>::operator () (int a) noex {
	int		rs = SR_BUGCHECK ;
	switch (w) {
	case addrsetmem_start:
	    rs = op->istart(a) ;
	    break ;
	case addrsetmem_finish:
	    rs = op->ifinish() ;
	    break ;
	case addrsetmem_count:
	    rs = op->icount() ;
	    break ;
	} /* end switch */
	return rs ;
}
/* end method (addrset_co::operator) */

#endif	/* __cplusplus */
#endif /* MAPBLOCK_INCLUDE */


