#include "page.h"
//implementation of strtol
long int strtol_new(string s) {
  char * pEnd;
  errno = 0;
  long int num = std::strtol(s.c_str(), &pEnd, 10);
  if (errno != 0 or *pEnd != '\0') {
    error(WRONG_STORY_FORMAT);
  }
  return num;
}
//implementation of strtoull
size_t strtoull_new(string s) {
  char * pEnd;
  errno = 0;
  size_t num = std::strtoull(s.c_str(), &pEnd, 10);
  if (errno != 0 || *pEnd != '\0') {
    error(WRONG_STORY_FORMAT);
  }
  return num;
}

class Story {
 private:
  vector<Page> pages;

 public:
  //constructor
  Story() : pages(vector<Page>()) {}
  Story(const Story & rhs) : pages(vector<Page>()) {
    for (size_t i = 0; i < rhs.pages.size(); i++) {
      pages.push_back(rhs.pages[i]);
    }
  }
  //assignment
  Story & operator=(const Story & rhs) {
    if (this != &rhs) {
      vector<Page> temp = vector<Page>();
      for (size_t i = 0; i < rhs.pages.size(); i++) {
        temp.push_back(rhs.pages[i]);
      }
      pages = temp;
    }
    return *this;
  }
  //destructor
  ~Story() {}
  //add a page to "Story"
  void addPage(const Page & p) {
    if (p.pageNum != pages.size()) {
      error(PAGE_ORDER);
    }
    pages.push_back(p);
  }
  //read from story.txt to add all contents to "Story"
  void addStory(string directory) {
    string filename = directory + "/story.txt";
    ifstream file(filename.c_str());
    if (!file) {
      error(NO_FILE);
    }
    string line;
    while (getline(file, line)) {
      if (line == "") {
        continue;
      }
      stringstream line_s(line);
      stringstream line_ss(line);
      string num_s;
      string choice_s;
      string pageType_s;
      size_t num, choice, var;

      // type
      // 7$sword=1
      getline(line_ss, num_s, '$');
      getline(line_ss, choice_s, '=');

      bool money = true;  //is there "$" sign in line
      char * pEnd;
      errno = 0;
      num = std::strtoull(num_s.c_str(), &pEnd, 10);
      if (errno != 0 || *pEnd != '\0') {
        money = false;
      }
      getline(line_ss, num_s);
      var = std::strtol(num_s.c_str(), &pEnd, 10);
      if (errno != 0 || *pEnd != '\0') {
        money = false;
      }
      if (money) {
        pages[num].variables.push_back(make_pair(choice_s, var));
        continue;
      }

      getline(line_s, num_s, ':');
      // a line of choice
      // type
      // 6:5:Decline and head out of town
      // or
      // 13[broke=0]:16:Fling your last coins at the dragon
      if (isdigit(num_s[num_s.length() - 1]) or num_s[num_s.length() - 1] == ']') {
        getline(line_s, choice_s, ':');
        choice = strtoull_new(choice_s);
        string condition_s = "$_$_NULL";
        string condition_v_s;
        long int condition_v = 0;
        if (num_s[num_s.length() - 1] == ']') {
          stringstream temp(num_s);
          getline(temp, num_s, '[');
          getline(temp, condition_s, '=');
          getline(temp, condition_v_s, ']');
          condition_v = strtol_new(condition_v_s);
        }
        num = strtoull_new(num_s);
        string line_back;
        getline(line_s, line_back);
        this->choice(num, choice, line_back, condition_s, condition_v);
      }
      // a line of page file
      // type
      // 1@N:croissant.txt
      else {
        stringstream temp(num_s);
        getline(temp, num_s, '@');
        getline(temp, pageType_s);
        if (pageType_s != "N" && pageType_s != "W" && pageType_s != "L") {
          error(WRONG_STORY_FORMAT);
        }
        char pageType = pageType_s.c_str()[0];
        num = strtoull_new(num_s);
        string line_back;
        getline(line_s, line_back);
        if (line_back == "") {
          error(WRONG_STORY_FORMAT);
        }
        this->addPage(Page(num, pageType, directory + "/" + line_back));
      }
    }
    file.close();
  }
  //check if all choices have been referenced
  void checkStory() {
    size_t maxnum = pages.size();
    vector<bool> check(maxnum, false);
    bool win = false;
    bool lose = false;
    for (size_t i = 0; i < maxnum; i++) {
      check[i] = 0;
    }
    for (size_t i = 0; i < maxnum; i++) {
      for (size_t j = 0; j < pages[i].choices.size(); j++) {
        if (0 <= pages[i].choices[j].first and pages[i].choices[j].first < maxnum) {
          check[pages[i].choices[j].first] = true;
        }
        else {
          error(WRONG_CHOICE_SIZE);
        }
      }
      if (pages[i].pageType == 'W') {
        win = true;
      }
      else if (pages[i].pageType == 'L') {
        lose = true;
      }
    }
    if (!win or !lose) {
      error(MISS_PAGE);
    }
    for (size_t i = 1; i < maxnum; i++) {
      if (!check[i]) {
        error(PAGE_NOT_REFERENCED);
      }
    }
  }
  //print all pages of story
  void printStory() {
    for (size_t i = 0; i < pages.size(); i++) {
      cout << "Page " << i << endl;
      cout << "==========" << endl;
      vector<pair<string, long int> > n = vector<pair<string, long int> >();
      pages[i].printPage(n);
    }
  }
  //print story by user input
  void printInputStory(size_t pageNum, vector<pair<string, long int> > & pathVariables) {
    pages[pageNum].printPage(pathVariables);
    if (pages[pageNum].pageType == 'N') {
      addCondition(pages[pageNum].variables, pathVariables);
      size_t x;
      bool goodChoice = false;
      while (!goodChoice) {
        while (!(cin >> x) or x <= 0 or x > pages[pageNum].choices.size()) {
          cin.clear();
          cin.ignore();
          cout << "That is not a valid choice, please try again\n";
        }
        goodChoice = meetCondition(pages[pageNum].conditions[x - 1], pathVariables);
        if (!goodChoice) {
          cout << "That choice is not available at this time, please try again" << endl;
        }
      }
      size_t p = pages[pageNum].choices[x - 1].first;
      printInputStory(p, pathVariables);
    }
  }
  //add a choice and its condition to a page
  void choice(size_t page, size_t l, string s, string ss, long int ll) {
    if (page >= pages.size()) {
      error(PAGE_DECLARE);
    }
    if (pages[page].pageType != 'N') {
      error(NO_CHOICE);
    }
    pages[page].addChoice(l, s);
    pages[page].addVar(ss, ll);
  }
  //recursivly call "findPath" to find all winning path to append to "allPath"
  void findPath(size_t pageNum,
                vector<pair<size_t, size_t> > path,
                vector<vector<pair<size_t, size_t> > > & allPath) {
    if (pages[pageNum].pageType == 'W') {
      path.push_back(make_pair(pageNum, 0));
      allPath.push_back(path);
      return;
    }
    else if (pages[pageNum].pageType == 'L') {
      return;
    }
    for (size_t i = 0; i < path.size(); i++) {
      if (pageNum == path[i].first) {
        return;
      }
    }
    vector<pair<size_t, size_t> > unique =
        vector<pair<size_t, size_t> >();  //choice num, page num
    for (size_t i = 0; i < pages[pageNum].choices.size(); i++) {
      bool notIn = true;
      for (size_t j = 0; j < unique.size(); j++) {
        if (unique[j].second == pages[pageNum].choices[i].first) {
          notIn = false;
        }
      }
      if (notIn) {
        unique.push_back(make_pair(i, pages[pageNum].choices[i].first));
      }
    }
    for (size_t i = 0; i < unique.size(); i++) {
      path.push_back(make_pair(pageNum, unique[i].first + 1));
      findPath(pages[pageNum].choices[unique[i].first].first, path, allPath);
      path.pop_back();
    }
  }
  //print all path in "allPath"
  void printPath(vector<vector<pair<size_t, size_t> > > allPath) {
    if (allPath.size() == 0) {
      cout << "This story is unwinnable!\n";
      return;
    }
    for (size_t i = 0; i < allPath.size(); i++) {
      for (size_t j = 0; j < allPath[i].size(); j++) {
        if (allPath[i][j].second == 0) {
          cout << allPath[i][j].first << "(win)\n";
        }
        else {
          cout << allPath[i][j].first << "(" << allPath[i][j].second << "),";
        }
      }
    }
  }
};
