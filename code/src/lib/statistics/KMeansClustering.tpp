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

#include "statistics/Randomizer.h"

#include <ANN/ANN.h>

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename T, size_t M>
void KMeansClustering<T, M>::cluster(const std::vector<Eigen::Matrix<T, M, 1> >&
  data, std::vector<Eigen::Matrix<T, M, 1> >& clusterCenters,
  std::vector<std::vector<size_t> >& assignments, size_t k,
  size_t maxIterations, double tol) throw (BadArgumentException<size_t>) {

  if (k == 0)
    throw BadArgumentException<size_t>(k,
      "KMeansClustering::cluster(): k must be greater than 0",
      __FILE__, __LINE__);

  if (data.size() == 0)
    throw BadArgumentException<size_t>(data.size(),
      "KMeansClustering::cluster(): input points vector is empty",
      __FILE__, __LINE__);

  ANNpointArray clusterCentersANN = annAllocPts(k, M);

  Randomizer<size_t> randomizer;

  for (size_t i = 0; i < k; ++i) {
    size_t idx = randomizer.sampleUniform(0, data.size());
    ANNpoint point = annAllocPt(M);
    for (size_t j = 0; j < M; ++j)
      point[j] = data[idx](j);
    clusterCentersANN[i] = point;
    annDeallocPt(point);
  }

  size_t iteration = 0;

  ANNidxArray idx = new ANNidx[1];
  ANNdistArray dist = new ANNdist[1];

  clusterCenters.clear();
  clusterCenters.resize(k);

  while (iteration != maxIterations) {
    ANNkd_tree* pKdTree =  new ANNkd_tree(clusterCentersANN, k, M);

    assignments.clear();
    assignments.resize(k);

    for (size_t i = 0; i < data.size(); ++i) {
      ANNpoint point = annAllocPt(M);
      for (size_t j = 0; j < M; j++)
        point[j] = data[i](j);
      pKdTree->annkSearch(point, 1, idx, dist, 0);
      assignments[idx[0]].push_back(i);
      annDeallocPt(point);
    }

    delete pKdTree;

    for (size_t i = 0; i < k; ++i) {
      clusterCenters[i].setConstant(0);
      for (size_t j = 0; j < assignments[i].size(); ++j) {
        clusterCenters[i] += data[assignments[i][j]];
      }
      if (assignments[i].size())
        clusterCenters[i] /= assignments[i].size();
    }

    for (size_t i = 0; i < k; ++i) {
      ANNpoint point = annAllocPt(M);
      for (size_t j = 0; j < M; ++j)
        point[j] = clusterCenters[i](j);
      clusterCentersANN[i] = point;
      annDeallocPt(point);
    }

    iteration++;
  }

  //annDeallocPts(clusterCentersANN);
  //delete [] idx;
  //delete [] dist;
  annClose();
}
