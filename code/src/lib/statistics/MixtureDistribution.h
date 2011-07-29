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

/** \file MixtureDistribution.h
    \brief This file contains an interface to any kind of mixture distributions
  */

#ifndef MIXTUREDISTRIBUTION_H
#define MIXTUREDISTRIBUTION_H

#include "statistics/Distribution.h"
#include "statistics/CategoricalDistribution.h"

#include <vector>

/** The MixtureDistribution class represents an interface to any kind of mixture
    distributions.
    \brief Mixture distribution
  */
template <typename D, size_t M> class MixtureDistribution :
  public D::DistributionType {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MixtureDistribution(const MixtureDistribution& other);
  /// Assignment operator
  MixtureDistribution& operator = (const MixtureDistribution& other);
  /** @}
    */

public:
  /** \name Types
    @{
    */
  /// Variable type
  typedef typename D::VariableType VariableType;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MixtureDistribution();
  /// Destructor
  virtual ~MixtureDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the probability density function at the given value
  virtual double pdf(const VariableType& value) const;
  /// Returns the probability mass function at the given value
  virtual double pmf(const VariableType& value) const;
  /** @}
    */

protected:
  std::vector<D> mDistributions;
  CategoricalDistribution<M> mWeights;

};

#include "statistics/MixtureDistribution.tpp"

#endif // MIXTUREDISTRIBUTION_H
