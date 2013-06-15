#define stain static inline
#ifdef _WIN32
#else
#include <unistd.h>
#include <sys/time.h>
static struct timeval tvx;
stain void inittime(){
	gettimeofday(&tvx,0);
}
stain double timesince(){
	static struct timeval tvy;
	gettimeofday(&tvy,0);
	timersub(&tvy,&tvx,&tvy);
	return tvy.tv_sec+tvy.tv_usec/1000000.;
}
stain void sleepd(double x){
	if(x>0){
		usleep(x*1000000);
	}
}
stain void endframe(int fps){
	sleepd(1./fps-timesince());
	inittime();
}
#endif
#undef stain