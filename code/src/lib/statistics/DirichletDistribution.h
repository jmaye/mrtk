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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file DirichletDistribution.h
    \brief This file defines the DirichletDistribution class, which represents
           a Dirichlet distribution
  */

#ifndef DIRICHLETDISTRIBUTION_H
#define DIRICHLETDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <Eigen/Core>

#include <iosfwd>

/** The DirichletDistribution class represents a Dirichlet distribution,
    i.e., a continuous distribution that is a conjugate prior to the multinomial
    or categorical distribution
    \brief Dirichlet distribution
  */
class DirichletDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const DirichletDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    DirichletDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const DirichletDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    DirichletDistribution& obj);

  /** \name Stream methods
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
  /// Pseudo-counts
  Eigen::VectorXd mAlphaVector;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  DirichletDistribution(const Eigen::VectorXd& alphaVector);
  /// Copy constructor
  DirichletDistribution(const DirichletDistribution& other);
  //// Assignment operator
  DirichletDistribution& operator = (const DirichletDistribution& other);
  /// Destructor
  ~DirichletDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of successes
  void setAlpha(const Eigen::VectorXd& alphaVector) throw (OutOfBoundException);
  /// Returns the number of successes
  const Eigen::VectorXd& getAlpha() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns the probability density function at a point
  double pdf(const Eigen::VectorXd& xVector) const;
  /// Returns the log-probability density function at a point
  double logpdf(const Eigen::VectorXd& xVector) const throw (OutOfBoundException);
  /// Returns a sample from the distribution
  const Eigen::VectorXd sample() const;
  /** @}
    */

protected:

};

#endif // DIRICHLETDISTRIBUTION_H
