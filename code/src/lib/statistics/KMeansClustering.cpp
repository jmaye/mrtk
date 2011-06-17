/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "statistics/KMeansClustering.h"

#include <ANN/ANN.h>

#include <stdlib.h>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void KMeansClustering::cluster(const std::vector<std::vector<double> >&
  inputPointsVector, std::vector<std::vector<double> >& clusterCentersVector,
  std::vector<std::vector<uint32_t > >& assignmentsVector, uint32_t u32K,
  uint32_t u32MaxIterations, double f64Tol) throw (InvalidOperationException) {

  if (u32K == 0)
    throw InvalidOperationException("KMeansClustering::cluster(): K must be greater than 0");

  if (inputPointsVector.size() == 0)
    throw InvalidOperationException("KMeansClustering::cluster(): input points vector is empty");

  if (inputPointsVector[0].size() == 0)
    throw InvalidOperationException("KMeansClustering::cluster(): input points have zero dimension");

  //srandom(time(NULL));

  ANNpointArray clusterCentersArray = annAllocPts(u32K,
    inputPointsVector[0].size());

  for (uint32_t i = 0; i < u32K; i++) {
    uint32_t u32Idx = round((double)random() / (double)RAND_MAX *
      (inputPointsVector.size() - 1));
    ANNpoint point = annAllocPt(inputPointsVector[u32Idx].size());
    for (uint32_t j = 0; j < inputPointsVector[u32Idx].size(); j++)
      point[j] = inputPointsVector[u32Idx][j];
    clusterCentersArray[i] = point;
    annDeallocPt(point);
  }

  uint32_t u32Iteration = 0;

  ANNidxArray idxArray = new ANNidx[1];
  ANNdistArray distArray = new ANNdist[1];

  while (u32Iteration != u32MaxIterations) {
    ANNkd_tree* pKdTree =  new ANNkd_tree(clusterCentersArray, u32K,
      inputPointsVector[0].size());

    assignmentsVector.clear();
    assignmentsVector.resize(u32K);

    for (uint32_t i = 0; i < inputPointsVector.size(); i++) {
      ANNpoint point = annAllocPt(inputPointsVector[i].size());
      for (uint32_t j = 0; j < inputPointsVector[i].size(); j++)
        point[j] = inputPointsVector[i][j];
      pKdTree->annkSearch(point, 1, idxArray, distArray, 0);
      assignmentsVector[idxArray[0]].push_back(i);
      annDeallocPt(point);
    }

    delete pKdTree;

    for (uint32_t i = 0; i < u32K; i++) {
      for (uint32_t j = 0; j < inputPointsVector[0].size(); j++)
        clusterCentersArray[i][j] = 0;
      for (uint32_t j = 0; j < assignmentsVector[i].size(); j++) {
        for (uint32_t k = 0;
          k < inputPointsVector[assignmentsVector[i][j]].size(); k++) {
          clusterCentersArray[i][k] +=
            inputPointsVector[assignmentsVector[i][j]][k];
        }
      }
      for (uint32_t j = 0; j < inputPointsVector[0].size(); j++)
        clusterCentersArray[i][j] /= assignmentsVector[i].size();
    }

    u32Iteration++;
  }

  clusterCentersVector.clear();
  clusterCentersVector.resize(u32K);

  for (uint32_t i = 0; i < u32K; i++) {
    clusterCentersVector[i].resize(inputPointsVector[0].size());
    for (uint32_t j = 0; j < inputPointsVector[0].size(); j++)
      clusterCentersVector[i][j] = clusterCentersArray[i][j];
  }

  annDeallocPts(clusterCentersArray);
  delete [] idxArray;
  delete [] distArray;
  annClose();
}
