#include "KeyPointsDrawer.h"

#include <stdint.h>

using namespace cv;
using namespace std;

void KeyPointsDrawer::draw(Image& image, vector<KeyPoint> keyPointsVector) {
  for (uint32_t i = 0; i < keyPointsVector.size(); i++)
    circle(image.getImageMatrix(), keyPointsVector[i].pt,
      keyPointsVector[i].size, Scalar(0, 0, 255));
}
