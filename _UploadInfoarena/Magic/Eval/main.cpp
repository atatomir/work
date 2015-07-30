#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <ctime>
#include <cstdlib>

using namespace std;

void result(char msg[], int p){
    fprintf(stderr, "%s", msg);
    printf("%d", p);
    exit(0);
}

#define MAX_COUNT 100000
#define count cnt

FILE * fin = fopen("magic4.in", "r");
FILE * fout = fopen("magic4.out", "r");

int Tests;
int my_secret_value, count;
bool passed;

vector<long> vv;



void fail() {
  result("Nu prea esti magic...\n",0);
  exit(0);
}

int giveValue( int value ) {

  -- count;

  if ( count < 0 )
    fail();

  if ( value < 0 || value >= ( 1 << 16 ) )
    fail();

  int rot = rand() % 16;

  my_secret_value ^= value;

  my_secret_value = ( my_secret_value >> rot ) |
                    ((my_secret_value & (( 1 << rot ) - 1)) << ( 16 - rot ));

  if ( my_secret_value == 0 ) {
    passed = true;
    return 1;
  }

  return 0;
}

void getAll(){
    vv.clear();
    long x;

    while( fscanf(fout,"%ld",&x) > 0 ) vv.push_back(x);
}

void play(){
    for(long i=0;i<vv.size();i++) giveValue(vv[i]);
}

int main() {

  srand(0);

  assert( fscanf( fin, "%d", &Tests ) != 0 );

  getAll();

  while ( Tests -- ) {

    assert( fscanf(fin, "%d", &my_secret_value) != 0 );
    count = MAX_COUNT;

    //!

        my_secret_value ^= rand()%(1<<16);

    //!

    passed = false;
    play();

    if ( my_secret_value != 0 && ! passed )
      fail();

  }

  result("Esti magic!",10);

  return 0;
}

