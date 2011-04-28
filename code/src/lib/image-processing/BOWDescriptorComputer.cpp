#include "BOWDescriptorComputer.h"

#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void BOWDescriptorComputer::compute(const Image& image,
  const Mat& dictionaryMatrix, Mat& descriptorsMatrix) {
  Ptr<FeatureDetector> detector = FeatureDetector::create("SURF");
  Ptr<DescriptorExtractor> descriptorExtractor =
    DescriptorExtractor::create("SURF");
  Ptr<DescriptorMatcher> descMatcher =
    DescriptorMatcher::create("BruteForce");
  BOWImgDescriptorExtractor bowExtractor(descriptorExtractor, descMatcher);
  bowExtractor.setVocabulary(dictionaryMatrix);
  vector<KeyPoint> keyPointsVector;
  cout << "Detecting keypoints..." << endl;
  detector->detect(image.getImageMatrix(), keyPointsVector);
  cout << "Found " << keyPointsVector.size() << endl;
  cout << "Computing descriptor..." << endl;
  bowExtractor.compute(image.getImageMatrix(), keyPointsVector,
    descriptorsMatrix);
}
