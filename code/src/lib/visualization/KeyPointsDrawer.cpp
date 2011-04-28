#include "KeyPointsDrawer.h"

#include <stdint.h>

using namespace cv;
using namespace std;

void KeyPointsDrawer::draw(const Image& imageSrc, Image& imageOut,
  const vector<KeyPoint>& keyPointsVector) {
  drawKeypoints(imageSrc.getImageMatrix(), keyPointsVector,
    imageOut.getImageMatrix(), Scalar::all(-1),
    DrawMatchesFlags::DRAW_OVER_OUTIMG | DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
}
