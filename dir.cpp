#include "dir.h"

using namespace std;

  Dir::Dir(string dir, int _chunkNum, int check)
  {
    dirName = dir;
    copyCheck = check;
    chunkNum = _chunkNum;
  }
    
  int Dir::setDir()
  {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dirName.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening " << dirName << endl;
      return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
      string stringHold = string(dirp->d_name);
      if(stringHold[stringHold.length() - 1] == 't'){
        fileNames.push_back(string(dirp->d_name));
      }
    }

    closedir(dp);
    return 0;
  }

  void Dir::cheatCheck()
  { 
      for(int i = 0; i < (fileNames.size()-1); i++){                                           //uses hash tables to check similar docs
        HashTable h(dirName, i, chunkNum, copyCheck, fileNames);                               //for each reference file, only files with larger indexes are
        h.initTable();                                                                         //checked to prevent doubles
        h.checkForCopies();
        vector<int> copyHold = h.retCheaters();

        for(int j = 0; j < copyHold.size(); j = j + 2){
          filePair temp;
          temp.pairNames = ": " + fileNames.at(i) + ", " + fileNames.at(copyHold.at(j));       //formats the output
          temp.pairCount = copyHold.at(j+1);
          filePairs.push_back(temp);
        }
      }
  }

  void Dir::showCheaters()
  {
    for(int i = 0; i < filePairs.size(); i++){                                                 //uses insertion sort so that the file(s) with the largest
      int best = i;                                                                            //number of similar chunks are at the top
   
      for(int j = i+1; j < filePairs.size(); j++){
        if((filePairs.at(j)).pairCount > (filePairs.at(best)).pairCount){
          best = j;
        }
      }

      filePair temp = filePairs[i];
      filePairs[i] = filePairs[best];
      filePairs[best] = temp;
    }

    for(int i = 0; i < filePairs.size(); i++){                                                 //outputs files in order
      cout << (filePairs.at(i)).pairCount << (filePairs.at(i)).pairNames << endl;
    }
  }
