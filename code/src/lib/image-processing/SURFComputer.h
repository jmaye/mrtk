#ifndef SURFCOMPUTER_H
#define SURFCOMPUTER_H

#include "Image.h"

#include <cv.h>
#include <opencv2/features2d/features2d.hpp>

#include <vector>

class SURFComputer {
  SURFComputer();

public:
  static void extract(const Image& image,
    std::vector<cv::KeyPoint>& keyPointsVector,
    cv::Mat& descriptorsMatrix);

protected:

};

#endif // SURFCOMPUTER_H
