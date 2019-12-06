Hans Matthew Robles
hrr592
12/06/2019
Instructions for using Plagiarism Catcher

1) After make, executable file name is "plagiarismCatcher"
2) Enter in order of directory, number of words in a chunk, number of similar chunks to be considered plagiarised.
   Ex:  ./plagiarismCatcher path/to/files 6 200
3) Since the hash function uses the sum of characters in a chunk, long continuous words, like a website, might cause a segfault because it might overflow and turn into a negative number
4) Program will ignore files in a directory that does not end in .txt
5) Program will stop reading a file when it reaches "<br>"; therefore, number of matching chunks detected will be smaller compared to other programs in the class
6) Code is available at github.com/hansrobles/fall19_PlagiarismChecker_hrr592

