#ifndef _SDC_DEBUG_H_
#define _SDC_DEBUG_H_

#include "tistdtypes.h"

int print(char *s);
#define error(e) print(RED e "\r\n" NOCOLOR);
#define PRINTI
#ifdef PRINTI
int printi(int i);
#else
#define printi(i) DEBUG_printHexInt(i)
#endif

#ifdef ANSI_COLORS
#define GRAY "\033[2;37m"
#define GREEN "\033[0;32m"
#define DARKGRAY "\033[0;30m"
//#define BLACK "\033[0;39m"
#define BLACK "\033[2;30m" // not faint black
//#define NOCOLOR "\033[0;39m"
#define NOCOLOR "\033[0m"
#define DBLUE "\033[2;34m"
#define RED "\033[0;31m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define CLS "\014"
#define NEWLINE "\r\n"
#define CR "\r"
#endif
#ifdef HTML_COLORS
#define GRAY "<font color=gray>"
#define GREEN "<font color=green>"
#define DARKGRAY "<font color=darkgray>"
#define BLACK "\033[2;30m" // not faint black
//#define NOCOLOR "\033[0;39m"
#define NOCOLOR "</font></font></u></b>"
#define DBLUE "<font color=blue>"
#define RED "<font color=red>"
#define BOLD "<b>"
#define UNDERLINE "<u>"
#define CLS "\014"
#define NEWLINE "<br>\r\n"
#define CR "<br>\r\n"
#endif

#ifndef GRAY
#define GRAY 
#define BLACK
#define NOCOLOR
#define DBLUE
#define RED
#endif

#define VALUE	DBLUE
#define IDENT	NOCOLOR
#define FNSTART	print((char*)__func__); print("\r\n");
#define entry	print((char*)__func__); print("\r\n"); goto entry; entry
#define trl_()	/*print(":"); printi(__LINE__);print(":");*/print((char*)__func__); print(" ");
#define trl()	/* print((char*)__FILE__);print(":"); printi(__LINE__);print(":");*/print((char*)__func__);print("\r\n");
#define trlm(m)	print((char*)__func__);print(" "); print(m);print("\r\n");
#define trlm_(m)	print((char*)__func__);print(" "); print(m);print(" ");
#define trvx(x)	{ print(IDENT #x GRAY"=0x");print_hex((int)x); print(NOCOLOR "\r\n"); }
#define trvi(i)	{ print(IDENT #i GRAY"="VALUE);printi((int)i); print(NOCOLOR "\r\n"); }
#define trvi_(i)	{ print(IDENT #i GRAY"="VALUE);printi((int)i); print(" " NOCOLOR); }
#define trvx_(x)	{ print(IDENT #x GRAY"=0x");print_hex((int)x); print(" " NOCOLOR); }
int getch();
int print_hex(unsigned int value);

#endif //_SDC_DEBUG_H_

