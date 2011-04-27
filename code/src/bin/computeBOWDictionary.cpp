#include "BOWDictionaryComputer.h"

#include <cv.h>

#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include <sys/time.h>
#include <stdint.h>
#include <dirent.h> 
#include <string.h>

using namespace cv;
using namespace std;

static uint32_t getMsCount() {
  struct timeval now;
  gettimeofday(&now, 0L);
  return ((now.tv_sec * 1000000) + (now.tv_usec)) / 1000;
}

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <imageDirectory>" << endl;
    return -1;
  }

  DIR *d;
  struct dirent *dir;
  d = opendir(argv[1]);
  set<string> filenamesSet;
  if (d) {
    while ((dir = readdir(d)) != NULL)
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
        filenamesSet.insert(string(argv[1]) + string(dir->d_name));
      }
    closedir(d);
  }

  Mat dictionaryMatrix;
  cout << "Computing dictionary..." << endl;
  double f64Time = getMsCount();
  BOWDictionaryComputer::compute(filenamesSet, 0.001, 100000, 256,
    dictionaryMatrix);
  cout << "Time elapsed: " << getMsCount() - f64Time << endl;

  return 0;
}
