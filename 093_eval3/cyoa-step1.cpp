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
  story.printStory();
  return EXIT_SUCCESS;
}
