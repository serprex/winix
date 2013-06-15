#define stain static inline
#ifdef _WIN32
#else
#include <stdlib.h>
FILE*randfd;
stain void initrand(){
	randfd = fopen("/dev/urandom");
}
stain int randint(){
	int x;
	fread(&x,sizeof(int),1);
	return x;
}
#endif
#undef stain