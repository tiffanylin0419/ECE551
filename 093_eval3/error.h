#include <cstdlib>   // EXIT_FAILURE
#include <iostream>  //cerr

using namespace std;
enum {
  WRONG_ARGUMENT,
  NO_FILE,
  WRONG_STORY_FORMAT,
  PAGE_ORDER,
  PAGE_DECLARE,
  NO_CHOICE,
  WRONG_CHOICE_SIZE,
  PAGE_NOT_REFERENCED,
  MISS_PAGE
};
void error(int err) {
  switch (err) {
    case WRONG_ARGUMENT:
      cerr << "Wrong number of arguments\n";
      break;
    case NO_FILE:
      cerr << "Cannot open file\n";
      break;
    case WRONG_STORY_FORMAT:
      cerr << "Wrong format of story.txt\n";
      break;
    case PAGE_ORDER:
      cerr << "Page declarations must appear in order.\n";
      break;
    case PAGE_DECLARE:
      cerr
          << "A page declaration must appear before anything else related to that page\n";
      break;
    case NO_CHOICE:
      cerr << "Win and Lose pages MUST NOT have any choices.\n";
      break;
    case WRONG_CHOICE_SIZE:
      cerr << "Choice number is too big or too small.\n";
      break;
    case PAGE_NOT_REFERENCED:
      cerr << "page needs to be referenced by at least one other page's choice.\n";
      break;
    case MISS_PAGE:
      cerr << "Missing lose or win page.\n";
      break;
    default:
      break;
  }
  exit(EXIT_FAILURE);
}
