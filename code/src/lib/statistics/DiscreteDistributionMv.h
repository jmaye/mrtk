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

/** \file DiscreteDistributionMv.h
    \brief This file contains an interface to the multivariate discrete
           distributions
  */

#ifndef DISCRETEDISTRIBUTIONMV_H
#define DISCRETEDISTRIBUTIONMV_H

#include "functions/ContinuousFunctionMv.h"
#include "statistics/Distribution.h"

/** The DiscreteDistributionMv class represents an interface to the
    multivariate discrete distributions
    \brief Multivariate discrete distribution
  */
template <typename X, size_t M> class DiscreteDistribution :
  public DiscreteFunction<double, X, M>,
  public Distribution<Eigen::Matrix<X, M, 1> > {
public:
  /** \name Types
    @{
    */
  typedef DiscreteDistribution<X, M> DistributionType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  DiscreteDistribution();
  /// Destructor
  virtual ~DiscreteDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Access the probablity of the variable to take on the given value
  virtual double pmf(const Eigen::Matrix<X, M, 1>& value) const = 0;
  /// Interface to function
  virtual double getValue(const Eigen::Matrix<X, M, 1>& argument) const;
  /** @}
    */

protected:

};

#include "statistics/DiscreteDistributionMv.tpp"

#endif // DISCRETEDISTRIBUTIONMV_H
