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

template <size_t M, size_t N>
size_t EstimatorMLBatch<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  estimate(MixtureDistribution<LinearRegression<M>, N>& dist, const
  std::vector<Eigen::Matrix<double, M, 1> >& points,
  Eigen::Matrix<double, Eigen::Dynamic, N>& responsibilities, size_t
  maxNumIter, double tol) throw (InvalidOperationException) {
  size_t numIter = 0;
  if (points.size()) {
    double oldLogLikelihood = 0;
    responsibilities.resize(points.size(), N);
    std::vector<LinearRegression<M> > distributions = dist.getDistributions();
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < N; ++j)
        distributions[j].setBasis(points[i].segment(0, M - 1));
      dist.setDistributions(distributions);
      oldLogLikelihood += log(dist(points[i](M - 1)));
    }
    while (numIter != maxNumIter) {
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < N; ++j)
          distributions[j].setBasis(points[i].segment(0, M - 1));
        dist.setDistributions(distributions);
        for (size_t k = 0; k < N; ++k) {
          Eigen::Matrix<size_t, N, 1> component =
            Eigen::Matrix<size_t, N, 1>::Zero();
          component(k) = 1.0;
          responsibilities(i, k) = dist.getWeights()(component) *
            dist.getDistributions()[k](points[i](M - 1));
        }
        responsibilities.row(i) /= dist(points[i](M - 1));
      }
      Eigen::Matrix<double, N, 1> numPoints =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t k = 0; k < N; ++k)
        numPoints(k) = responsibilities.col(k).sum();
      Eigen::Matrix<double, N, 1> weights = numPoints / points.size();
      weights /= weights.sum();
      dist.setWeights(CategoricalDistribution<N>(weights));
      Eigen::Matrix<double, Eigen::Dynamic, 1> targets(points.size());
      Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(points.size(),
        (int)M);
      for (size_t i = 0; i < points.size(); ++i) {
        targets(i) = points[i](M - 1);
        designMatrix(i, 0) = 1.0;
        designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
      }
      for (size_t k = 0; k < N; ++k) {
        Eigen::Matrix<double, M, M> invCheckMatrix = designMatrix.transpose() *
          responsibilities.col(k).asDiagonal() * designMatrix;
        if (invCheckMatrix.determinant() < tol)
          throw InvalidOperationException("EstimatorMLBatch<MixtureDistribution<LinearRegression<M>, N>, M, N>::estimate(): data cannot be fitted");
        Eigen::Matrix<double, M, 1> coefficients = invCheckMatrix.inverse() *
          designMatrix.transpose() * responsibilities.col(k).asDiagonal() *
          targets;
        double variance = 0.0;
        for (size_t i = 0; i < points.size(); ++i)
          variance += responsibilities(i, k) * (targets(i) -
            (coefficients.transpose() * designMatrix.row(i).transpose())(0)) *
            (targets(i) - (coefficients.transpose() *
            designMatrix.row(i).transpose())(0));
        variance /= numPoints(k);
        distributions[k].setCoefficients(coefficients);
        distributions[k].setVariance(variance);
      }
      double newLogLikelihood = 0;
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t j = 0; j < N; ++j)
          distributions[j].setBasis(points[i].segment(0, M - 1));
        dist.setDistributions(distributions);
        newLogLikelihood += log(dist(points[i](M - 1)));
      }
      if (fabs(oldLogLikelihood - newLogLikelihood) < tol)
        break;
      oldLogLikelihood = newLogLikelihood;
      numIter++;
    }
  }
  return numIter;
}
