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

#include <limits>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EstimatorMLOnline<NormalDistribution<1> >::EstimatorMLOnline() :
  mNumPoints(0) {
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::EstimatorMLOnline() :
  mNumPoints(0) {
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>::EstimatorMLOnline() :
  mNumPoints(0) {
}

template <size_t M>
EstimatorMLOnline<MultinomialDistribution<M>, M>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<ExponentialDistribution>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<GeometricDistribution>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<PoissonDistribution>::EstimatorMLOnline() :
  mNumPoints(0) {
}

EstimatorMLOnline<NormalDistribution<1> >::EstimatorMLOnline(const
  EstimatorMLOnline<NormalDistribution<1> >& other) :
  mNumPoints(other.mNumPoints) {
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::EstimatorMLOnline(const
  EstimatorMLOnline<NormalDistribution<M>, M>& other) :
  mNumPoints(other.mNumPoints) {
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>::EstimatorMLOnline(const
  EstimatorMLOnline<CategoricalDistribution<M>, M>& other) :
  mNumPoints(other.mNumPoints) {
}

template <size_t M>
EstimatorMLOnline<MultinomialDistribution<M>, M>::EstimatorMLOnline(const
  EstimatorMLOnline<MultinomialDistribution<M>, M>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<ExponentialDistribution>::EstimatorMLOnline(const
  EstimatorMLOnline<ExponentialDistribution>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<GeometricDistribution>::EstimatorMLOnline(const
  EstimatorMLOnline<GeometricDistribution>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<PoissonDistribution>::EstimatorMLOnline(const
  EstimatorMLOnline<PoissonDistribution>& other) :
  mNumPoints(other.mNumPoints) {
}

EstimatorMLOnline<NormalDistribution<1> >&
  EstimatorMLOnline<NormalDistribution<1> >::operator =
  (const EstimatorMLOnline<NormalDistribution<1> >& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>&
  EstimatorMLOnline<NormalDistribution<M>, M>::operator =
  (const EstimatorMLOnline<NormalDistribution<M>, M>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>&
  EstimatorMLOnline<CategoricalDistribution<M>, M>::operator =
  (const EstimatorMLOnline<CategoricalDistribution<M>, M>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

template <size_t M>
EstimatorMLOnline<MultinomialDistribution<M>, M>&
  EstimatorMLOnline<MultinomialDistribution<M>, M>::operator =
  (const EstimatorMLOnline<MultinomialDistribution<M>, M>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<ExponentialDistribution>&
  EstimatorMLOnline<ExponentialDistribution>::operator =
  (const EstimatorMLOnline<ExponentialDistribution>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<GeometricDistribution>&
  EstimatorMLOnline<GeometricDistribution>::operator =
  (const EstimatorMLOnline<GeometricDistribution>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<PoissonDistribution>&
  EstimatorMLOnline<PoissonDistribution>::operator =
  (const EstimatorMLOnline<PoissonDistribution>& other) {
  if (this != &other) {
    mNumPoints = other.mNumPoints;
  }
  return *this;
}

EstimatorMLOnline<NormalDistribution<1> >::~EstimatorMLOnline() {
}

template <size_t M>
EstimatorMLOnline<NormalDistribution<M>, M>::~EstimatorMLOnline() {
}

template <size_t M>
EstimatorMLOnline<CategoricalDistribution<M>, M>::~EstimatorMLOnline() {
}

template <size_t M>
EstimatorMLOnline<MultinomialDistribution<M>, M>::~EstimatorMLOnline() {
}

EstimatorMLOnline<ExponentialDistribution>::~EstimatorMLOnline() {
}

EstimatorMLOnline<GeometricDistribution>::~EstimatorMLOnline() {
}

EstimatorMLOnline<PoissonDistribution>::~EstimatorMLOnline() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

void EstimatorMLOnline<NormalDistribution<1> >::read(std::istream& stream) {
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::read(std::istream&
  stream) {
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::read(std::istream&
  stream) {
}

void EstimatorMLOnline<ExponentialDistribution>::read(std::istream& stream) {
}

void EstimatorMLOnline<GeometricDistribution>::read(std::istream& stream) {
}

void EstimatorMLOnline<PoissonDistribution>::read(std::istream& stream) {
}

void EstimatorMLOnline<NormalDistribution<1> >::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::write(std::ostream&
  stream) const {
  stream << "number of points: " << mNumPoints;
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::write(std::ostream&
  stream) const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<ExponentialDistribution>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<GeometricDistribution>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<PoissonDistribution>::write(std::ostream& stream)
  const {
  stream << "number of points: " << mNumPoints;
}

void EstimatorMLOnline<NormalDistribution<1> >::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::read(std::ifstream&
  stream) {
}

void EstimatorMLOnline<ExponentialDistribution>::read(std::ifstream& stream) {
}

void EstimatorMLOnline<GeometricDistribution>::read(std::ifstream& stream) {
}

void EstimatorMLOnline<PoissonDistribution>::read(std::ifstream& stream) {
}

void EstimatorMLOnline<NormalDistribution<1> >::write(std::ofstream& stream)
  const {
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::write(std::ofstream& stream)
  const {
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::write(std::ofstream&
  stream) const {
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::write(std::ofstream&
  stream) const {
}

void EstimatorMLOnline<ExponentialDistribution>::write(std::ofstream& stream)
  const {
}

void EstimatorMLOnline<GeometricDistribution>::write(std::ofstream& stream)
  const {
}

void EstimatorMLOnline<PoissonDistribution>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void EstimatorMLOnline<NormalDistribution<1> >::setNumPoints(size_t numPoints) {
  mNumPoints = numPoints;
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

void EstimatorMLOnline<ExponentialDistribution>::setNumPoints(size_t
  numPoints) {
  mNumPoints = numPoints;
}

void EstimatorMLOnline<GeometricDistribution>::setNumPoints(size_t numPoints) {
  mNumPoints = numPoints;
}

void EstimatorMLOnline<PoissonDistribution>::setNumPoints(size_t numPoints) {
  mNumPoints = numPoints;
}

size_t EstimatorMLOnline<NormalDistribution<1> >::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
size_t EstimatorMLOnline<NormalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
size_t EstimatorMLOnline<CategoricalDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
size_t EstimatorMLOnline<MultinomialDistribution<M>, M>::getNumPoints() const {
  return mNumPoints;
}

size_t EstimatorMLOnline<ExponentialDistribution>::getNumPoints() const {
  return mNumPoints;
}

size_t EstimatorMLOnline<GeometricDistribution>::getNumPoints() const {
  return mNumPoints;
}

size_t EstimatorMLOnline<PoissonDistribution>::getNumPoints() const {
  return mNumPoints;
}

void EstimatorMLOnline<NormalDistribution<1> >::addPoint(NormalDistribution<1>&
  dist, const NormalDistribution<1>::VariableType& point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  double variance = dist.getVariance();
  variance += 1.0 / mNumPoints * ((point - mean) * (point - mean) - variance);
  if (variance == 0.0 || mNumPoints == 1)
    variance = dist.getVariance();
  dist.setMean(mean);
  try {
    dist.setVariance(variance);
  }
  catch (BadArgumentException<double>& e) {
  }
}

template <size_t M>
void EstimatorMLOnline<NormalDistribution<M>, M>::addPoint(
  NormalDistribution<M>& dist, const typename
  NormalDistribution<M>::VariableType& point) {
  mNumPoints++;
  Eigen::Matrix<double, M, 1> mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  Eigen::Matrix<double, M, M> covariance = dist.getCovariance();
  covariance += 1.0 / mNumPoints * ((point - mean) * (point - mean).transpose()
    - covariance);
  if (mNumPoints == 1)
    covariance = dist.getCovariance();
  dist.setMean(mean);
  try {
    dist.setCovariance(covariance);
  }
  catch (BadArgumentException<Eigen::Matrix<double, M, M> >& e) {
  }
}

template <size_t M>
void EstimatorMLOnline<CategoricalDistribution<M>, M>::addPoint(
  CategoricalDistribution<M>& dist, const Eigen::Matrix<size_t, M, 1>& point) {
  mNumPoints++;
  Eigen::Matrix<double, M, 1> successProbabilities =
    Eigen::Matrix<double, M, 1>::Zero();
  if (mNumPoints == 1) {
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += point(i);
  }
  else {
    successProbabilities = dist.getSuccessProbabilities();
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += 1.0 / mNumPoints * (point(i) -
        successProbabilities(i));
  }
  successProbabilities /= successProbabilities.sum();
  dist.setSuccessProbabilities(successProbabilities);
}

template <size_t M>
void EstimatorMLOnline<MultinomialDistribution<M>, M>::addPoint(
  MultinomialDistribution<M>& dist, const Eigen::Matrix<size_t, M, 1>& point) {
  mNumPoints++;
  Eigen::Matrix<double, M, 1> successProbabilities =
    Eigen::Matrix<double, M, 1>::Zero();
  size_t numTrials;
  if (mNumPoints == 1) {
    numTrials = point.sum();
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += point(i) / (double)numTrials;
  }
  else {
    successProbabilities = dist.getSuccessProbabilities();
    numTrials = dist.getNumTrials();
    numTrials += 1.0 / mNumPoints * (point.sum() - numTrials);
    for (size_t i = 0; i < M; ++i)
      successProbabilities(i) += 1.0 / mNumPoints * (point(i) /
        (double)numTrials - successProbabilities(i));
  }
  successProbabilities /= successProbabilities.sum();
  dist.setSuccessProbabilities(successProbabilities);
  dist.setNumTrials(numTrials);
}

void EstimatorMLOnline<ExponentialDistribution>::addPoint(
  ExponentialDistribution& dist, const ExponentialDistribution::VariableType&
  point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  dist.setRate(1.0 / mean);
}

void EstimatorMLOnline<GeometricDistribution>::addPoint(GeometricDistribution&
  dist, const GeometricDistribution::VariableType& point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  mean++;
  dist.setSuccessProbability(1.0 / mean);
}

void EstimatorMLOnline<PoissonDistribution>::addPoint(PoissonDistribution& dist,
  const PoissonDistribution::VariableType& point) {
  mNumPoints++;
  double mean;
  if (mNumPoints == 1)
    mean = point;
  else {
    mean = dist.getMean();
    mean += 1.0 / mNumPoints * (point - mean);
  }
  if (mean == 0)
    mean = std::numeric_limits<double>::epsilon();
  dist.setRate(mean);
}
