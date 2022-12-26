#ifndef __SINGLEstory_HPP__
#define __SINGLEstory_HPP__
#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <utility>

struct choice_tag{
    int nextpage;
    std::string choicetxt;
    int cond;//-9988=unconditional else =conditional
    std::string condtxt;
    int ava;
};
typedef struct choice_tag choice_t;

// struct equip_tag{
//     int equiptag;
//     std::string equipName;
// };
// typedef struct equip_tag equip_t;

// equip_t class
class equip_t
{
private:

public: 
    int equiptag;
    std::string equipName;

    bool operator==(const equip_t & eq){
        if((this->equipName == eq.equipName && this->equiptag == eq.equiptag) ){
            return true;
        }
        return false;
    }
    // equip_t();
    // ~equip_t();
};

//

class Page
{
private:

public:
    int Type;//0=invalid type 1=win 2=lose 3=choice
    int pagenum;
    std::vector<choice_t> choices;
    std::string pagepath;
    std::vector<std::string> raw;

    //constructor
	Page();
    //destructor
	~Page();
};

class story
{
private:

public:
    int Type;//0=invalid type 1=win 2=lose 3=choice
    std::vector<std::string> storyin; //row story data
    std::vector<std::string> print;
    std::vector<Page> Pages;
    std::string storypath;
    std::vector<std::pair<int,int>> path;
    std::vector<std::vector<std::pair<int,int>>> paths; 
    std::vector<equip_t> equips;        
    //constructor
	story();
    //destructor
	~story();

    void readstory(char * argv);
    void printstory(char * argv);
    int judgeType();
    void parsestory();
    void parsepage();
    void checkstory();
    void beginstory();
    void printpage(int i);
    void winpath();
    void dfs(story & sty, int currPage);
    void parsestorys4();
    void parsepages4(int i);
    void beginstorys4();
    void printstorys4();
    void printpages4(int i);
};

#endif
