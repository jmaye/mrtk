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

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void EstimatorMLBatch<NormalDistribution<1> >::estimate(NormalDistribution<1>&
  dist, const std::vector<NormalDistribution<1>::VariableType>&
  points) {
  if (points.size()) {
    Eigen::Map<Eigen::VectorXd> dataMapped(&points[0], points.size());
    double mean = dataMapped.sum() / points.size();
    double variance = (dataMapped.cwise() - mean).cwise().square().sum() /
      points.size();
    dist.setMean(mean);
    dist.setVariance(variance);
  }
}

template <size_t M>
void EstimatorMLBatch<NormalDistribution<M>, M>::estimate(NormalDistribution<M>&
  dist, const std::vector<typename NormalDistribution<M>::VariableType>&
  points) {
  if (points.size()) {
    Eigen::Matrix<double, M, 1> mean = Eigen::Matrix<double, M, 1>::Zero();
    for (size_t i = 0; i < points.size(); ++i)
      mean += points[i];
    mean /= points.size();
    Eigen::Matrix<double, M, M> covariance =
      Eigen::Matrix<double, M, M>::Zero();
    for (size_t i = 0; i < points.size(); ++i)
      covariance += (points[i] - mean) * (points[i] - mean).transpose();
    covariance /= points.size();
    dist.setMean(mean);
    dist.setCovariance(covariance);
  }
}

template <size_t M>
void EstimatorMLBatch<CategoricalDistribution<M>, M>::estimate(
  CategoricalDistribution<M>& dist, const
  std::vector<Eigen::Matrix<size_t, M, 1> >& points) {
  if (points.size()) {
    Eigen::Matrix<double, M, 1> successProbabilities =
      Eigen::Matrix<double, M, 1>::Zero();
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < M; ++j)
        successProbabilities(j) += points[i](j);
    }
    successProbabilities /= points.size();
    dist.setSuccessProbabilities(successProbabilities);
  }
}

template <size_t M>
void EstimatorMLBatch<MultinomialDistribution<M>, M>::estimate(
  MultinomialDistribution<M>& dist, const
  std::vector<Eigen::Matrix<size_t, M, 1> >& points) {
  if (points.size()) {
    Eigen::Matrix<double, M, 1> successProbabilities =
      Eigen::Matrix<double, M, 1>::Zero();
    double numTrials = 0;
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < M; ++j)
        successProbabilities(j) += points[i](j) / (double)points[i].sum();
      numTrials += points[i].sum();
    }
    successProbabilities /= points.size();
    numTrials /= points.size();
    std::cout << successProbabilities << std::endl;
    std::cout << numTrials << std::endl;
    dist.setNumTrials(numTrials);
    dist.setSuccessProbabilities(successProbabilities);
  }
}
