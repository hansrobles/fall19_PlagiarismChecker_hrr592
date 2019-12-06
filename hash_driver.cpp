//Hans Matthew Robles
//hrr592
//12/06/2019

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>

#include "dir.h"
#include "hash.h"

using namespace std;

int main(int argc, char** argv){
  int chunkNum;
  int copyCheck;
  string dir;

  chunkNum = atoi(argv[2]);
  copyCheck = atoi(argv[3]);
  char *dirHold = argv[1];
    
  for(int i = 0; dirHold[i] != 0; i++){                                                //converts character array to string
    dir.push_back(dirHold[i]);
  }

  Dir d(dir, chunkNum, copyCheck);
  d.setDir();
  d.cheatCheck();
  d.showCheaters();

  return 0;
}
