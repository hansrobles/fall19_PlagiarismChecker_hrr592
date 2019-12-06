#include "hash.h"

using namespace std;

  HashTable::HashTable(string dir, int _refIndex, int chunkNum, int check, vector<string> _fileNames)
  {
    directory = dir;
    refIndex = _refIndex;   
    copyCheck = check;
    chunkMax = chunkNum;
    fileNames = _fileNames;    

    for(int i = refIndex + 1; i < fileNames.size(); i++){                                                  //initializes vector of files for comparisons
      file temp;
      temp.fileIndex = i;
      temp.copyCount = 0;
      files.push_back(temp);
    }

    tableSize = 100003;                                                                                   //uses large prime number to prevent false
  }                                                                                                       //positive comparisons

  void HashTable::initTable()
  {
    hashArr.resize(tableSize, "empty");                                                                   //fills the hashtable with "empty" string to
                                                                                                          //account for the empty spaces in hash table
    bool lineFlag = true;                                                                                 //stops reading file when <br> line is reached
    int chunkCount = 0;                                                                                

    string word;                                                                                          //uses to hold the word read from file
    string wordHold;                                                                                      //modified the word variable to be alpha numeric
    string chunk;                                                                                         
    string fileAccess = directory + "/" + fileNames.at(refIndex);
              
    ifstream file1(fileAccess.c_str());
    while((file1 >> word)&&(lineFlag)){
      if((word[0]!='<')||(word[1]!='b')||(word[2]!='r')||(word[3]!='>')){                                 //checks for <br> line
        for(string::iterator it = word.begin(); it != word.end(); it++){                                  
          if((*it >= 48 && *it <= 57)||(*it >= 65 && *it <= 90)||(*it >= 97 && *it <= 122)){              //ony places alpha numeric chars into wordHold
            if(*it >= 65 && *it <= 90){
              wordHold.push_back(*it + 32);                                                               //changes uppercase to lowercase
            }else{
              wordHold.push_back(*it);
            }
          }
        }
          
        chunk = chunk + wordHold;
        chunkCount ++;                                                                                    //counts how many words are in chunk

        if(chunkCount == chunkMax){                                                                       //modifies hashtable when max words are in chunk
          int key = hashFunction(chunk);
          hashArr[key] = "chunk";                                                                         //places each chunk into hash table

          chunkCount = 0;                                                                                 //resets variables
          chunk.clear();
        }
        
        wordHold.clear();  
      }else{
        lineFlag = false;                                                                                 //flag to stop reading when <br> is reached
      }       
    }
    
    file1.close();
    
    return;
  }
                      
  int HashTable::hashFunction(string chunk)
  {
    int sumofChar  = chunk[0] + chunk[chunk.length()-1];                                                  //adds first and last char
    int chunkCount = 0;

    for(string::iterator it = chunk.begin(); it != chunk.end(); it++){                                    //sum of all char in string
      chunkCount = chunkCount + *it;
    }

    return ((chunkCount * sumofChar)%tableSize);                                                          //complexity to prevent false positives
  }

  void HashTable::checkForCopies()
  {
    for(int i = 0; i < files.size(); i++){
      file hold = files.at(i);                                                                            //traverses to other files in directory for
      bool lineFlag = true;                                                                               //comparisons
      int chunkCount = 0;

      string word;
      string wordHold;
      string chunk;
      string fileAccess = directory + "/" + fileNames.at(hold.fileIndex);
      ifstream file1(fileAccess.c_str());
      while((file1 >> word)&&(lineFlag)){
        if((word[0]!='<')||(word[1]!='b')||(word[2]!='r')||(word[3]!='>')){
          for(string::iterator it = word.begin(); it != word.end(); it++){
            if((*it >= 48 && *it <= 57)||(*it >= 65 && *it <= 90)||(*it >= 97 && *it <= 122)){
              if(*it >= 65 && *it <= 90){
                wordHold.push_back(*it + 32);
              }else{
                wordHold.push_back(*it);
              }
            }
          }

          chunk = chunk + wordHold;
          chunkCount ++;

          if(chunkCount == chunkMax){
            int key = hashFunction(chunk);

            if(hashArr.at(key) != "empty"){                                                              //if chunk from this file is similar to a chunk in
              hold.copyCount = hold.copyCount + 1;                                                       //reference file, similarity counter is incremented
            }

            chunkCount = 0;
            chunk.clear();
          }

          wordHold.clear();
        }else{
          lineFlag = false;
        }
      }

      file1.close();
      
      files[i] = hold;                                                                                   //adds the new similarity counter to each file
    }
  }

  vector <int> HashTable::retCheaters()
  {
    vector <int> result;                                                                                 //every odd index 

    for(int i = 0; i < files.size(); i++){
      if((files.at(i)).copyCount >= copyCheck){
        file temp = files.at(i);
        result.push_back(temp.fileIndex);
        result.push_back(temp.copyCount);
      }
    }
    
    return result;
  }
