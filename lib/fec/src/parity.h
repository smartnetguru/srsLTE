/* User include file for libfec
 * Copyright 2004, Phil Karn, KA9Q
 * May be used under the terms of the GNU Lesser General Public License (LGPL)
 */


#ifdef __x86_64__
#define __i386__
#endif

/* Determine parity of argument: 1 = odd, 0 = even */
#ifdef __i386__
static inline int parityb(unsigned char x){
  __asm__ __volatile__ ("test %1,%1;setpo %0" : "=g"(x) : "r" (x));
  return x;
}
#else
void partab_init();

static inline int parityb(unsigned char x){
  extern unsigned char Partab[256];
  extern int P_init;
  if(!P_init){
    partab_init();
  }
  return Partab[x];
}
#endif


static inline int parity(int x){
  /* Fold down to one byte */
  x ^= (x >> 16);
  x ^= (x >> 8);
  return parityb(x);
}
