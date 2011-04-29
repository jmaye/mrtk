#include "BOWDictionaryComputer.h"

#include "Image.h"
#include "SURFComputer.h"

#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <math.h>
#include <time.h>

using namespace cv;
using namespace std;

void BOWDictionaryComputer::compute(const set<string>& filenamesSet,
  double f64FilesPercentage, double f64FeaturesPercentage,
  uint32_t u32MaxDescriptors, uint32_t u32DictionarySize,
  Mat& dictionaryMatrix) {
  uint32_t u32ImagesNbr = round(filenamesSet.size() * f64FilesPercentage);
  vector<string> filenamesVector;
  set<string>::const_iterator filenamesSetIt;
  for (filenamesSetIt = filenamesSet.begin();
    filenamesSetIt != filenamesSet.end(); filenamesSetIt++)
    filenamesVector.push_back(*filenamesSetIt);
  cout << "Selecting descriptors for training..." << endl;
  cout << u32ImagesNbr << " images to process" << endl;
  BOWKMeansTrainer bowTrainer(u32DictionarySize);
  srandom(time(NULL));
  for (uint32_t i = 0; i < u32ImagesNbr; i++) {
    if ((uint32_t)bowTrainer.descripotorsCount() >= u32MaxDescriptors)
      break;
    uint32_t u32Idx = 
      round((double)random() / (double)RAND_MAX * (filenamesVector.size() - 1));
    Image image(filenamesVector[u32Idx]);
    vector<KeyPoint> keyPointsVector;
    Mat descriptorsMatrix;
    cout << "Processing: " << filenamesVector[u32Idx] << endl;
    SURFComputer::extract(image, keyPointsVector, descriptorsMatrix);
    if (!descriptorsMatrix.empty()) {
      int32_t i32DescriptorsCount = descriptorsMatrix.rows;
      uint32_t u32DescriptorsToExtract = round(f64FeaturesPercentage *
        i32DescriptorsCount);
      cout << "Selecting " << u32DescriptorsToExtract << " out of "
           << i32DescriptorsCount << endl;
      vector<char> usedMask(i32DescriptorsCount, false);
      fill(usedMask.begin(), usedMask.begin() + u32DescriptorsToExtract, true);
      for (uint32_t j = 0; j < (uint32_t)i32DescriptorsCount; j++) {
        uint32_t u32Idx1 = round((double)random() / (double)RAND_MAX *
          (i32DescriptorsCount - 1));
        uint32_t u32Idx2 = round((double)random() / (double)RAND_MAX *
          (i32DescriptorsCount - 1));
        char tmp = usedMask[u32Idx1];
        usedMask[u32Idx1] = usedMask[u32Idx2];
        usedMask[u32Idx2] = tmp;
      }
      for (uint32_t j = 0; j < (uint32_t)i32DescriptorsCount; j++) {
        if (usedMask[j] == true &&
          (uint32_t)bowTrainer.descripotorsCount() < u32MaxDescriptors) {
          bowTrainer.add(descriptorsMatrix.row(j));
        }
      }
    }
    filenamesVector.erase(filenamesVector.begin() + u32Idx);
    cout << "Descriptors: " << bowTrainer.descripotorsCount() << endl;
    cout << "Remaining possible images: " << filenamesVector.size() << endl;
    cout << "Processed images: " << i << endl;
  }
  cout << "Clustering descriptors..." << endl;
  dictionaryMatrix = bowTrainer.cluster();
}
