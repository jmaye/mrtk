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
        successProbabilities(j) += points[i](j);
      numTrials += points[i].sum();
    }
    successProbabilities /= numTrials;
    numTrials /= points.size();
    dist.setNumTrials(numTrials);
    dist.setSuccessProbabilities(successProbabilities);
  }
}

void EstimatorMLBatch<ExponentialDistribution>::estimate(
  ExponentialDistribution& dist, const
  std::vector<ExponentialDistribution::VariableType>& points) {
  if (points.size()) {
    Eigen::Map<Eigen::VectorXd> dataMapped(&points[0], points.size());
    double mean = dataMapped.sum() / points.size();
    dist.setRate(1.0 / mean);
  }
}

void EstimatorMLBatch<GeometricDistribution>::estimate(GeometricDistribution&
  dist, const std::vector<GeometricDistribution::VariableType>& points) {
  if (points.size()) {
    Eigen::Map<Eigen::Matrix<size_t, Eigen::Dynamic, 1> >
      dataMapped(&points[0], points.size());
    double mean = dataMapped.sum() / (double)points.size();
    mean++;
    dist.setSuccessProbability(1.0 / mean);
  }
}

void EstimatorMLBatch<PoissonDistribution>::estimate(PoissonDistribution& dist,
  const std::vector<PoissonDistribution::VariableType>& points) {
  if (points.size()) {
    Eigen::Map<Eigen::Matrix<size_t, Eigen::Dynamic, 1> >
      dataMapped(&points[0], points.size());
    double mean = dataMapped.sum() / (double)points.size();
    dist.setRate(mean);
  }
}

template <size_t M>
void EstimatorMLBatch<LinearRegression<M>, M>::estimate(LinearRegression<M>&
  dist, const std::vector<Eigen::Matrix<double, M, 1> >& points, double tol)
  throw (InvalidOperationException) {
  if (points.size()) {
    Eigen::Matrix<double, Eigen::Dynamic, 1> targets(points.size());
    Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(points.size(),
      (int)M);
    for (size_t i = 0; i < points.size(); ++i) {
      targets(i) = points[i](M - 1);
      designMatrix(i, 0) = 1.0;
      for (size_t j = 1; j < M; ++j)
        designMatrix(i, j) = points[i](j - 1);
    }
    Eigen::Matrix<double, M, M> invCheckMatrix =
      designMatrix.transpose() * designMatrix;
    if (points.size() < M || invCheckMatrix.determinant() < tol)
      throw InvalidOperationException("EstimatorMLBatch<LinearRegression<M>, M>::estimate(): data cannot be fitted");
    Eigen::Matrix<double, M, 1> coefficients = invCheckMatrix.inverse() *
      designMatrix.transpose() * targets;
    double variance = 0.0;
    for (size_t i = 0; i < points.size(); ++i)
      variance += (targets(i) - (coefficients.transpose() *
        designMatrix.row(i).transpose())(0)) * (targets(i) -
        (coefficients.transpose() * designMatrix.row(i).transpose())(0));
    variance /= points.size();
    dist.setCoefficients(coefficients);
    dist.setVariance(variance);
  }
}
