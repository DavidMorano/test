/* proginfo */


/* Copyright © 1998 David A­D­ Morano.  All rights reserved. */

#ifndef	PROGINFO_INCLUDE
#define	PROGINFO_INCLUDE	1


#ifdef	__cplusplus
extern "C" {
#endif

extern int proginfo_start(struct proginfo *,cchar **,cchar *,
			cchar *) ;
extern int proginfo_setprogroot(struct proginfo *,cchar *,int) ;
extern int proginfo_rootprogdname(struct proginfo *) ;
extern int proginfo_rootexecname(struct proginfo *,cchar *) ;
extern int proginfo_setentry(struct proginfo *,cchar **,cchar *,int) ;
extern int proginfo_setversion(struct proginfo *,cchar *) ;
extern int proginfo_setbanner(struct proginfo *,cchar *) ;
extern int proginfo_setsearchname(struct proginfo *,cchar *,cchar *) ;
extern int proginfo_setprogname(struct proginfo *,cchar *) ;
extern int proginfo_setexecname(struct proginfo *,cchar *) ;
extern int proginfo_pwd(struct proginfo *) ;
extern int proginfo_getpwd(struct proginfo *,char *,int) ;
extern int proginfo_getename(struct proginfo *,char *,int) ;
extern int proginfo_nodename(struct proginfo *) ;
extern int proginfo_finish(struct proginfo *) ;

#ifdef	__cplusplus
}
#endif

#endif /* PROGINFO_INCLUDE */


