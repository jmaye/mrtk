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
    \brief This file defines the MvNormalDistribution class, which represents a
           multivariate normal distribution
  */

#ifndef MVNORMALDISTRIBUTION_H
#define MVNORMALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <Eigen/Core>
#include <Eigen/Cholesky>

#include <iosfwd>

/** The MvNormalDistribution class represents a multivariate normal
    distribution.
    \brief Multivariate normal distribution
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

  /** \name Streaming methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private members
    @{
    */
  /// Mean of the normal distribution
  Eigen::VectorXd mMeanVector;
  /// Covariance matrix of the normal distribution
  Eigen::MatrixXd mCovarianceMatrix;
  /// Precision matrix of the normal distribution
  Eigen::MatrixXd mPrecisionMatrix;
  /// Determinant of the covariance matrix
  double mf64Determinant;
  /// Normalizer of the distribution
  double mf64Normalizer;
  /// Cholesky decomposition of the covariance matrix
  Eigen::LLT<Eigen::MatrixXd> mTransformation;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the distribution from the parameters
  MvNormalDistribution(const Eigen::VectorXd& meanVector,
    const Eigen::MatrixXd& covarianceMatrix) throw (OutOfBoundException);
  /// Copy constructor
  MvNormalDistribution(const MvNormalDistribution& other);
  /// Assignment operator
  MvNormalDistribution& operator = (const MvNormalDistribution& other);
  /// Destructor
  ~MvNormalDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the mean of the distribution
  void setMean(const Eigen::VectorXd& meanVector)
    throw (OutOfBoundException);
  /// Returns the mean of the distribution
  const Eigen::VectorXd& getMean() const;
  /// Sets the covariance matrix of the distribution
  void setCovariance(const Eigen::MatrixXd& covarianceMatrix)
    throw (OutOfBoundException);
  /// Returns the covariance matrix of the distribution
  const Eigen::MatrixXd& getCovariance() const;
  /// Returns the precision matrix of the distribution
  const Eigen::MatrixXd& getPrecision() const;
  /// Returns the determinant of the covariance matrix
  double getDeterminant() const;
  /// Returns the normalizer of the distribution
  double getNormalizer() const;
  /// Returns the cholesky decomposition of the covariance matrix
  const Eigen::LLT<Eigen::MatrixXd>& getTransformation() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability density at a point
  double pdf(const Eigen::VectorXd& xVector) const throw (OutOfBoundException);
  /// Returns a sample of the distribution
  const Eigen::VectorXd sample() const;
  /// Returns the KL-divergence with another distribution
  double KLDivergence(const MvNormalDistribution& other) const
    throw (OutOfBoundException);
  /// Returns the Mahalanobis distance from a point
  double mahalanobisDistance(const Eigen::VectorXd& xVector) const
    throw (OutOfBoundException);
  /** @}
    */

protected:

};

#include "statistics/MvNormalDistribution.tpp"

#endif // MVNORMALDISTRIBUTION_H
