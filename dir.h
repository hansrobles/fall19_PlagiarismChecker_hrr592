//Hans Matthew Robles
//hrr592
//12/06/2019

#ifndef DIR_H
#define DIR_H

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "hash.h"

using namespace std;

class Dir {

  private:
    struct filePair {
      string pairNames;
      int pairCount;
      
      bool operator >(const filePair& rhs) const          //used to sort through the different similar documents
      {
        return (pairCount < rhs.pairCount);
      }
    };

    string dirName;
    vector<filePair> filePairs;
    vector<string> fileNames;

    int chunkNum;                                         //sets number of words in a chunk
    int copyCheck;                                        //sets number of similar chunks to be considered cheating

  public:

    Dir(string dir, int chunkNum, int check);

    /*Sets up all of the available file names in a given directory
      Pre: dirName must be a valid string that pertains to a valid directory
      Post: fileNames.size() > 0
    */
    int setDir();

    /*Uses hash tables to determine how similar each docs are to each other
      Pre: fileNames.size(), each entry is a valid file in the directory
      Post: filePaies.size() > 0, unless docs are not similar to each other by the defined copyCheck
    */
    void cheatCheck();

    /*Displays all of the possible similar docs
      Pre: entries in filePairs cannot be invalid files
    */
    void showCheaters();

    ~Dir(){
      fileNames.clear();
    };

};

#endif
