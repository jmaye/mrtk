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

/** \file UniformDistributionMv.h
    \brief This file contains an interface to the multivariate uniform
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

/** The UniformDistributionMv class represents an interface to the multivariate
    uniform distributions.
    \brief Multivariate uniform distribution
  */
template <typename X, size_t M> class UniformDistribution:
  public IfThenElse<typename IsReal<X>::Result,
    ContinuousDistribution<X, M>, DiscreteDistribution<X, M> >::Result,
  public SampleDistribution<Eigen::Matrix<X, M, 1> >,
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
      static Z getSupportArea(const Eigen::Matrix<Z, M, 1>& minSupport, const
        Eigen::Matrix<Z, M, 1>& maxSupport);
    /// Get support area for integer types
    template <typename Z, typename IsInteger<Z>::Result::Numeric>
      static Z getSupportArea(const Eigen::Matrix<Z, M, 1>& minSupport, const
        Eigen::Matrix<Z, M, 1>& maxSupport);
    /// Get covariance for real types
    template <typename Z, typename IsReal<Z>::Result::Numeric>
      static Eigen::Matrix<double, M, M> getCovariance(
        const Eigen::Matrix<Z, M, 1>& minSupport,
        const Eigen::Matrix<Z, M, 1>& maxSupport);
    /// Get covariance for integer types
    template <typename Z, typename IsInteger<Z>::Result::Numeric>
      static Eigen::Matrix<double, M, M> getCovariance(
        const Eigen::Matrix<Z, M, 1>& minSupport,
        const Eigen::Matrix<Z, M, 1>& maxSupport);
  };
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs distribution from parameters
  UniformDistribution(const Eigen::Matrix<X, M, 1>& minSupport =
    Eigen::Matrix<X, M, 1>::Zero(), const Eigen::Matrix<X, M, 1>&
    maxSupport = Eigen::Matrix<X, M, 1>::Ones());
  /// Copy constructor
  UniformDistribution(const UniformDistribution<X, M>& other);
  /// Assignment operator
  UniformDistribution& operator = (const UniformDistribution<X, M>& other);
  /// Destructor
  virtual ~UniformDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the support of the distribution
  void setSupport(const Eigen::Matrix<X, M, 1>& minSupport, const
    Eigen::Matrix<X, M, 1>& maxSupport)
    throw (BadArgumentException<Eigen::Matrix<X, M, 1> >);
  /// Sets the minimum support
  void setMinSupport(const Eigen::Matrix<X, M, 1>& minSupport);
  /// Returns the minimum support
  const Eigen::Matrix<X, M, 1>& getMinSupport() const;
  /// Sets the maximum support
  void setMaxSupport(const Eigen::Matrix<X, M, 1>& maxSupport);
  /// Returns the maximum support
  const Eigen::Matrix<X, M, 1>& getMaxSupport() const;
  /// Access the multivariate uniform distribution's support area
  const X& getSupportArea() const;
  /// Returns the mean of the distribution
  Eigen::Matrix<double, M, 1> getMean() const;
  /// Returns the median of the distribution
  Eigen::Matrix<double, M, 1> getMedian() const;
  /// Returns the mode of the distribution
  Eigen::Matrix<double, M, 1> getMode() const;
  /// Returns the variance of the distribution
  Eigen::Matrix<double, M, M> getCovariance() const;
  /// Access the probablity density function at the given value
  virtual double pdf(const Eigen::Matrix<X, M, 1>& value) const;
  /// Access the probablity mass function at the given value
  virtual double pmf(const Eigen::Matrix<X, M, 1>& value) const;
  /// Access a sample drawn from the distribution
  virtual Eigen::Matrix<X, M, 1> getSample() const;
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
  Eigen::Matrix<X, M, 1> mMinSupport;
  /// Maximum support of the distribution
  Eigen::Matrix<X, M, 1> mMaxSupport;
  /// Support area
  X mSupportArea;
  /** @}
    */

};

#include "statistics/UniformDistributionMv.tpp"
