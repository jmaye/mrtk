#ifndef KEYPOINTSDRAWER_H
#define KEYPOINTSDRAWER_H

#include "Image.h"

#include <cv.h>
#include <opencv2/features2d/features2d.hpp>

#include <vector>

class KeyPointsDrawer {
  KeyPointsDrawer();

public:
  static void draw(const Image& imageSrc, Image& imageOut,
    const std::vector<cv::KeyPoint>& keyPointsVector);

protected:

};

#endif // KEYPOINTSDRAWER_H
