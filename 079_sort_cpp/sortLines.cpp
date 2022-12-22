#include <algorithm>  //std::sort
#include <cstdlib>
#include <fstream>   //std::ifstream
#include <iostream>  //std::cout
#include <string>    //std::string
#include <vector>    //std::vector
using namespace std;

void sortLine(istream & stream) {
  string line;
  vector<string> v;
  if (stream.bad()) {  //check if any errors happened
    stream.clear();    //clear the error state
    cerr << "IO error" << endl;
    exit(EXIT_FAILURE);
  }

  while (getline(stream, line)) {
    v.push_back(line);
  }

  if (!stream.eof()) {
    cerr << "format error" << endl;
    exit(EXIT_FAILURE);
  }
  sort(v.begin(), v.end());
  vector<string>::iterator it = v.begin();
  while (it != v.end()) {
    std::cout << *it << "\n";
    ++it;
  }
  return;
}
int main(int argc, char ** argv) {
  if (argc == 1) {
    sortLine(cin);
    return EXIT_SUCCESS;
  }
  for (int i = 1; i < argc; i++) {
    ifstream f(argv[i]);
    if (!f) {
      cerr << "fail to open " << argv[i] << endl;
      return EXIT_FAILURE;
    }
    sortLine(f);
    f.close();
  }
  return EXIT_SUCCESS;
}
