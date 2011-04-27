#include "SURFComputer.h"

#include <stdint.h>

using namespace cv;
using namespace std;

void SURFComputer::extract(const Image& image,
  vector<KeyPoint>& keyPointsVector, Mat& descriptorsMatrix) {
  Ptr<FeatureDetector> detector = FeatureDetector::create("SURF");
  Ptr<DescriptorExtractor> descriptorExtractor =
    DescriptorExtractor::create("SURF");
  detector->detect(image.getImageMatrix(), keyPointsVector);
  descriptorExtractor->compute(image.getImageMatrix(), keyPointsVector,
    descriptorsMatrix);
}
