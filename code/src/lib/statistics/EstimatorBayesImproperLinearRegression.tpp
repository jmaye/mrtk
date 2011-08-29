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
/* Constructors and Destructor                                                */
/******************************************************************************/

template <size_t M>
EstimatorBayesImproper<LinearRegression<M>, M>::EstimatorBayesImproper(double
  tol) :
  mSampleCoeff(Eigen::Matrix<double, M, 1>::Zero()),
  mSampleVariance(0),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M>, M>::EstimatorBayesImproper(const
  EstimatorBayesImproper<LinearRegression<M>, M>& other) :
  mPostCoeffDist(other.mPostCoeffDist),
  mPostVarianceDist(other.mPostVarianceDist),
  mPostPredDist(other.mPostPredDist),
  mSampleCoeff(other.mSampleCoeff),
  mSampleVariance(other.mSampleCovariance),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M>, M>&
  EstimatorBayesImproper<LinearRegression<M>, M>::operator =
  (const EstimatorBayesImproper<LinearRegression<M>, M>& other) {
  if (this != &other) {
    mPostCoeffDist = other.mPostCoeffDist;
    mPostVarianceDist = other.mPostVarianceDist;
    mPostPredDist = other.mPostPredDist;
    mSampleCoeff = other.mSampleCoeff;
    mSampleVariance = other.mSampleVariance;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorBayesImproper<LinearRegression<M>, M>::~EstimatorBayesImproper() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::read(std::istream&
  stream) {
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::write(std::ostream&
  stream) const {
  stream << "posterior coefficients distribution: " << std::endl
    << mPostCoeffDist
    << std::endl << "posterior variance distribution: " << std::endl
    << mPostVarianceDist << std::endl
    << "posterior predictive distribution: " << std::endl << mPostPredDist
    << std::endl
    << "sample coefficients: " << mSampleCoeff.transpose() << std::endl
    << "sample variance: " << mSampleVariance << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::read(std::ifstream&
  stream) {
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::write(std::ofstream&
  stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
const StudentDistribution<M>& EstimatorBayesImproper<LinearRegression<M>, M>::
getPostCoeffDist() const {
  return mPostCoeffDist;
}

template <size_t M>
const ScaledInvChiSquareDistribution&
EstimatorBayesImproper<LinearRegression<M>, M>::getPostVarianceDist()
  const {
  return mPostVarianceDist;
}

template <size_t M>
const LinearRegressionPred<M>& EstimatorBayesImproper<LinearRegression<M>, M>::
getPostPredDist() const {
  return mPostPredDist;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorBayesImproper<LinearRegression<M>, M>::getSampleCoeff() const {
  return mSampleCoeff;
}

template <size_t M>
double EstimatorBayesImproper<LinearRegression<M>, M>::getSampleVariance()
  const {
  return mSampleVariance;
}

template <size_t M>
double EstimatorBayesImproper<LinearRegression<M>, M>::getTolerance() const {
  return mTol;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::setTolerance(double tol) {
  mTol = tol;
}

template <size_t M>
size_t EstimatorBayesImproper<LinearRegression<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorBayesImproper<LinearRegression<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::reset() {
  mSampleCoeff = Eigen::Matrix<double, M, 1>::Zero();
  mSampleVariance = 0;
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorBayesImproper<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  reset();
  if (points.size() > M) {
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
    if (points.size() < M || invCheckMatrix.determinant() < mTol)
      return;
    mSampleCoeff = invCheckMatrix.inverse() * designMatrix.transpose() *
      targets;
    mSampleVariance = ((targets - designMatrix * mSampleCoeff).transpose() *
      (targets - designMatrix * mSampleCoeff))(0);
    mSampleVariance /= points.size() - M;
    mValid = true;
    mNumPoints = points.size();
    Eigen::Matrix<double, M, M> coeffCovariance = (designMatrix.transpose() *
      designMatrix).inverse();
    mPostVarianceDist.setDegrees(mNumPoints - M);
    mPostVarianceDist.setScale(mSampleVariance);
    mPostCoeffDist.setDegrees(mNumPoints - M);
    mPostCoeffDist.setLocation(mSampleCoeff);
    mPostCoeffDist.setScale(mSampleVariance * coeffCovariance);
    mPostPredDist.setDegrees(mNumPoints - M);
    mPostPredDist.setCoefficients(mSampleCoeff);
    mPostPredDist.setCoeffCovariance(coeffCovariance);
    mPostPredDist.setRegressionVariance(mSampleVariance);
    mValid = true;
  }
}
