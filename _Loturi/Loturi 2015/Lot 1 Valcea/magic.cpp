#include "header.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>

//! giveValue();
#define rnd ( (rand())%16 )

void play()
{
    srand(time(NULL));

    long conf,lim,ant,mask;
    lim = 1<<16; ant=0;
    mask = lim-1;

    giveValue(0); giveValue(mask);
	for(conf=0;conf<lim;conf++){
        //giveValue( ( conf^(conf << rnd)^(conf >> rnd) )&(mask>>rnd) ) ;
        giveValue( ((rand()^rand()^(rand()-1))>>(rnd)&mask ));
	}

	while(conf <= 99900) {giveValue((rand())%lim);conf++;}
}
