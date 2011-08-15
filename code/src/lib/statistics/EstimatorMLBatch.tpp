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

#include "base/Timestamp.h"

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
      designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
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

template <size_t N>
size_t EstimatorMLBatch<MixtureDistribution<NormalDistribution<1>, N>, 1, N>::
  estimate(MixtureDistribution<NormalDistribution<1>, N>& dist, const
  std::vector<double>& points, std::vector<Eigen::Matrix<double, N, 1> >&
  responsibilities, size_t maxNumIter, double tol) {
  size_t numIter = 0;
  responsibilities.clear();
  if (points.size()) {
    double oldLogLikelihood = 0;
    for (size_t i = 0; i < points.size(); ++i)
      oldLogLikelihood += log(dist(points[i]));
    responsibilities.resize(points.size());
    while (numIter != maxNumIter) {
      for (size_t i = 0; i < points.size(); ++i) {
        Eigen::Matrix<double, N, 1> responsibility;
        for (size_t k = 0; k < N; ++k) {
          Eigen::Matrix<size_t, N, 1> component =
            Eigen::Matrix<size_t, N, 1>::Zero();
          component(k) = 1.0;
          responsibility(k) = dist.getWeights()(component) *
            dist.getDistributions()[k](points[i]);
        }
        responsibility /= dist(points[i]);
        responsibilities[i] = responsibility;
      }
      Eigen::Matrix<double, N, 1> mean = Eigen::Matrix<double, N, 1>::Zero();
      Eigen::Matrix<double, N, 1> numPoints =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t k = 0; k < N; ++k)
          mean(k) += responsibilities[i](k) * points[i];
        numPoints += responsibilities[i];
      }
      mean.cwise() /= numPoints;
      Eigen::Matrix<double, N, 1> variance =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t i = 0; i < points.size(); ++i)
        for (size_t k = 0; k < N; ++k)
          variance(k) += responsibilities[i](k) * (points[i] - mean(k)) *
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

