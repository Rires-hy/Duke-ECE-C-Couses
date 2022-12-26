#include "story.hpp"

#include <algorithm>  // std::find
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>  // std::vector

story::story() {
}

story::~story() {
}
Page::Page() {
}

Page::~Page() {
}

//read raw text from input file
void story::readstory(char * argcin) {
  //open file from directory
  std::ifstream f;
  std::string filepath(argcin);
  storypath = argcin;
  //append the stroy.txt to the end of input path
  filepath.append("/story.txt", 10);
  f.open(filepath);
  //check for invalid input file
  if (!f.is_open()) {
    std::cout << "cannot open file" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::string buffer;
  //store each line into this vector string
  while (getline(f, buffer)) {
    this->storyin.push_back(buffer);
  }
  f.close();
}

//judge the type of page accoridng to the first line
int story::judgeType() {
  //separate the first line
  std::string Navi = this->storyin.front();
  //start judge
  if (Navi.compare(0, 3, "WIN") == 0) {
    return 1;
  }
  else if (Navi.compare(0, 4, "LOSE") == 0) {
    return 2;
  }
  else {
    size_t i = 0;
    //find the position of ":"
    if (Navi.find(":") >= 1) {
      size_t col = Navi.find(":");
      // NAVY is a line
      std::string str = Navi.substr(0, col);
      // char * pagenumber;
      // //copy the page number into char *
      // size_t numberLenght=Navi.copy(pagenumber,col-0,0);
      //check for digit
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          return 0;
        }
      }
      //convert to integer
      int pageN = 0;
      pageN = std::stoi(str);
      if (pageN > 0) {
        return 3;
      }
    }
    return 0;
  }
}

//read the story page and store the content for later print:
void story::parsestory() {
  std::vector<std::string>::iterator it = storyin.begin();
  //read from each line of story.txt
  while (it != storyin.end()) {
    //store this line to temp
    std::string temp = *it;
    int posA = temp.find("@");
    int posCol = temp.find(":");
    if (posA != -1) {
      std::string str = temp.substr(0, posA);
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Page temppage;
      temppage.pagenum = pageN;
      temppage.raw.push_back(*it);
      Pages.push_back(temppage);
    }
    else if (posCol != -1) {
      std::string str = temp.substr(0, posCol);
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Pages[pageN].raw.push_back(*it);
    }
    else {
    }
    it++;
  }
}

