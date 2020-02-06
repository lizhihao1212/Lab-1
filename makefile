linker: linkList.cpp linkList.hpp main.cpp readFile.cpp readFile.hpp printMemMap.cpp printMemMap.hpp 
	g++ -std=c++0x linkList.cpp linkList.hpp main.cpp readFile.cpp readFile.hpp printMemMap.cpp printMemMap.hpp -o linker

clean:
	rm -f linkList*~ readFile*~ printMemMap*~ main*~ makefile*~
 