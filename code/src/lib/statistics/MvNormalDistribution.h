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

/** \file MvNormalDistribution.h
    \brief MvNormalDistribution
  */

#ifndef MVNORMALDISTRIBUTION_H
#define MVNORMALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <Eigen/Core>
#include <Eigen/Cholesky>

#include <iosfwd>

/** This class represents a multivariate normal distribution.
  */
class MvNormalDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const MvNormalDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    MvNormalDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MvNormalDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    MvNormalDistribution& obj);

  /** Copy constructor
    */
  MvNormalDistribution(const MvNormalDistribution& other);

  /** Assignment operator
    */
  MvNormalDistribution& operator = (const MvNormalDistribution& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  Eigen::VectorXd mMeanVector;
  Eigen::MatrixXd mCovarianceMatrix;
  Eigen::MatrixXd mPrecisionMatrix;
  double mf64Determinant;
  double mf64Normalizer;
  Eigen::LLT<Eigen::MatrixXd> mTransformation;

public:
  /** Constructors
    */
  MvNormalDistribution(const Eigen::VectorXd& meanVector,
    const Eigen::MatrixXd& covarianceMatrix) throw (OutOfBoundException);

  /** Destructor
    */
  ~MvNormalDistribution();

  /** Accessors
    */
  void setMean(const Eigen::VectorXd& meanVector)
    throw (OutOfBoundException);
  const Eigen::VectorXd& getMean() const;
  void setCovariance(const Eigen::MatrixXd& covarianceMatrix)
    throw (OutOfBoundException);
  const Eigen::MatrixXd& getCovariance() const;
  const Eigen::MatrixXd& getPrecision() const;
  double getDeterminant() const;
  double getNormalizer() const;
  const Eigen::LLT<Eigen::MatrixXd>& getTransformation() const;

  /** Methods
    */
  double pdf(const Eigen::VectorXd& xVector) const throw (OutOfBoundException);
  const Eigen::VectorXd sample() const;
  double KLDivergence(const MvNormalDistribution& other) const
    throw (OutOfBoundException);
  double mahalanobisDistance(const Eigen::VectorXd& xVector) const
    throw (OutOfBoundException);

protected:

};

#endif // MVNORMALDISTRIBUTION_H
