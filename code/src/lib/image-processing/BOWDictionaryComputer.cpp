#include "BOWDictionaryComputer.h"

#include "Image.h"
#include "SURFComputer.h"

#include <opencv2/features2d/features2d.hpp>

#include <iostream>
#include <vector>

#include <stdlib.h>
#include <math.h>

using namespace cv;
using namespace std;

void BOWDictionaryComputer::compute(const set<string>& filenamesSet,
  double f64Percentage, uint32_t u32MaxDescriptors,
  uint32_t u32DictionarySize, Mat& dictionaryMatrix) {
  uint32_t u32ImagesNbr = round(filenamesSet.size() * f64Percentage);
  vector<string> filenamesVector;
  set<string>::const_iterator filenamesSetIt;
  for (filenamesSetIt = filenamesSet.begin();
    filenamesSetIt != filenamesSet.end(); filenamesSetIt++)
    filenamesVector.push_back(*filenamesSetIt);
  cout << "Selecting descriptors for training..." << endl;
  cout << u32ImagesNbr << " images to process" << endl;
  BOWKMeansTrainer bowTrainer(u32DictionarySize);
  for (uint32_t i = 0; i < u32ImagesNbr; i++) {
    uint32_t u32Idx = 
      round((double)random() / (double)RAND_MAX * filenamesVector.size());
    Image image(filenamesVector[u32Idx]);
    vector<KeyPoint> keyPointsVector;
    Mat descriptorsMatrix;
    cout << "Processing: " << filenamesVector[u32Idx] << endl;
    SURFComputer::extract(image, keyPointsVector, descriptorsMatrix);
    bowTrainer.add(descriptorsMatrix);
    filenamesVector.erase(filenamesVector.begin() + u32Idx);
    cout << "Descriptors: " << bowTrainer.descripotorsCount() << endl;
  }
  cout << "Clustering descriptors..." << endl;
  dictionaryMatrix = bowTrainer.cluster();
}
