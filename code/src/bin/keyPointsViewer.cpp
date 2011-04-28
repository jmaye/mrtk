#include "Image.h"
#include "Window.h"
#include "KeyPointsDrawer.h"
#include "SURFComputer.h"

#include <cv.h>

#include <iostream>
#include <fstream>

#include <sys/time.h>

using namespace std;

static uint32_t getMsCount() {
  struct timeval now;
  gettimeofday(&now, 0L);
  return ((now.tv_sec * 1000000) + (now.tv_usec)) / 1000;
}

int main(int argc ,char** argv) {
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <imageFile>" << endl;
    return -1;
  }

  Image image(argv[1]);
  vector<cv::KeyPoint> keyPointsVector;
  cv::Mat descriptorsMatrix;
  double f64Time = getMsCount();
  SURFComputer::extract(image, keyPointsVector, descriptorsMatrix);
  cout << "SURF computation: " << getMsCount() - f64Time << " [ms]" << endl;

  Window window("Original image");
  window.showImage(image);

  Window windowKeypoint("Image with keypoints");
  Image imageKeypoints(image);
  KeyPointsDrawer::draw(image, imageKeypoints, keyPointsVector);
  windowKeypoint.showImage(imageKeypoints);

  return 0;
}
