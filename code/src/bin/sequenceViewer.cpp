#include "Image.h"
#include "Window.h"

#include <iostream>
#include <fstream>
#include <set>
#include <string>

#include <dirent.h> 
#include <string.h>

using namespace std;

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

  Window window("Car dataset");
  set<string>::const_iterator filenamesSetIt;
  for (filenamesSetIt = filenamesSet.begin();
    filenamesSetIt != filenamesSet.end(); filenamesSetIt++)
    window.showImage(Image(*filenamesSetIt), 5);

  return 0;
}
