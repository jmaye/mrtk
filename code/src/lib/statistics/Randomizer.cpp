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

#include "statistics/Randomizer.h"

#include <Eigen/LU>
#include <Eigen/Cholesky>
#include <Eigen/Geometry>

#include <iostream>
#include <fstream>
#include <limits>

#include <stdlib.h>
#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Randomizer::Randomizer(double f64Seed) :
  mf64Seed(f64Seed) {
  srandom((uint32_t)round(f64Seed));
}

Randomizer::Randomizer(const Randomizer& other) :
  mf64Seed(other.mf64Seed) {
}

Randomizer& Randomizer::operator = (const Randomizer& other) {
  mf64Seed = other.mf64Seed;
  return *this;
}

Randomizer::~Randomizer() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Randomizer::read(std::istream& stream) {
}

void Randomizer::write(std::ostream& stream) const {
  stream << "mf64Seed: " << mf64Seed;
}

void Randomizer::read(std::ifstream& stream) {
}

void Randomizer::write(std::ofstream& stream) const {
}

std::ostream& operator << (std::ostream& stream, const Randomizer& obj) {
  obj.write(stream);
  return stream;
}

std::istream& operator >> (std::istream& stream, Randomizer& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Randomizer& obj) {
  obj.write(stream);
  return stream;
}

