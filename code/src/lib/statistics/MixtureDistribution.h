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
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"

#include <vector>

/** The MixtureDistribution class represents an interface to any kind of mixture
    distributions.
    \brief Mixture distribution
  */
template <typename D, size_t M> class MixtureDistribution :
  public D::DistributionType,
  public virtual Serializable {
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
  /// Constructs mixture from parameters
  MixtureDistribution(const std::vector<D>& compDistributions, const
    CategoricalDistribution<M> assignDistribution);
  /// Copy constructor
  MixtureDistribution(const MixtureDistribution& other);
  /// Assignment operator
  MixtureDistribution& operator = (const MixtureDistribution& other);
  /// Destructor
  virtual ~MixtureDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the components distributions
  const std::vector<D>& getCompDistributions() const;
  /// Sets the components distributions
  void setCompDistributions(const std::vector<D>& distributions)
    throw (BadArgumentException<size_t>);
  /// Returns the assignments distribution
  const CategoricalDistribution<M>& getAssignDistribution() const;
  /// Sets the assignments distribution
  void setAssignDistribution(const CategoricalDistribution<M>& distribution);
  /// Returns the probability density function at the given value
  virtual double pdf(const VariableType& value) const;
  /// Returns the probability mass function at the given value
  virtual double pmf(const VariableType& value) const;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Distributions of the components
  std::vector<D> mCompDistributions;
  /// Distribution of the assignments
  CategoricalDistribution<M> mAssignDistribution;
  /** @}
    */

};

#include "statistics/MixtureDistribution.tpp"

#endif // MIXTUREDISTRIBUTION_H
