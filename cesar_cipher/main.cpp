#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::atoi;
using std::tolower;
using std::toupper;
using std::isupper;

int main(int argc, char* argv[]){
	if(argc != 4){//4=1+3 because program name counts as argument
		std::cout << "usage: cipher <key> <source file> <target file>" << std::endl;
		return 1;
	}

	int key = atoi(argv[1]);
	std::ofstream target(argv[3], std::ios_base::out);
	std::ifstream source(argv[2], std::ios_base::in);
	char nextChar;
	while(source.get(nextChar)){
		if(isalpha(nextChar)){
			bool upper = isupper(nextChar);
			nextChar = tolower(nextChar) - 97;//97 corresponds to a, shift so we can use mod
			nextChar = (nextChar + key) % 26;
			nextChar = nextChar + 97;//shift back
			if(upper)
				nextChar = toupper(nextChar);
		}
		target.put(nextChar);
	}
	return 0;
}
