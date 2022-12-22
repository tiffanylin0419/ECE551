
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
  vector<vector<pair<size_t, size_t> > > allPath;
  vector<pair<size_t, size_t> > path;
  story.findPath(0, path, allPath);
  story.printPath(allPath);
  return EXIT_SUCCESS;
}
