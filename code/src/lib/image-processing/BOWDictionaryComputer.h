#ifndef BOWDICTIONARYCOMPUTER_H
#define BOWDICTIONARYCOMPUTER_H

#include <cv.h>

#include <set>
#include <string>

#include <stdint.h>

class BOWDictionaryComputer {
  BOWDictionaryComputer();

public:
  static void compute(const std::set<std::string>& filenamesSet,
    double f64FilesPercentage, double f64FeaturesPercentage,
    uint32_t u32MaxDescriptors, uint32_t u32DictionarySize,
    cv::Mat& dictionaryMatrix);

protected:

};

#endif // BOWDICTIONARYCOMPUTER_H
