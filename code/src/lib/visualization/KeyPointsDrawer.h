#ifndef KEYPOINTSDRAWER_H
#define KEYPOINTSDRAWER_H

#include "Image.h"

#include <opencv2/features2d/features2d.hpp>

#include <vector>

class KeyPointsDrawer {
  KeyPointsDrawer();

public:
  static void draw(Image& image, std::vector<cv::KeyPoint> keyPointsVector);

protected:

};

#endif // KEYPOINTSDRAWER_H