std::ifstream& operator >> (std::ifstream& stream, Randomizer& obj) {
  obj.read(stream);
  return stream;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Randomizer::setSeed(double f64Seed) {
  mf64Seed = f64Seed;
  srandom((uint32_t)round(mf64Seed));
}

double Randomizer::getSeed() const {
  return mf64Seed;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

double Randomizer::sampleUniform(double f64MinSupport, double f64MaxSupport)
  const throw (OutOfBoundException) {
  if (f64MinSupport >= f64MaxSupport)
    throw OutOfBoundException("Randomizer::sampleUniform(): f64MinSupport must be smaller than f64MaxSupport");
  double f64U = (double)random() / (double)RAND_MAX;
  return f64MinSupport + (f64MaxSupport - f64MinSupport) * f64U;
}

int32_t Randomizer::sampleUniform(int32_t i32MinSupport, int32_t i32MaxSupport)
  const throw (OutOfBoundException) {
  if (i32MinSupport > i32MaxSupport)
    throw OutOfBoundException("Randomizer::sampleUniform(): i32MinSupport must be smaller or equal to i32MaxSupport");
  double f64U = (double)random() / (double)RAND_MAX;
  return round(i32MinSupport + (i32MaxSupport - i32MinSupport) * f64U);
}

double Randomizer::sampleNormal(double f64Mean, double f64Variance) const
  throw (OutOfBoundException) {
  if (f64Variance <= 0)
    throw OutOfBoundException("Randomizer::sampleNormal(): f64Variance must be greater than 0");
  double f64U, f64V, f64S;
  do {
    f64U = 2.0 * sampleUniform() - 1.0;
    f64V = 2.0 * sampleUniform() - 1.0;
    f64S = f64U * f64U + f64V * f64V;
  }
  while (f64S >= 1.0 || f64S == 0.0);
  return f64U * sqrt(-2.0 * log(f64S) / f64S) * sqrt(f64Variance) + f64Mean;
}

const Eigen::VectorXd Randomizer::sampleNormal(const Eigen::VectorXd&
  meanVector, const Eigen::MatrixXd& covarianceMatrix) const
  throw (OutOfBoundException) {
  if (meanVector.rows() < 2 || meanVector.rows() != covarianceMatrix.rows())
    throw OutOfBoundException("Randomizer::sampleNormal(): wrong dimensions for mean or covariance");
  if (covarianceMatrix.transpose() != covarianceMatrix)
    throw OutOfBoundException("Randomizer::sampleNormal(): covariance must be symmetric");
  if (covarianceMatrix.llt().isPositiveDefinite() == false)
    throw OutOfBoundException("Randomizer::sampleNormal(): covariance must be positive definite");
  if ((covarianceMatrix.diagonal().cwise() < 0).any() == true)
    throw OutOfBoundException("Randomizer::sampleNormal(): variances must be positive");
  Eigen::VectorXd sampleVector(meanVector.rows());
  for (uint32_t i = 0; i < (uint32_t)meanVector.rows(); i++)
    sampleVector(i) = sampleNormal(meanVector(i), covarianceMatrix(i, i));
  return meanVector + covarianceMatrix.llt().matrixL() * sampleVector;
}

const Eigen::VectorXd Randomizer::sampleNormal(const MvNormalDistribution& dist)
  const {
  Eigen::VectorXd sampleVector(dist.getMean().rows());
  for (uint32_t i = 0; i < (uint32_t)dist.getMean().rows(); i++)
    sampleVector(i) = sampleNormal(dist.getMean()(i),
      dist.getCovariance()(i, i));
  return dist.getMean() + dist.getTransformation().matrixL() * sampleVector;
}

bool Randomizer::sampleBernoulli(double f64P) const
  throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("Randomizer::sampleBernoulli(): f64P must be between 0 and 1");
  if (sampleUniform() >= 1.0 - f64P)
    return true;
  else
    return false;
}

uint32_t Randomizer::sampleCategorical(const Eigen::VectorXd&
  eventProbabilitiesVector) const throw (OutOfBoundException) {
  if (fabs(eventProbabilitiesVector.sum() - 1.0) >
    std::numeric_limits<double>::epsilon() ||
    (eventProbabilitiesVector.cwise() < 0).any() == true)
    throw OutOfBoundException("Randomizer::sampleCategorical(): event probabilities must sum to 1 and probabilities bigger or equal to 0");
  Eigen::VectorXd cumProbVector =
    Eigen::VectorXd::Zero(eventProbabilitiesVector.rows() + 1);
  double f64Sum = 0.0;
  for (uint32_t i = 1; i < (uint32_t)eventProbabilitiesVector.rows() + 1; i++) {
    f64Sum += eventProbabilitiesVector(i);
    cumProbVector(i) += f64Sum;
  }
  double f64U = sampleUniform();
  for (uint32_t i = 1; i < (uint32_t)eventProbabilitiesVector.rows() + 1; i++) {
    if (f64U > cumProbVector(i - 1) && f64U <= cumProbVector(i))
      return i - 1;
  }
  return eventProbabilitiesVector.rows() - 1;
}

uint32_t Randomizer::samplePoisson(double f64Lambda) const
  throw (OutOfBoundException) {
  if (f64Lambda <= 0)
    throw OutOfBoundException("Randomizer::samplePoisson(): f64Lambda must be strictly positive");
  double f64L = exp(-f64Lambda);
  uint32_t u32K = 0;
  double f64P = 1.0;
  do {
    u32K++;
    f64P *= sampleUniform();
  }
  while (f64P > f64L);
  return u32K - 1;
}

double Randomizer::sampleExponential(double f64Lambda) const
  throw (OutOfBoundException) {
  if (f64Lambda <= 0)
    throw OutOfBoundException("Randomizer::sampleExponential(): f64Lambda must be strictly positive");
  double f64U;
  do {
    f64U = sampleUniform();
  }
  while (f64U == 0);
  return -log(f64U) / f64Lambda;
}

uint32_t Randomizer::sampleGeometric(double f64P) const
  throw (OutOfBoundException) {
  if (f64P < 0.0 || f64P > 1.0)
    throw OutOfBoundException("Randomizer::sampleExponential(): f64P must be between 0 and 1");
  double f64U;
  do {
    f64U = sampleUniform();
  }
  while (f64U == 0);
  return floor(log(f64U) / log(1 - f64P));
}

double Randomizer::sampleGamma(double f64K, double f64Theta) const
  throw (OutOfBoundException) {
  if (f64K <= 0)
    throw OutOfBoundException("Randomizer::sampleGamma(): f64K must be strictly positive");
  if (f64Theta <= 0)
    throw OutOfBoundException("Randomizer::sampleGamma(): f64Beta must be strictly positive");
  uint32_t u32IntegralPart = floor(f64K);
  double f64FractionalPart = f64K - u32IntegralPart;
  double f64Y = 0;
  for (uint32_t i = 0; i < u32IntegralPart; i++)
    f64Y += sampleExponential(f64Theta);
  double f64B = (M_E + f64FractionalPart) / M_E;
  double f64Z = 0;
  if (fabs(f64FractionalPart - 0) > std::numeric_limits<double>::epsilon())
    while (true) {
      double f64P = f64B * sampleUniform();
      if (f64P > 1) {
        f64Z = pow(f64P, 1.0 / f64FractionalPart);
        if (sampleUniform() > exp(-f64Z))
          continue;
        else
          break;
      }
      else {
        f64Z = -log((f64B - f64P) / f64FractionalPart);
        if (sampleUniform() > pow(f64Z, f64FractionalPart - 1))
          continue;
        else
          break;
      }
    }
  return f64Y + f64Z / f64Theta;
}

double Randomizer::sampleBeta(double f64Alpha, double f64Beta) const
  throw (OutOfBoundException) {
  if (f64Alpha <= 0)
    throw OutOfBoundException("Randomizer::sampleBeta(): f64Alpha must be strictly positive");
  if (f64Beta <= 0)
    throw OutOfBoundException("Randomizer::sampleBeta(): f64Beta must be strictly positive");
  double f64X = sampleGamma(f64Alpha, 1);
  double f64Y = sampleGamma(f64Beta, 1);
  return f64X / (f64X + f64Y);
}
