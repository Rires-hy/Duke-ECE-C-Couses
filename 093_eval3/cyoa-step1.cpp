#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include "story.hpp"

int main(int argc,char ** argv) {
    //check correct input
    if (argc!=2){
        std::cout<<"invalid input argument"<<std::endl;
        exit(EXIT_FAILURE);
    }
    story a; 
    //read the story text
    a.readstory(argv[1]);
    //parse story
    a.parsestory();
    //parse each page
    a.parsepage();
    //print story
    a.printstory(argv[1]);
	return 0;
}

