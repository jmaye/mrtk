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

#include "statistics/MvNormalDistribution.h"

#include "statistics/Randomizer.h"

#include <Eigen/LU>
#include <Eigen/Geometry>

#include <iostream>
#include <fstream>

#include <cmath>
#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MvNormalDistribution::MvNormalDistribution(const Eigen::VectorXd& meanVector,
  const Eigen::MatrixXd& covarianceMatrix) throw (OutOfBoundException) :
  mMeanVector(meanVector) {
  if (meanVector.rows() < 2 || meanVector.rows() != covarianceMatrix.rows())
    throw OutOfBoundException("MvNormalDistribution::MvNormalDistribution(): wrong dimensions for mean or covariance");
  mCovarianceMatrix.resize(covarianceMatrix.rows(), covarianceMatrix.cols());
  setCovariance(covarianceMatrix);
}

MvNormalDistribution::MvNormalDistribution(const MvNormalDistribution& other) :
  mMeanVector(other.mMeanVector),
  mCovarianceMatrix(other.mCovarianceMatrix),
  mPrecisionMatrix(other.mPrecisionMatrix),
  mf64Determinant(other.mf64Determinant),
  mf64Normalizer(other.mf64Normalizer),
  mTransformation(other.mTransformation) {
}

MvNormalDistribution& MvNormalDistribution::operator = (const
  MvNormalDistribution& other) {
  mMeanVector = other.mMeanVector;
  mCovarianceMatrix = other.mCovarianceMatrix;
  mPrecisionMatrix = other.mPrecisionMatrix;
  mf64Determinant = other.mf64Determinant;
  mf64Normalizer = other.mf64Normalizer;
  mTransformation = other.mTransformation;
  return *this;
}

MvNormalDistribution::~MvNormalDistribution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void MvNormalDistribution::read(std::istream& stream) {
}

void MvNormalDistribution::write(std::ostream& stream) const {
  stream << "mMeanVector: " << std::endl << mMeanVector << std::endl
    << "mCovarianceMatrix: " << std::endl << mCovarianceMatrix;
}

void MvNormalDistribution::read(std::ifstream& stream) {
}

void MvNormalDistribution::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream,
  const MvNormalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, MvNormalDistribution& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream,
  const MvNormalDistribution& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, MvNormalDistribution& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void MvNormalDistribution::setMean(const Eigen::VectorXd& meanVector)
  throw (OutOfBoundException) {
  if (meanVector.rows() != mMeanVector.rows())
    throw OutOfBoundException("MvNormalDistribution::setMean(): wrong dimensions for the mean");
  mMeanVector = meanVector;
}

const Eigen::VectorXd& MvNormalDistribution::getMean() const {
  return mMeanVector;
}

void MvNormalDistribution::setCovariance(const Eigen::MatrixXd&
  covarianceMatrix) throw (OutOfBoundException) {
  if (covarianceMatrix.cols() != mCovarianceMatrix.cols())
   throw OutOfBoundException("MvNormalDistribution::setCovariance(): wrong dimensions for the covariance");
  if (covarianceMatrix.transpose() != covarianceMatrix)
    throw OutOfBoundException("MvNormalDistribution::setCovariance(): covariance must be symmetric");
  mTransformation = covarianceMatrix.llt();
  if (mTransformation.isPositiveDefinite() == false)
    throw OutOfBoundException("MvNormalDistribution::setCovariance(): covariance must be positive definite");
  if ((covarianceMatrix.diagonal().cwise() < 0).any() == true)
    throw OutOfBoundException("MvNormalDistribution::setCovariance(): variances must be positive");
  mf64Determinant = covarianceMatrix.determinant();
  mPrecisionMatrix = covarianceMatrix.inverse();
  mf64Normalizer = pow(2.0 * M_PI, 0.5 * covarianceMatrix.cols()) *
    sqrt(mf64Determinant);
  mCovarianceMatrix = covarianceMatrix;
}

const Eigen::MatrixXd& MvNormalDistribution::getCovariance() const {
  return mCovarianceMatrix;
}

const Eigen::MatrixXd& MvNormalDistribution::getPrecision() const {
  return mPrecisionMatrix;
}

double MvNormalDistribution::getDeterminant() const {
  return mf64Determinant;
}

double MvNormalDistribution::getNormalizer() const {
  return mf64Normalizer;
}

const Eigen::LLT<Eigen::MatrixXd>& MvNormalDistribution::getTransformation()
  const {
  return mTransformation;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double MvNormalDistribution::pdf(const Eigen::VectorXd& xVector) const
  throw (OutOfBoundException) {
  if (xVector.rows() != mMeanVector.rows())
    throw OutOfBoundException("MvNormalDistribution::pdf(): wrong dimensions for input");
  return 1 / mf64Normalizer * exp(-0.5 *
    ((mMeanVector - xVector).transpose() * mPrecisionMatrix *
    (mMeanVector - xVector))(0, 0));
}

const Eigen::VectorXd MvNormalDistribution::sample() const {
  static Randomizer randomizer;
  return randomizer.sampleNormal(*this);
}

double MvNormalDistribution::KLDivergence(const MvNormalDistribution& other)
  const throw (OutOfBoundException) {
  if (other.mMeanVector.rows() != mMeanVector.rows() ||
    other.mCovarianceMatrix.rows() != mCovarianceMatrix.rows())
    throw OutOfBoundException("MvNormalDistribution::KLDivergence(): incompatible dimensions");
  return 0.5 * (log(other.mf64Determinant / mf64Determinant) +
    (other.mPrecisionMatrix * mCovarianceMatrix).trace() - mMeanVector.rows() +
    ((mMeanVector - other.mMeanVector).transpose() * other.mPrecisionMatrix *
    (mMeanVector - other.mMeanVector))(0, 0));
}

double MvNormalDistribution::mahalanobisDistance(const Eigen::VectorXd& xVector)
  const throw (OutOfBoundException) {
  if (xVector.rows() != mMeanVector.rows())
    throw OutOfBoundException("MvNormalDistribution::mahalanobisDistance(): incompatible dimensions");
  return sqrt(((xVector - mMeanVector) * mPrecisionMatrix *
    (xVector - mMeanVector))(0, 0));
}
