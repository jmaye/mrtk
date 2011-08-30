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

#include <Eigen/QR>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>::EstimatorBayes() :
  mSampleCoeff(Eigen::Matrix<double, M, 1>::Zero()),
  mSampleCoeffCovariance(Eigen::Matrix<double, M, M>::Identity()),
  mSampleRegressionVariance(0),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>::EstimatorBayes(const
  EstimatorBayes<LinearRegression<M>, M>& other) :
  mPostCoeffDist(other.mPostCoeffDist),
  mPostVarianceDist(other.mPostVarianceDist),
  mPostPredDist(other.mPostPredDist),
  mSampleCoeff(other.mSampleCoeff),
  mSampleCoeffCovariance(other.mSampleCoeffCovariance),
  mSampleRegressionVariance(other.mSampleRegressionVariance),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>&
  EstimatorBayes<LinearRegression<M>, M>::operator =
  (const EstimatorBayes<LinearRegression<M>, M>& other) {
  if (this != &other) {
    mPostCoeffDist = other.mPostCoeffDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mSampleCoeff = other.mSampleCoeff;
    mSampleCoeffCovariance = other.mSampleCoeffCovariance;
    mSampleRegressionVariance = other.mSampleRegressionVariance;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorBayes<LinearRegression<M>, M>::~EstimatorBayes() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::write(std::ostream& stream) const {
  stream << "posterior coefficients distribution: " << std::endl
    << mPostCoeffDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist
    << std::endl
    << "sample coefficients: " << mSampleCoeff.transpose() << std::endl
    << "sample coefficients covariance: " << std::endl
    << mSampleCoeffCovariance << std::endl
    << "sample regression variance: " << mSampleRegressionVariance << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::write(std::ofstream& stream)
  const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>& EstimatorBayes<LinearRegression<M>, M>::
  getPostCoeffDist() const {
  return mPostCoeffDist;
}

template <size_t M>
const ScaledInvChiSquareDistribution&
EstimatorBayes<LinearRegression<M>, M>::getPostVarianceDist() const {
  return mPostVarianceDist;
}

template <size_t M>
const LinearRegressionPred<M>& EstimatorBayes<LinearRegression<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorBayes<LinearRegression<M>, M>::getSampleCoeff() const {
  return mSampleCoeff;
}

template <size_t M>
const Eigen::Matrix<double, M, M>&
EstimatorBayes<LinearRegression<M>, M>::getSampleCoeffCovariance() const {
  return mSampleCoeffCovariance;
}

template <size_t M>
double EstimatorBayes<LinearRegression<M>, M>::getSampleRegressionVariance()
  const {
  return mSampleRegressionVariance;
}

template <size_t M>
size_t EstimatorBayes<LinearRegression<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayes<LinearRegression<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::reset() {
  mSampleCoeff = Eigen::Matrix<double, M, 1>::Zero();
  mSampleCoeffCovariance = Eigen::Matrix<double, M, M>::Identity();
  mSampleRegressionVariance = 0;
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  Eigen::Matrix<double, Eigen::Dynamic, 1> weights =
    Eigen::Matrix<double, Eigen::Dynamic, 1>::Ones(points.size());
  return addPoints(points, weights);
}

template <size_t M>
void EstimatorBayes<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points, const
  Eigen::Matrix<double, Eigen::Dynamic, 1>& weights) {
  reset();
  mNumPoints = points.size();
  if ((size_t)weights.size() != mNumPoints)
    return;
  Eigen::Matrix<double, Eigen::Dynamic, 1> targets(mNumPoints);
  Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(mNumPoints, (int)M);
  for (size_t i = 0; i < mNumPoints; ++i) {
    targets(i) = points[i](M - 1);
    designMatrix(i, 0) = 1.0;
    designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
  }
  Eigen::QR<Eigen::Matrix<double, Eigen::Dynamic, M> > qrDecomp =
    (weights.asDiagonal() * designMatrix).qr();
  if (mNumPoints > M && qrDecomp.rank() == M) {
    Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> coeff;
    qrDecomp.solve(weights.asDiagonal() * targets, &coeff);
    mSampleCoeff = coeff;
    mSampleRegressionVariance = ((targets - designMatrix *
      mSampleCoeff).transpose() * weights.asDiagonal() * (targets -
      designMatrix * mSampleCoeff))(0) / (points.size() - M);
    Eigen::Matrix<double, M, M> invR = qrDecomp.matrixR().inverse();
    mSampleCoeffCovariance = invR * invR.transpose();
    mPostVarianceDist.setDegrees(mNumPoints - M);
    mPostVarianceDist.setScale(mSampleRegressionVariance);
    mPostCoeffDist.setDegrees(mNumPoints - M);
    mPostCoeffDist.setLocation(mSampleCoeff);
    mPostCoeffDist.setScale(mSampleRegressionVariance * mSampleCoeffCovariance);
    mPostPredDist.setDegrees(mNumPoints - M);
    mPostPredDist.setCoefficients(mSampleCoeff);
    mPostPredDist.setCoeffCovariance(mSampleCoeffCovariance);
    mPostPredDist.setRegressionVariance(mSampleRegressionVariance);
    mValid = true;
  }
  else
    mValid = false;
}
