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

#include "statistics/ContinuousDistribution.h"
#include "statistics/SampleDistribution.h"
#include "exceptions/BadArgumentException.h"

#include <iosfwd>

/** The DirichletDistribution class represents a Dirichlet distribution,
    i.e., a continuous distribution that is a conjugate prior to the multinomial
    or categorical distribution
    \brief Dirichlet distribution
  */
template <size_t M> class DirichletDistribution :
  public ContinuousDistribution<double, M>,
  public SampleDistribution<Eigen::Matrix<double, M, 1> > {
  template <size_t N>
  friend std::ostream& operator << (std::ostream& stream,
    const DirichletDistribution<N>& obj);
  template <size_t N>
  friend std::istream& operator >> (std::istream& stream,
    DirichletDistribution<N>& obj);
  template <size_t N>
  friend std::ofstream& operator << (std::ofstream& stream,
    const DirichletDistribution<N>& obj);
  template <size_t N>
  friend std::ifstream& operator >> (std::ifstream& stream,
    DirichletDistribution<N>& obj);

  /** \name Stream methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  DirichletDistribution(const Eigen::Matrix<double, M, 1>& alphaVector);
  /// Copy constructor
  DirichletDistribution(const DirichletDistribution<M>& other);
  //// Assignment operator
  DirichletDistribution& operator = (const DirichletDistribution<M>& other);
  /// Destructor
  virtual ~DirichletDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of successes
  void setAlpha(const Eigen::Matrix<double, M, 1>& alphaVector)
    throw (BadArgumentException<Eigen::Matrix<double, M, 1> >);
  /// Returns the number of successes
  const Eigen::Matrix<double, M, 1>& getAlpha() const;
  /// Returns the normalizer
  double getNormalizer() const;
  /// Access the probability density function at the given value
  virtual double pdf(const Eigen::Matrix<double, M, 1>& value) const;
  /// Access the log-probablity density function at the given value
  double logpdf(const Eigen::Matrix<double, M, 1>& value) const
    throw (BadArgumentException<Eigen::Matrix<double, M, 1> >);
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<double, M, 1> getSample() const;
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Pseudo-counts
  Eigen::Matrix<double, M, 1> mAlphaVector;
  /// Normalizer
  double mf64Normalizer;
  /** @}
    */

};

#include "statistics/DirichletDistribution.tpp"

#endif // DIRICHLETDISTRIBUTION_H
