#ifndef BOWDESCRIPTORCOMPUTER_H
#define BOWDESCRIPTORCOMPUTER_H

#include "Image.h"

#include <cv.h>

class BOWDescriptorComputer {
  BOWDescriptorComputer();

public:
  static void compute(const Image& image, const cv::Mat& dictionaryMatrix,
    cv::Mat& descriptorsMatrix);

protected:

};

#endif // BOWDESCRIPTORCOMPUTER_H
