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
EstimatorML<LinearRegression<M>, M>::EstimatorML(double tol) :
  mCoefficients(Eigen::Matrix<double, M, 1>::Zero()),
  mVariance(0),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>::EstimatorML(const
  EstimatorML<LinearRegression<M>, M>& other) :
  mCoefficients(other.mCoefficients),
  mVariance(other.mVariance),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>&
  EstimatorML<LinearRegression<M>, M>::operator =
  (const EstimatorML<LinearRegression<M>, M>& other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariance = other.mVariance;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M>
EstimatorML<LinearRegression<M>, M>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::read(std::istream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::write(std::ostream& stream) const {
  stream << "coefficients: " << mCoefficients.transpose() << std::endl
    << "variance: " << mVariance << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::read(std::ifstream& stream) {
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M>
size_t EstimatorML<LinearRegression<M>, M>::getNumPoints() const {
  return mNumPoints;
}

template <size_t M>
bool EstimatorML<LinearRegression<M>, M>::getValid() const {
  return mValid;
}

template <size_t M>
const Eigen::Matrix<double, M, 1>&
EstimatorML<LinearRegression<M>, M>::getCoefficients() const {
  return mCoefficients;
}

template <size_t M>
double EstimatorML<LinearRegression<M>, M>::getVariance() const {
  return mVariance;
}

template <size_t M>
double EstimatorML<LinearRegression<M>, M>::getTolerance() const {
  return mTol;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::setTolerance(double tol) {
  mTol = tol;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::reset() {
  mCoefficients = Eigen::Matrix<double, M, 1>::Zero();
  mVariance = 0;
  mNumPoints = 0;
  mValid = false;
}

template <size_t M>
void EstimatorML<LinearRegression<M>, M>::addPoints(const
  std::vector<Eigen::Matrix<double, M, 1> >& points) {
  reset();
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
    if (points.size() < M || invCheckMatrix.determinant() < mTol)
      return;
    mCoefficients = invCheckMatrix.inverse() * designMatrix.transpose() *
      targets;
    //mVariance = targets - mCoefficients *
    for (size_t i = 0; i < points.size(); ++i)
      mVariance += (targets(i) - (mCoefficients.transpose() *
        designMatrix.row(i).transpose())(0)) * (targets(i) -
        (mCoefficients.transpose() * designMatrix.row(i).transpose())(0));
    mVariance /= points.size();
    mValid = true;
    mNumPoints = points.size();
  }
}
