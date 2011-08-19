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

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::EstimatorML(
  const Eigen::Matrix<double, N, M>& coefficients,
  const Eigen::Matrix<double, N, 1>& variances,
  const Eigen::Matrix<double, N, 1>& weights, size_t maxNumIter, double tol) :
  mCoefficients(coefficients),
  mVariances(variances),
  mWeights(weights),
  mMaxNumIter(maxNumIter),
  mTol(tol),
  mNumPoints(0),
  mValid(false) {
}

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::EstimatorML(
  const EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>& other) :
  mCoefficients(other.mCoefficients),
  mVariances(other.mVariances),
  mResponsibilities(other.mResponsibilities),
  mWeights(other.mWeights),
  mMaxNumIter(other.mMaxNumIter),
  mTol(other.mTol),
  mNumPoints(other.mNumPoints),
  mValid(other.mValid) {
}

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>&
  EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::operator =
  (const EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>&
  other) {
  if (this != &other) {
    mCoefficients = other.mCoefficients;
    mVariances = other.mVariances;
    mResponsibilities = other.mResponsibilities;
    mWeights = other.mWeights;
    mMaxNumIter = other.mMaxNumIter;
    mTol = other.mTol;
    mNumPoints = other.mNumPoints;
    mValid = other.mValid;
  }
  return *this;
}

template <size_t M, size_t N>
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::~EstimatorML() {
}

/******************************************************************************/
/* Streaming operations                                                       */
/******************************************************************************/

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::read(
  std::istream& stream) {
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::write(
  std::ostream& stream) const {
  stream << "coefficients: " << std::endl << mCoefficients << std::endl
    << "variances: " << mVariances.transpose() << std::endl
    << "weights: " << mWeights.transpose() << std::endl
    << "maxNumIter: " << mMaxNumIter << std::endl
    << "tolerance: " << mTol << std::endl
    << "number of points: " << mNumPoints << std::endl
    << "valid: " << mValid;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::read(
  std::ifstream& stream) {
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::write(
  std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getNumPoints() const {
  return mNumPoints;
}

template <size_t M, size_t N>
bool EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::getValid()
  const {
  return mValid;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, M>&
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getCoefficients() const {
  return mCoefficients;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getVariances() const {
  return mVariances;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, Eigen::Dynamic, N>&
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getResponsibilities() const {
  return mResponsibilities;
}

template <size_t M, size_t N>
const Eigen::Matrix<double, N, 1>&
EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getWeights() const {
  return mWeights;
}

template <size_t M, size_t N>
double EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
getTolerance() const {
  return mTol;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  setTolerance(double tol) {
  mTol = tol;
}

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  getMaxNumIter() const {
  return mMaxNumIter;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  setMaxNumIter(size_t maxNumIter) {
  mMaxNumIter = maxNumIter;
}

template <size_t M, size_t N>
void EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::reset() {
  mNumPoints = 0;
  mValid = false;
}

template <size_t M, size_t N>
size_t EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::
  addPoints(const std::vector<Eigen::Matrix<double, M, 1> >& points) {
  size_t numIter = 0;
  reset();
  if (points.size()) {
    double oldLogLikelihood = 0;
    mResponsibilities.resize(points.size(), N);
    for (size_t i = 0; i < points.size(); ++i) {
      Eigen::Matrix<double, M, 1> basisTrans;
      basisTrans << 1, points[i].segment(0, M - 1);
      double probability = 0.0;
      for (size_t j = 0; j < N; ++j) {
        probability += mWeights(j) *
          NormalDistribution<1>((mCoefficients.row(j) * basisTrans)(0),
          mVariances(j))(points[i](M - 1));
      }
      oldLogLikelihood += log(probability);
    }
    std::cout << "Init ll: " << oldLogLikelihood << std::endl;
    return 0;
//    while (numIter != maxNumIter) {
//      for (size_t i = 0; i < points.size(); ++i) {
//        for (size_t j = 0; j < N; ++j)
//          distributions[j].setBasis(points[i].segment(0, M - 1));
//        dist.setDistributions(distributions);
//        for (size_t k = 0; k < N; ++k) {
//          Eigen::Matrix<size_t, N, 1> component =
//            Eigen::Matrix<size_t, N, 1>::Zero();
//          component(k) = 1.0;
//          responsibilities(i, k) = dist.getWeights()(component) *
//            dist.getDistributions()[k](points[i](M - 1));
//        }
//        responsibilities.row(i) /= dist(points[i](M - 1));
//      }
//      Eigen::Matrix<double, N, 1> numPoints =
//        Eigen::Matrix<double, N, 1>::Zero();
//      for (size_t k = 0; k < N; ++k)
//        numPoints(k) = responsibilities.col(k).sum();
//      Eigen::Matrix<double, N, 1> weights = numPoints / points.size();
//      weights /= weights.sum();
//      dist.setWeights(CategoricalDistribution<N>(weights));
//      Eigen::Matrix<double, Eigen::Dynamic, 1> targets(points.size());
//      Eigen::Matrix<double, Eigen::Dynamic, M> designMatrix(points.size(),
//        (int)M);
//      for (size_t i = 0; i < points.size(); ++i) {
//        targets(i) = points[i](M - 1);
//        designMatrix(i, 0) = 1.0;
//        designMatrix.row(i).segment(1, M - 1) = points[i].segment(0, M - 1);
//      }
//      for (size_t k = 0; k < N; ++k) {
//        Eigen::Matrix<double, M, M> invCheckMatrix = designMatrix.transpose() *
//          responsibilities.col(k).asDiagonal() * designMatrix;
//        if (invCheckMatrix.determinant() < tol)
//          throw InvalidOperationException("EstimatorML<MixtureDistribution<LinearRegression<M>, N>, M, N>::estimate(): data cannot be fitted");
//        Eigen::Matrix<double, M, 1> coefficients = invCheckMatrix.inverse() *
//          designMatrix.transpose() * responsibilities.col(k).asDiagonal() *
//          targets;
//        double variance = 0.0;
//        for (size_t i = 0; i < points.size(); ++i)
//          variance += responsibilities(i, k) * (targets(i) -
//            (coefficients.transpose() * designMatrix.row(i).transpose())(0)) *
//            (targets(i) - (coefficients.transpose() *
//            designMatrix.row(i).transpose())(0));
//        variance /= numPoints(k);
//        distributions[k].setCoefficients(coefficients);
//        distributions[k].setVariance(variance);
//      }
//      double newLogLikelihood = 0;
//      for (size_t i = 0; i < points.size(); ++i) {
//        for (size_t j = 0; j < N; ++j)
//          distributions[j].setBasis(points[i].segment(0, M - 1));
//        dist.setDistributions(distributions);
//        newLogLikelihood += log(dist(points[i](M - 1)));
//      }
//      if (fabs(oldLogLikelihood - newLogLikelihood) < tol)
//        break;
//      oldLogLikelihood = newLogLikelihood;
//      numIter++;
//    }
  }
  return numIter;
}
