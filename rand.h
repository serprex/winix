#define stain static inline
#ifdef _WIN32
#else
#include <stdio.h>
#include <limits.h>
FILE*randfd;
stain void initrand(){
	randfd = fopen("/dev/urandom","rb");
}
stain unsigned int randint(){
	int x;
	fread(&x,sizeof(int),1,randfd);
	return x;
}
stain unsigned char randbyte(){
	return getc(randfd);
}
stain unsigned int randto(unsigned int x){
	return x/(randint()/(double)UINT_MAX);
}
#endif
#undef stain