//Hans Matthew Robles
//hrr592
//12/06/2019

#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cmath>
#include <fstream>

using namespace std;

class HashTable {

  private:
    struct file{
      int fileIndex;                                                                              //based on the passed vector of strings
      int copyCount;                                                                              //used to increment for every similar chunk
    };

    string directory;
    vector <file> files;
    vector <string> fileNames;
    vector <string> hashArr;                                                                      //the hash table

    int refIndex;                                                                                 //reference file to compare other files with
    int chunkMax;
    int copyCheck;
    int tableSize;                                                         

  public:
    HashTable(string dir, int refIndex, int chunkNum, int check, vector<string> fileNames); 
    
    /*Initializes the hash table using the reference file passed
      Pre: refIndex must be a valid index on the passed vector of strings, and must not be fileNames.size() - 1
      Post: created a vector of strings hash table, where sections where the chunks are stored != "empty"
    */
    void initTable();

    /*Uses the chunk passed to return a key index to where a chunk will be stored or compared
      Pre: chunk is not empty
      Post: returns a valid index to the hash table
    */
    int hashFunction(string chunk);

    /*Compares the other files in the directory to the refFile
      Pre: refIndex + 1 must be a valid index to fileNames
      Post: copyCount for each file compared will be incremented based on similar chunk
    */
    void checkForCopies();

    /*Returns a vector of int based on docs who have equal or greater number of similar chunks based on the copyCheck criteria
      Pre condition similar to checkForCopies
    */
    vector<int> retCheaters();

    ~HashTable() {files.clear();}

};

#endif
