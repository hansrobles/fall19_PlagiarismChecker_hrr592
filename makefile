final: hash_driver.o dir.o hash.o
	g++ -o plagiarismCatcher hash_driver.o dir.o hash.o
driver: hash_driver.cpp dir.h hash.h
	g++ -c hash_driver.cpp
dir.o: dir.cpp dir.h hash.h
	g++ -c dir.cpp
hash.o: hash.cpp hash.h
	g++ -c hash.cpp