template <size_t M, size_t N>
size_t EstimatorMLBatch<MixtureDistribution<NormalDistribution<M>, N>, M, N>::
  estimate(MixtureDistribution<NormalDistribution<M>, N>& dist, const
  std::vector<typename NormalDistribution<M>::VariableType>& points,
  std::vector<Eigen::Matrix<double, N, 1> >& responsibilities, size_t
  maxNumIter, double tol) {
  size_t numIter = 0;
  responsibilities.clear();
  if (points.size()) {
    double oldLogLikelihood = 0;
    for (size_t i = 0; i < points.size(); ++i)
      oldLogLikelihood += log(dist(points[i]));
    responsibilities.resize(points.size());
    while (numIter != maxNumIter) {
      for (size_t i = 0; i < points.size(); ++i) {
        Eigen::Matrix<double, N, 1> responsibility;
        for (size_t k = 0; k < N; ++k) {
          Eigen::Matrix<size_t, N, 1> component =
            Eigen::Matrix<size_t, N, 1>::Zero();
          component(k) = 1.0;
          responsibility(k) = dist.getWeights()(component) *
            dist.getDistributions()[k](points[i]);
        }
        responsibility /= dist(points[i]);
        responsibilities[i] = responsibility;
      }
      std::vector<Eigen::Matrix<double, M, 1> > mean(N);
      for (size_t k = 0; k < N; ++k)
        mean[k] = Eigen::Matrix<double, M, 1>::Zero();
      Eigen::Matrix<double, N, 1> numPoints =
        Eigen::Matrix<double, N, 1>::Zero();
      for (size_t i = 0; i < points.size(); ++i) {
        for (size_t k = 0; k < N; ++k)
          mean[k] += responsibilities[i](k) * points[i];
        numPoints += responsibilities[i];
      }
      for (size_t k = 0; k < N; ++k)
        mean[k] /= numPoints[k];
      std::vector<Eigen::Matrix<double, M, M> > covariance(N);
      for (size_t k = 0; k < N; ++k)
        covariance[k] = Eigen::Matrix<double, M, M>::Zero();
      for (size_t i = 0; i < points.size(); ++i)
        for (size_t k = 0; k < N; ++k)
          covariance[k] += responsibilities[i](k) * (points[i] - mean[k]) *
            (points[i] - mean[k]).transpose();
      for (size_t k = 0; k < N; ++k) {
        covariance[k] /= numPoints[k];
      }
      Eigen::Matrix<double, N, 1> weights = numPoints / points.size();
      weights /= weights.sum();
      dist.setWeights(CategoricalDistribution<N>(weights));
      std::vector<NormalDistribution<M> > distributions;
      distributions.resize(N);
      for (size_t k = 0; k < N; ++k) {
        distributions[k].setMean(mean[k]);
        for (size_t i = 0; i < M; ++i)
          for (size_t j = i + 1; j < M; ++j)
            covariance[k](i, j) = covariance[k](j, i);
        distributions[k].setCovariance(covariance[k]);
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

template <size_t M, size_t N>
size_t EstimatorMLBatch<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  estimate(MixtureDistribution<LinearRegression<M>, N>& dist, const
  std::vector<Eigen::Matrix<double, M, 1> >& points,
  std::vector<Eigen::Matrix<double, N, 1> >& responsibilities, size_t
  maxNumIter, double tol) {
  size_t numIter = 0;
  responsibilities.clear();
  if (points.size()) {
    double oldLogLikelihood = 0;
    std::vector<LinearRegression<M> > distributions = dist.getDistributions();
    for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < N; ++j)
        distributions[j].setBasis(points[i].segment(0, M - 1));
      dist.setDistributions(distributions);
      oldLogLikelihood += log(dist(points[i](M - 1)));
    }
    responsibilities.resize(points.size());
    while (numIter != maxNumIter) {
      Eigen::Matrix<double, Eigen::Dynamic, N> responsibilityInternal(
        points.size(), (int)N);
      for (size_t i = 0; i < points.size(); ++i) {
        Eigen::Matrix<double, N, 1> responsibility;
        for (size_t j = 0; j < N; ++j)
          distributions[j].setBasis(points[i].segment(0, M - 1));
        dist.setDistributions(distributions);
        for (size_t k = 0; k < N; ++k) {
          Eigen::Matrix<size_t, N, 1> component =
            Eigen::Matrix<size_t, N, 1>::Zero();
          component(k) = 1.0;
          responsibility(k) = dist.getWeights()(component) *
            dist.getDistributions()[k](points[i](M - 1));
          responsibilityInternal(i, k) = responsibility(k);
        }
        responsibility /= dist(points[i](M - 1));
        responsibilities[i] = responsibility;
      }
      Eigen::Matrix<double, Eigen::Dynamic, 1> targets(points.size());
      Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(points.size(),
        (int)M);
      for (size_t i = 0; i < points.size(); ++i) {
        targets(i) = points[i](M - 1);
        designMatrix(i, 0) = 1.0;
        designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
      }
      for (size_t k = 0; k < N; ++k) {
        (designMatrix.transpose() * responsibilityInternal.col(k).asDiagonal() * designMatrix).inverse() *
          designMatrix.transpose() * responsibilityInternal.col(k).asDiagonal() * targets;
      }
//      std::vector<Eigen::Matrix<double, M, 1> > mean(N);
//      for (size_t k = 0; k < N; ++k)
//        mean[k] = Eigen::Matrix<double, M, 1>::Zero();
//      Eigen::Matrix<double, N, 1> numPoints =
//        Eigen::Matrix<double, N, 1>::Zero();
//      for (size_t i = 0; i < points.size(); ++i) {
//        for (size_t k = 0; k < N; ++k)
//          mean[k] += responsibilities[i](k) * points[i];
//        numPoints += responsibilities[i];
//      }
//      for (size_t k = 0; k < N; ++k)
//        mean[k] /= numPoints[k];
//      std::vector<Eigen::Matrix<double, M, M> > covariance(N);
//      for (size_t k = 0; k < N; ++k)
//        covariance[k] = Eigen::Matrix<double, M, M>::Zero();
//      for (size_t i = 0; i < points.size(); ++i)
//        for (size_t k = 0; k < N; ++k)
//          covariance[k] += responsibilities[i](k) * (points[i] - mean[k]) *
//            (points[i] - mean[k]).transpose();
//      for (size_t k = 0; k < N; ++k) {
//        covariance[k] /= numPoints[k];
//      }
//      Eigen::Matrix<double, N, 1> weights = numPoints / points.size();
//      weights /= weights.sum();
//      dist.setWeights(CategoricalDistribution<N>(weights));
//      std::vector<NormalDistribution<M> > distributions;
//      distributions.resize(N);
//      for (size_t k = 0; k < N; ++k) {
//        distributions[k].setMean(mean[k]);
//        for (size_t i = 0; i < M; ++i)
//          for (size_t j = i + 1; j < M; ++j)
//            covariance[k](i, j) = covariance[k](j, i);
//        distributions[k].setCovariance(covariance[k]);
//      }
//      dist.setDistributions(distributions);
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
