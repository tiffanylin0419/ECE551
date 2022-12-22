#include <errno.h>  //errno

#include <fstream>  //ifstream
#include <sstream>  //stringstream
#include <string>   //string
#include <vector>   //vector

#include "error.h"
using namespace std;
//check if condition is in var(variables)
bool meetCondition(pair<string, long int> & condition,
                   vector<pair<string, long int> > & var) {
  for (size_t i = 0; i < var.size(); i++) {
    if (condition.first == var[i].first) {
      if (condition.second != var[i].second) {
        return false;
      }
      else {
        return true;
      }
    }
  }
  if (condition.second == 0) {
    return true;
  }
  return false;
}

//add variables to pathVariables
void addCondition(vector<pair<string, long int> > & variables,
                  vector<pair<string, long int> > & pathVariables) {
  for (size_t i = 0; i < variables.size(); i++) {
    bool in = false;
    for (size_t j = 0; j < pathVariables.size(); j++) {
      if (variables[i].first == pathVariables[j].first) {
        in = true;
        pathVariables[j].second = variables[i].second;
        break;
      }
    }
    if (!in) {
      pathVariables.push_back(variables[i]);
    }
  }
}

class Page {
 public:
  size_t pageNum;                              //page number
  char pageType;                               //page type
  vector<string> context;                      //page context
  vector<pair<size_t, string> > choices;       //page choices
  vector<pair<string, long int> > conditions;  //condition for page choices
  vector<pair<string, long int> > variables;   //page variables
  //constructor
  Page() :
      pageNum(0),
      pageType('N'),
      context(vector<string>()),
      choices(vector<pair<size_t, string> >()),
      conditions(vector<pair<string, long int> >()),
      variables(vector<pair<string, long int> >()) {}
  Page(size_t pageNum, char pageType, string filename) :
      pageNum(pageNum),
      pageType(pageType),
      context(vector<string>()),
      choices(vector<pair<size_t, string> >()),
      conditions(vector<pair<string, long int> >()),
      variables(vector<pair<string, long int> >()) {
    ifstream file(filename.c_str());
    if (!file) {
      error(NO_FILE);
    }
    string line;
    while (getline(file, line)) {
      context.push_back(line);
    }
    file.close();
  }
  //copy constructor
  Page(const Page & rhs) :
      pageNum(rhs.pageNum),
      pageType(rhs.pageType),
      context(vector<string>()),
      choices(vector<pair<size_t, string> >()),
      conditions(vector<pair<string, long int> >()),
      variables(vector<pair<string, long int> >()) {
    for (size_t i = 0; i < rhs.choices.size(); i++) {
      choices.push_back(rhs.choices[i]);
    }
    for (size_t i = 0; i < rhs.context.size(); i++) {
      context.push_back(rhs.context[i]);
    }
    for (size_t i = 0; i < rhs.conditions.size(); i++) {
      conditions.push_back(rhs.conditions[i]);
    }
    for (size_t i = 0; i < rhs.variables.size(); i++) {
      variables.push_back(rhs.variables[i]);
    }
  }
  //assignment constructor
  Page & operator=(const Page & rhs) {
    if (this != &rhs) {
      pageNum = rhs.pageNum;
      pageType = rhs.pageType;
      context = rhs.context;

      vector<pair<size_t, string> > temp = vector<pair<size_t, string> >();
      for (size_t i = 0; i < rhs.choices.size(); i++) {
        temp.push_back(rhs.choices[i]);
      }
      choices = temp;

      vector<string> temp1 = vector<string>();
      for (size_t i = 0; i < rhs.context.size(); i++) {
        temp1.push_back(rhs.context[i]);
      }
      context = temp1;

      vector<pair<string, long int> > temp2 = vector<pair<string, long int> >();
      for (size_t i = 0; i < rhs.variables.size(); i++) {
        temp2.push_back(rhs.variables[i]);
      }
      variables = temp2;

      vector<pair<string, long int> > temp3 = vector<pair<string, long int> >();
      for (size_t i = 0; i < rhs.conditions.size(); i++) {
        temp3.push_back(rhs.conditions[i]);
      }
      conditions = temp3;
    }
    return *this;
  }
  //destructor
  ~Page() {}
  //print page
  void printPage(vector<pair<string, long int> > & pathVariables) {
    //print context
    for (size_t i = 0; i < context.size(); i++) {
      cout << context[i] << endl;
    }
    // check page type
    if (pageType == 'L') {
      cout << endl << "Sorry, you have lost. Better luck next time!" << endl;
    }
    else if (pageType == 'W') {
      cout << endl << "Congratulations! You have won. Hooray!" << endl;
    }
    else if (pageType == 'N') {
      cout << endl << "What would you like to do?" << endl << endl;
      size_t count = 1;
      for (size_t i = 0; i < choices.size(); i++) {
        cout << " " << count << ". ";
        //check if a choice are availble by checking condition with pathVariable
        if (meetCondition(conditions[i], pathVariables)) {
          cout << choices[i].second << endl;
        }
        else {
          cout << "<UNAVAILABLE>" << endl;
        }
        count++;
      }
    }
    else {
      error(WRONG_ARGUMENT);
    }
  }
  //add choice pair into choices
  void addChoice(size_t n, string s) { choices.push_back(make_pair(n, s)); }
  //add condition pair into conditions
  void addVar(string s, long int l) { conditions.push_back(make_pair(s, l)); }
};
