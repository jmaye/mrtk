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

/** \file UniformDistribution1v.h
    \brief This file contains an interface to the univariate uniform
           distributions
  */

#include "statistics/ContinuousDistribution.h"
#include "statistics/DiscreteDistribution.h"
#include "statistics/SampleDistribution.h"
#include "base/Serializable.h"
#include "exceptions/BadArgumentException.h"
#include "utils/IfThenElse.h"
#include "utils/IsReal.h"
#include "utils/IsInteger.h"

/** The UniformDistribution1v class represents an interface to the univariate
    uniform distributions.
    \brief Univariate uniform distribution
  */
template <typename X> class UniformDistribution<X> :
  public IfThenElse<typename IsReal<X>::Result,
    ContinuousDistribution<X>, DiscreteDistribution<X> >::Result,
  public SampleDistribution<X>,
  public virtual Serializable {
public:
  /** \name Traits
    @{
    */
  /// Specialization for integer or real types
  struct Traits {
  public:
    /// Get support area for real types
    template <typename Z, typename IsReal<Z>::Result::Numeric>
      static Z getSupportArea(const Z& minSupport, const Z& maxSupport);
    /// Get support area for integer types
    template <typename Z, typename IsInteger<Z>::Result::Numeric>
      static Z getSupportArea(const Z& minSupport, const Z& maxSupport);
    /// Get variance for real types
    template <typename Z, typename IsReal<Z>::Result::Numeric>
      static double getVariance(const Z& minSupport, const Z& maxSupport);
    /// Get variance for integer types
    template <typename Z, typename IsInteger<Z>::Result::Numeric>
      static double getVariance(const Z& minSupport, const Z& maxSupport);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  UniformDistribution(const X& minSupport = X(0), const X& maxSupport = X(1));
  /// Copy constructor
  UniformDistribution(const UniformDistribution<X>& other);
  /// Assignment operator
  UniformDistribution& operator = (const UniformDistribution<X>& other);
  /// Destructor
  virtual ~UniformDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the support of the distribution
  void setSupport(const X& minSupport, const X& maxSupport)
    throw (BadArgumentException<X>);
  /// Sets the minimum support
  void setMinSupport(const X& minSupport);
  /// Returns the minimum support
  const X& getMinSupport() const;
  /// Sets the maximum support
  void setMaxSupport(const X& maxSupport);
  /// Returns the maximum support
  const X& getMaxSupport() const;
  /// Returns the support area
  const X& getSupportArea() const;
  /// Returns the mean of the distribution
  double getMean() const;
  /// Returns the median of the distribution
  double getMedian() const;
  /// Returns the mode of the distribution
  double getMode() const;
  /// Returns the variance of the distribution
  double getVariance() const;
  /// Access the probablity density function at the given value
  virtual double pdf(const X& value) const;
  /// Access the probablity mass function at the given value
  virtual double pmf(const X& value) const;
  /// Access a sample drawn from the distribution
  virtual X getSample() const;
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
  /// Minimum support of the distribution
  X mMinSupport;
  /// Maximum support of the distribution
  X mMaxSupport;
  /// Support area
  X mSupportArea;
  /** @}
    */

};

#include "statistics/UniformDistribution1v.tpp"
