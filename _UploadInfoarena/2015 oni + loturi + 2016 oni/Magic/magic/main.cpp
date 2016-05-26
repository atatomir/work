#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "header.h"

#define MAX_COUNT 100000

FILE * fin = fopen("magic.in", "r");
FILE * fout = fopen("magic.out", "w");

int Tests;
int my_secret_value, count;
bool passed;

void fail() {
  fprintf( fout, "Incorect!\n");
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

int main() {

  srand(0);

  assert( fscanf( fin, "%d", &Tests ) != 0 );

  while ( Tests -- ) {

    assert( fscanf(fin, "%d", &my_secret_value) != 0 );
    count = MAX_COUNT;

    passed = false;
    play();

    if ( my_secret_value != 0 && ! passed )
      fail();

  }

  fprintf( fout, "Nika a obtinut 10 puncte!\n" );

  return 0;
}

