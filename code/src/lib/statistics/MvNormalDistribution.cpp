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

#include <Eigen/Core>

#include <iostream>
#include <fstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

MvNormalDistribution::MvNormalDistribution(const std::vector<double>&
  meanVector, const std::vector<std::vector<double> >& covarianceMatrix)
  throw (OutOfBoundException) :
  mMeanVector(meanVector),
  mCovarianceMatrix(covarianceMatrix) {
  if (meanVector.size() != covarianceMatrix.size() ||
    covarianceMatrix.size() == 0 ||
    covarianceMatrix.size() != covarianceMatrix[0].size())
    throw OutOfBoundException("MvNormalDistribution::MvNormalDistribution");
}

MvNormalDistribution::MvNormalDistribution(const MvNormalDistribution& other) :
  mMeanVector(other.mMeanVector),
  mCovarianceMatrix(other.mCovarianceMatrix) {
}

MvNormalDistribution& MvNormalDistribution::operator = (const
  MvNormalDistribution& other) {
  mMeanVector = other.mMeanVector;
  mCovarianceMatrix = other.mCovarianceMatrix;
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

void MvNormalDistribution::setMean(const std::vector<double>& meanVector)
  throw (OutOfBoundException) {
  if (meanVector.size() != mMeanVector.size())
    throw OutOfBoundException("MvNormalDistribution::setMean(): wrong dimensions for the mean");
}

const std::vector<double>& MvNormalDistribution::getMean() const {
  return mMeanVector;
}

void MvNormalDistribution::setCovariance(
  const std::vector<std::vector<double> >& covarianceMatrix)
  throw (OutOfBoundException) {
  if (covarianceMatrix.size() != mCovarianceMatrix.size() ||
    covarianceMatrix[0].size() != mCovarianceMatrix[0].size())
    throw OutOfBoundException("MvNormalDistribution::setCovariance(): wrong dimensions for the covariance");
}

const std::vector<std::vector<double> >& MvNormalDistribution::getCovariance()
  const {
  return mCovarianceMatrix;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double MvNormalDistribution::pdf(const std::vector<double>& xVector) const
  throw (OutOfBoundException) {
  if (xVector.size() != mMeanVector.size())
    throw OutOfBoundException("MvNormalDistribution::pdf(): wrong dimensions for input");
}

const std::vector<double>& MvNormalDistribution::sample() const {
}

double MvNormalDistribution::KLDivergence(const MvNormalDistribution& other)
  const throw (OutOfBoundException) {
}
