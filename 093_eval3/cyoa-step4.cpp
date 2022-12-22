
#include <cstdio>
#include <fstream>  //ifstream
#include <sstream>  //stringstream

#include "story.h"
using namespace std;
int main(int argc, char ** argv) {
  if (argc != 2) {
    error(WRONG_ARGUMENT);
  }

  Story story;
  story.addStory(string(argv[1]));
  story.checkStory();
  vector<pair<string, long int> > pathVariables = vector<pair<string, long int> >();
  pathVariables.push_back(make_pair("$_$_NULL", 0));
  story.printInputStory(0, pathVariables);
  return EXIT_SUCCESS;
}
