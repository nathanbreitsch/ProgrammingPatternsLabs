//
//  main.cpp
//  diff
//
//  Created by is-Lib on 8/28/14.
//  Copyright (c) 2014 is-Lib. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>

#define MAX_LINE_WIDTH 1024

int main(int argc, const char * argv[])
{
    if(argc != 3){//the name of the program counts as an argument
        std::cout << "usage: diff <file1> <file2>" << std::endl;
        return 1;
    }
    std::ifstream file1(argv[1]);
    std::ifstream file2(argv[2]);
    std::string lineFile1, lineFile2;
    int lineNum = 0;
        
    while(std::getline(file1, lineFile1) && std::getline(file2, lineFile2)){
        if (lineFile1.compare(lineFile2) != 0){
            std::cout << "file1: " << lineNum << " " << lineFile1 << std::endl;
            std::cout << "file2: " << lineNum << " " << lineFile2 << std::endl;
        }
        ++lineNum;
    }

    while(std::getline(file1, lineFile1)){
	std::cout << "file1: " << lineNum << " " << lineFile1 << std::endl;
	std::cout << "file2: " << lineNum << " " << "" << std::endl;
	++lineNum;
    }



    while(std::getline(file2, lineFile2)){
	std::cout << "file1: " << lineNum << " " << "" << std::endl;
	std::cout << "file2: " << lineNum << " " << lineFile2 << std::endl;
	++lineNum;
    }

   return 0;
}

