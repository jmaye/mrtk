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

template <size_t N>
size_t EstimatorML<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
  estimate(MixtureDistribution<NormalDistribution<1>, N>& dist, const
  std::vector<double>& points, Eigen::Matrix<double, Eigen::Dynamic, N>&
  responsibilities, size_t maxNumIter, double tol) {
  size_t numIter = 0;
  if (points.size()) {
    double oldLogLikelihood = 0;
    responsibilities.resize(points.size(), N);
    for (size_t i = 0; i < points.size(); ++i)
      oldLogLikelihood += log(dist(points[i]));
    while (numIter != maxNumIter) {
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t k = 0; k < N; ++k) {
          Eigen::Matrix<size_t, N, 1> component =
            Eigen::Matrix<size_t, N, 1>::Zero();
          component(k) = 1.0;
          responsibilities(i, k) = dist.getWeights()(component) *
            dist.getDistributions()[k](points[i]);
        }
        responsibilities.row(i) /= dist(points[i]);
      }
      Eigen::Matrix<double, N, 1> mean = Eigen::Matrix<double, N, 1>::Zero();
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t k = 0; k < N; ++k)
          mean(k) += responsibilities(i, k) * points[i];
      }
      Eigen::Matrix<double, N, 1> numPoints =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t k = 0; k < N; ++k)
        numPoints(k) = responsibilities.col(k).sum();
      mean.cwise() /= numPoints;
      Eigen::Matrix<double, N, 1> variance =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t i = 0; i < points.size(); ++i)
        for (size_t k = 0; k < N; ++k)
          variance(k) += responsibilities(i, k) * (points[i] - mean(k)) *
            (points[i] - mean(k));
      variance.cwise() /= numPoints;
      Eigen::Matrix<double, N, 1> weights = numPoints / points.size();
      weights /= weights.sum();
      dist.setWeights(CategoricalDistribution<N>(weights));
      std::vector<NormalDistribution<1> > distributions;
      distributions.resize(N);
      for (size_t k = 0; k < N; ++k) {
        distributions[k].setMean(mean(k));
        distributions[k].setVariance(variance(k));
      }
      dist.setDistributions(distributions);
      double newLogLikelihood = 0;
      for (size_t i = 0; i < points.size(); ++i) {
        newLogLikelihood += log(dist(points[i]));
      }
      if (fabs(oldLogLikelihood - newLogLikelihood) < tol)
        break;
      oldLogLikelihood = newLogLikelihood;
      numIter++;
    }
  }
  return numIter;
}