//parse the page
void story::parsepage() {
  for (int i = 0; i < Pages.size(); i++) {
    //parse first line:
    std::string str = Pages[i].raw.front();
    int posA = str.find("@");
    if (posA != -1) {
      //there is at least an @
      if (((str.find("@", posA + 1)) == -1) &&
          ((str.find(":", posA) != -1))) {  //store the page type and take page path:
        if (str.compare(posA + 1, 1, "W") == 0) {
          Pages[i].Type = 1;
        }
        else if (str.compare(posA + 1, 1, "L") == 0) {
          Pages[i].Type = 2;
        }
        else if (str.compare(posA + 1, 1, "N") == 0) {
          Pages[i].Type = 3;
        }
        else {
          std::cout << "invalid page type" << std::endl;
          exit(EXIT_FAILURE);
        }

        //store page path:
        // int eol=str.find("\n");
        int col = str.find(":", posA);
        Pages[i].pagepath = str.substr(col + 1);
      }
      else {
        std::cout << "invalid declaration line: more than 1 @" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
    else {
      std::cout << "invalid declaration line: no @" << std::endl;
      exit(EXIT_FAILURE);
    }

    //store the choice and next page number:
    if ((Pages[i].Type == 1) || (Pages[i].Type == 2)) {
      std::vector<std::string>::iterator it = Pages[i].raw.begin();
      std::vector<std::string>::iterator end = Pages[i].raw.end();
      for (it = Pages[i].raw.begin() + 1; it != end; ++it) {
        std::string temm = *it;
        if (temm.find(":") != -1) {
          std::cout << "Win and Lose pages MUST NOT have any choices" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
    }
    else if (Pages[i].Type == 3) {
      std::vector<std::string>::iterator it = Pages[i].raw.begin();
      std::vector<std::string>::iterator end = Pages[i].raw.end();
      for (it = Pages[i].raw.begin() + 1; it != end; ++it) {
        std::string temm = *it;
        int firstcol = temm.find(":");
        if (firstcol != -1) {
          int sedcol = temm.find(":", firstcol + 1);
          if (sedcol != -1) {
            //start to store:
            choice_t tempChoice;
            std::string strPagenum = temm.substr(firstcol + 1, sedcol - firstcol - 1);
            //convert to digit
            for (int i = 0; i < strPagenum.size(); i++) {
              if (isdigit(strPagenum[i]) == 0) {
                std::cout << "invalid page number" << std::endl;
                exit(EXIT_FAILURE);
              }
            }
            tempChoice.nextpage = std::stoi(strPagenum);
            //
            tempChoice.choicetxt = temm.substr(sedcol + 1);
            Pages[i].choices.push_back(tempChoice);
          }
          else {
            std::cout << "only one : in choice" << std::endl;
            exit(EXIT_FAILURE);
          }
        }
        else {
          std::cout << "invalid choice" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
    }
  }
}
//print the page according to the type
void story::printstory(char * argcin) {
  std::vector<Page>::iterator it = Pages.begin();
  std::vector<Page>::iterator end = Pages.end();
  for (; it != end; ++it) {
    int i = it - Pages.begin();
    std::cout << "Page " << i << std::endl;
    std::cout << "==========" << std::endl;
    if (Pages[i].Type == 3) {
      //open page file and print:
      std::ifstream f;
      std::string filepath = argcin;
      //append the stroy.txt to the end of input path
      filepath += '/';
      filepath += Pages[i].pagepath;
      f.open(filepath);
      //check for invalid input file
      if (!f.is_open()) {
        std::cout << "cannot open this page file" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string buffer;
      //store each line into this vector string
      while (getline(f, buffer)) {
        std::cout << buffer << std::endl;
      }
      //print as required:
      std::cout << std::endl;
      std::cout << "What would you like to do?" << std::endl;
      std::cout << std::endl;
      //print choice:
      for (int j = 0; j < Pages[i].choices.size(); j++) {
        std::cout << " " << j + 1 << ". " << Pages[i].choices[j].choicetxt << std::endl;
      }
      f.close();
    }
    else if ((Pages[i].Type == 1) || (Pages[i].Type == 2)) {
      //open page file and print:
      std::ifstream f;
      std::string filepath = argcin;
      //append the stroy.txt to the end of input path
      filepath += '/';
      filepath += Pages[i].pagepath;
      f.open(filepath);
      //check for invalid input file
      if (!f.is_open()) {
        std::cout << "cannot open this page file" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string buffer;
      //store each line into this vector string
      while (getline(f, buffer)) {
        std::cout << buffer << std::endl;
      }
      //print as required:
      std::cout << std::endl;
      if (Pages[i].Type == 1) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
      }
      else if (Pages[i].Type == 2) {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
      }
      //close this file
      f.close();
    }
  }
}
void story::checkstory() {
  //nextpage vector
  std::vector<int> nextVec;
  //win and lose counter:
  int winNum = 0;
  int loseNum = 0;
  std::vector<Page>::iterator it = Pages.begin();
  std::vector<Page>::iterator end = Pages.end();
  int totalpage = Pages.size();
  //for each choice-page, check each reference is valid:
  for (; it != end; ++it) {
    int i = it - Pages.begin();
    if (Pages[i].Type == 3) {
      for (int j = 0; j < Pages[i].choices.size(); j++) {
        nextVec.push_back(Pages[i].choices[j].nextpage);
        if (Pages[i].choices[j].nextpage > totalpage) {
          std::cout << "target page not in the story " << std::endl;
          exit(EXIT_FAILURE);
        }
      }
    }
    else if (Pages[i].Type == 1) {
      winNum++;
    }
    else if (Pages[i].Type == 2) {
      loseNum++;
    }
  }
  //check every page (except page 0) is referenced by at least one *other*page's choices.
  std::vector<int>::iterator it2;
  for (int k = 1; k < Pages.size(); k++) {
    it2 = find(nextVec.begin(), nextVec.end(), k);
    if (it2 != nextVec.end()) {
      //found
    }
    else {
      std::cout << "some page is not referenced by at least 1 page " << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  //check for at least one win page and one lose page
  if ((winNum < 1) || (loseNum < 1)) {
    std::cout << "there is no at least 1 win page or one 1 page " << std::endl;
    exit(EXIT_FAILURE);
  }
}
void story::printpage(int i) {
  if (Pages[i].Type == 3) {
    //open page file and print:
    std::ifstream f;
    std::string filepath = storypath;
    //append the stroy.txt to the end of input path
    filepath += '/';
    filepath += Pages[i].pagepath;
    f.open(filepath);
    //check for invalid input file
    if (!f.is_open()) {
      std::cout << "cannot open this page file" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string buffer;
    //store each line into this vector string
    while (getline(f, buffer)) {
      std::cout << buffer << std::endl;
    }
    //print as required:
    std::cout << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    //print choice:
    for (int j = 0; j < Pages[i].choices.size(); j++) {
      std::cout << " " << j + 1 << ". " << Pages[i].choices[j].choicetxt << std::endl;
    }
    f.close();
  }
  else if ((Pages[i].Type == 1) || (Pages[i].Type == 2)) {
    //open page file and print:
    std::ifstream f;
    std::string filepath = storypath;
    //append the stroy.txt to the end of input path
    filepath += '/';
    filepath += Pages[i].pagepath;
    f.open(filepath);
    //check for invalid input file
    if (!f.is_open()) {
      std::cout << "cannot open this page file" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string buffer;
    //store each line into this vector string
    while (getline(f, buffer)) {
      std::cout << buffer << std::endl;
    }
    //print as required:
    std::cout << std::endl;
    if (Pages[i].Type == 1) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (Pages[i].Type == 2) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    f.close();
  }
}
//begin story
void story::beginstory() {
  int curpage = 0;
  while ((Pages[curpage].Type != 1) && (Pages[curpage].Type != 2)) {
    //print current page:
    printpage(curpage);

    //can exit?
    if ((Pages[curpage].Type == 1) || (Pages[curpage].Type == 2)) {
      return;
    }
    else {
      std::string instr;
      int inputNum = 0;
      int valid = 0;
      while (valid != 2) {
        std::cin >> instr;
        //judge if valid:
        for (int i = 0; i < instr.size(); i++) {
          if (isdigit(instr[i]) == 0) {
            valid = 0;
          }
          else {
            valid = 1;
          }
        }
        //convert to integer
        if (valid == 1) {
          inputNum = std::stoi(instr);
        }

        if ((inputNum <= Pages[curpage].choices.size()) && (inputNum > 0)) {
          valid = 2;
          //go to that page:
          curpage = Pages[curpage].choices[inputNum - 1].nextpage;
        }
        else {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
      }
    }
  }
  printpage(curpage);
  return;
}

//the recursive way to find the path:
void story::dfs(story & sty, int currPage) {
  //base case
  if (Pages[currPage].Type == 1) {
    path.push_back(std::make_pair(currPage, -1));
    paths.push_back(path);
    return;
  }
  if (Pages[currPage].Type == 2) {
    return;
  }
  //store the nextpage number for each choices
  for (int i = 0; i < Pages[currPage].choices.size(); i++) {
    path.push_back(std::make_pair(currPage, i + 1));
    dfs(sty, Pages[currPage].choices[i].nextpage);
    if (path[path.size() - 1].second == -1) {
      path.pop_back();
    }
    path.pop_back();
  }
}

//display the winpath:
void story::winpath() {
  //do recuirsive function:
  dfs(*this, 0);
  // print the paths after finding all paths
  for (int i = 0; i < paths.size(); i++) {
    for (int j = 0; j < paths[i].size(); j++) {
      if (paths[i][j].second == -1) {
        std::cout << paths[i][j].first << "(win)" << std::endl;
      }
      else {
        std::cout << paths[i][j].first << "(" << paths[i][j].second << "),";
      }
    }
  }
}

//parse the story and store the content to each page
void story::parsestorys4() {
  std::vector<std::string>::iterator it = storyin.begin();
  //read from each line of story.txt
  while (it != storyin.end()) {
    //store this line to temp
    std::string temp = *it;
    int posA = temp.find("@");
    int posCol = temp.find(":");
    //find: "["
    int posbra = temp.find("[");
    //find "&"
    int posdollar = temp.find("$");
    if (posA != -1) {
      std::string str = temp.substr(0, posA);
      //convert to int:
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Page temppage;
      temppage.pagenum = pageN;
      temppage.raw.push_back(*it);
      Pages.push_back(temppage);
    }
    //deal with "$"
    else if (posdollar != -1) {
      std::string str = temp.substr(0, posdollar);
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Pages[pageN].raw.push_back(*it);
    }
    //deal with "["
    else if (posbra != -1) {
      std::string str = temp.substr(0, posbra);
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Pages[pageN].raw.push_back(*it);
    }
    //
    //store the value of pagenumber:
    else if (posCol != -1) {
      std::string str = temp.substr(0, posCol);
      for (int i = 0; i < str.size(); i++) {
        if (isdigit(str[i]) == 0) {
          std::cout << "invalid page number" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      int pageN = 0;
      pageN = std::stoi(str);
      Pages[pageN].raw.push_back(*it);
    }
    else {
    }
    it++;
  }
}

//parse each page
void story::parsepages4(int i) {
  //parse first line:
  std::string str = Pages[i].raw.front();
  int posA = str.find("@");
  if (posA != -1) {
    //there is at least an @
    if (((str.find("@", posA + 1)) == -1) &&
        ((str.find(":", posA) != -1))) {  //store the page type and take page path:
      if (str.compare(posA + 1, 1, "W") == 0) {
        Pages[i].Type = 1;
      }
      else if (str.compare(posA + 1, 1, "L") == 0) {
        Pages[i].Type = 2;
      }
      else if (str.compare(posA + 1, 1, "N") == 0) {
        Pages[i].Type = 3;
      }
      else {
        std::cout << "invalid page type" << std::endl;
        exit(EXIT_FAILURE);
      }

      //store page path:
      // int eol=str.find("\n");
      int col = str.find(":", posA);
      Pages[i].pagepath = str.substr(col + 1);
    }
    else {
      std::cout << "invalid declaration line: more than 1 @" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  else {
    std::cout << "invalid declaration line: no @" << std::endl;
    exit(EXIT_FAILURE);
  }

  //store the choice and next page number:
  if ((Pages[i].Type == 1) || (Pages[i].Type == 2)) {
    std::vector<std::string>::iterator it = Pages[i].raw.begin();
    std::vector<std::string>::iterator end = Pages[i].raw.end();
    for (it = Pages[i].raw.begin() + 1; it != end; ++it) {
      std::string temm = *it;
      if (temm.find(":") != -1) {
        std::cout << "Win and Lose pages MUST NOT have any choices" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  // N: normal type
  else if (Pages[i].Type == 3) {
    std::vector<std::string>::iterator it = Pages[i].raw.begin();
    std::vector<std::string>::iterator end = Pages[i].raw.end();
    //parse each line:
    for (it = Pages[i].raw.begin() + 1; it != end; ++it) {
      std::string temm = *it;
      int firstcol = temm.find(":");
      int dollar = temm.find("$");
      if (firstcol != -1) {
        int sedcol = temm.find(":", firstcol + 1);
        if (sedcol != -1) {
          //start to store:
          choice_t tempChoice;
          std::string strPagenum = temm.substr(firstcol + 1, sedcol - firstcol - 1);
          //convert to digit
          for (int i = 0; i < strPagenum.size(); i++) {
            if (isdigit(strPagenum[i]) == 0) {
              std::cout << "invalid page number" << std::endl;
              exit(EXIT_FAILURE);
            }
          }
          tempChoice.nextpage = std::stoi(strPagenum);
          tempChoice.choicetxt = temm.substr(sedcol + 1);
          //judge for "[]" type
          int posbra = temm.find("[");
          if (posbra != -1) {
            int posequ = temm.find("=");
            int posbra2 = temm.find("]");
            if ((posequ != -1) && (posbra2 != -1)) {
              tempChoice.condtxt = temm.substr(posbra + 1, posequ - posbra - 1);
              std::string tempcondNum = temm.substr(posequ + 1, posbra2 - posequ - 1);
              //convert to int
              for (int i = 0; i < tempcondNum.size(); i++) {
                if (isdigit(tempcondNum[i]) == 0) {
                  std::cout << "invalid object number" << std::endl;
                  exit(EXIT_FAILURE);
                }
              }
              tempChoice.cond = std::stoi(tempcondNum);
            }
          }
          else {
            tempChoice.cond = -9988;
          }
          //end judge for "[]" type
          tempChoice.ava = 0;
          Pages[i].choices.push_back(tempChoice);
          //test if first meet:
          int firstmeet = 0;
          std::vector<equip_t>::iterator itcop = equips.begin();
          while (itcop != equips.end()) {
            if (tempChoice.condtxt.compare(itcop->equipName) == 0) {
              firstmeet = 1;
            }
            itcop++;
          }
          if (firstmeet == 0) {
            equip_t tempeqp;
            tempeqp.equiptag = 0;
            tempeqp.equipName = tempChoice.condtxt;
            //store the equips if it was the first meet:
            equips.push_back(tempeqp);
          }
        }
        else {
          std::cout << "only one : in choice" << std::endl;
          exit(EXIT_FAILURE);
        }
      }
      //if there is dollar $
      else if (dollar != -1) {
        int posequal = temm.find("=");
        equip_t tempEquip;
        if (posequal != -1) {  // if there is "="
          //store the equipment name
          tempEquip.equipName = temm.substr(dollar + 1, posequal - dollar - 1);
          //store the equipment number:
          std::string tempNum = temm.substr(posequal + 1);
          //conver to int:
          for (int i = 0; i < tempNum.size(); i++) {
            if (isdigit(tempNum[i]) == 0) {
              std::cout << "invalid page number" << std::endl;
              exit(EXIT_FAILURE);
            }
          }
          tempEquip.equiptag = std::stoi(tempNum);
          equips.push_back(tempEquip);
        }
      }
      else {
        std::cout << "invalid choice in step 4" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
}

//print each page according to requirement:
void story::printpages4(int i) {
  if (Pages[i].Type == 3) {
    //open page file and print:
    std::ifstream f;
    std::string filepath = storypath;
    //append the stroy.txt to the end of input path
    filepath += '/';
    filepath += Pages[i].pagepath;
    f.open(filepath);
    //check for invalid input file
    if (!f.is_open()) {
      std::cout << "cannot open this page file" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string buffer;
    //store each line into this vector string
    while (getline(f, buffer)) {
      std::cout << buffer << std::endl;
    }
    //print as required:
    std::cout << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << std::endl;
    //print choice:
    for (int j = 0; j < Pages[i].choices.size(); j++) {
      if (Pages[i].choices[j].cond == -9988) {
        std::cout << " " << j + 1 << ". " << Pages[i].choices[j].choicetxt << std::endl;
        Pages[i].choices[j].ava = 0;
      }
      else {  //compare the equipment with the choices requirement:
        equip_t comp;
        comp.equiptag = Pages[i].choices[j].cond;
        comp.equipName = Pages[i].choices[j].condtxt;
        std::vector<equip_t>::iterator it = find(equips.begin(), equips.end(), comp);
        if (it == equips.end()) {
          //print <UNAVAILABLE>
          std::cout << " " << j + 1 << ". "
                    << "<UNAVAILABLE>" << std::endl;
          Pages[i].choices[j].ava = 1;
        }
        else {
          std::cout << " " << j + 1 << ". " << Pages[i].choices[j].choicetxt << std::endl;
          Pages[i].choices[j].ava = 0;
        }
      }
    }
    f.close();
  }
  else if ((Pages[i].Type == 1) || (Pages[i].Type == 2)) {
    //open page file and print:
    std::ifstream f;
    std::string filepath = storypath;
    //append the stroy.txt to the end of input path
    filepath += '/';
    filepath += Pages[i].pagepath;
    f.open(filepath);
    //check for invalid input file
    if (!f.is_open()) {
      std::cout << "cannot open this page file" << std::endl;
      exit(EXIT_FAILURE);
    }
    std::string buffer;
    //store each line into this vector string
    while (getline(f, buffer)) {
      std::cout << buffer << std::endl;
    }
    //print as required:
    std::cout << std::endl;
    if (Pages[i].Type == 1) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (Pages[i].Type == 2) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    f.close();
  }
}

//begin story s4
void story::beginstorys4() {
  int curpage = 0;
  parsepages4(curpage);
  while ((Pages[curpage].Type != 1) && (Pages[curpage].Type != 2)) {
    //print current page:
    printpages4(curpage);

    //can exit?
    if ((Pages[curpage].Type == 1) || (Pages[curpage].Type == 2)) {
      return;
    }
    else {
      std::string instr;
      int inputNum = 0;
      int valid = 0;
      while (valid != 2) {
        std::cin >> instr;
        //judge if valid int:
        for (int i = 0; i < instr.size(); i++) {
          if (isdigit(instr[i]) == 0) {
            valid = 0;
          }
          else {
            valid = 1;
          }
        }
        //convert to integer
        if (valid == 1) {
          inputNum = std::stoi(instr);
        }
        //check if it is unavailable and invalid choice
        if ((inputNum <= Pages[curpage].choices.size()) && (inputNum > 0)) {
          if (Pages[curpage].choices[inputNum - 1].ava == 0) {
            valid = 2;
            //go to that page:
            curpage = Pages[curpage].choices[inputNum - 1].nextpage;
            parsepages4(curpage);
          }
          else {
            std::cout << "That choice is not available at this time, please try again"
                      << std::endl;
          }
        }
        else {
          std::cout << "That is not a valid choice, please try again" << std::endl;
        }
      }
    }
  }
  printpages4(curpage);
  return;
}
