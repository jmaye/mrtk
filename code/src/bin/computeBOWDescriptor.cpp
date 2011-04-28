#include "Image.h"
#include "BOWDescriptorComputer.h"

#include <cv.h>

#include <iostream>
#include <fstream>

#include <sys/time.h>
#include <stdint.h>

using namespace cv;
using namespace std;

static uint32_t getMsCount() {
  struct timeval now;
  gettimeofday(&now, 0L);
  return ((now.tv_sec * 1000000) + (now.tv_usec)) / 1000;
}

int main(int argc ,char** argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <imageFile> <dictionaryFile> <outFile>"
         << endl;
    return -1;
  }

  Mat dictionaryMatrix;
  FileStorage fs(argv[2], FileStorage::READ);
  if (fs.isOpened()) {
    fs["dictionary"] >> dictionaryMatrix;
  } else
    return -1;

  Image image(argv[1]);
  Mat descriptorsMatrix;
  double f64Time = getMsCount();
  BOWDescriptorComputer::compute(image, dictionaryMatrix, descriptorsMatrix);
  cout << "BOW descriptor computation: " << getMsCount() - f64Time << " [ms]"
       <<endl;

  ofstream descriptorFile(argv[3]);
  descriptorFile << descriptorsMatrix;

  return 0;
}
