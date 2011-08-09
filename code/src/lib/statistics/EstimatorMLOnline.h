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

/** \file EstimatorMLOnline.h
    \brief This file defines the EstimatorMLOnline class, which implements
           online maximum likelihood estimators for various distributions
  */

#ifndef ESTIMATORMLONLINE_H
#define ESTIMATORMLONLINE_H

#include "statistics/NormalDistribution.h"
#include "statistics/CategoricalDistribution.h"
#include "statistics/MultinomialDistribution.h"
#include "statistics/ExponentialDistribution.h"
#include "statistics/GeometricDistribution.h"
#include "statistics/PoissonDistribution.h"
#include "base/Serializable.h"

template <typename D, size_t M = 1> class EstimatorMLOnline;

/** The class EstimatorMLOnline is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution ML estimator
  */
template <> class EstimatorMLOnline<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<NormalDistribution<1> >& other);
  /// Assignment operator
  EstimatorMLOnline<NormalDistribution<1> >& operator =
    (const EstimatorMLOnline<NormalDistribution<1> >& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(NormalDistribution<1>& dist, const
    NormalDistribution<1>::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for multivariate normal
    distributions.
    \brief Multivariate normal distribution ML estimator
  */
template <size_t M> class EstimatorMLOnline<NormalDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<NormalDistribution<M>, M>& other);
  /// Assignment operator
  EstimatorMLOnline<NormalDistribution<M>, M>& operator =
    (const EstimatorMLOnline<NormalDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(NormalDistribution<M>& dist, const typename
    NormalDistribution<M>::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for categorical distributions.
    \brief Categorical distribution ML estimator
  */
template <size_t M> class EstimatorMLOnline<CategoricalDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<CategoricalDistribution<M>, M>&
    other);
  /// Assignment operator
  EstimatorMLOnline<CategoricalDistribution<M>, M>& operator =
    (const EstimatorMLOnline<CategoricalDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(CategoricalDistribution<M>& dist, const
    Eigen::Matrix<size_t, M, 1>& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for multinomial distributions.
    \brief Multinomial distribution ML estimator
  */
template <size_t M> class EstimatorMLOnline<MultinomialDistribution<M>, M> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<MultinomialDistribution<M>, M>&
    other);
  /// Assignment operator
  EstimatorMLOnline<MultinomialDistribution<M>, M>& operator =
    (const EstimatorMLOnline<MultinomialDistribution<M>, M>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(MultinomialDistribution<M>& dist, const
    Eigen::Matrix<size_t, M, 1>& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for exponential distributions.
    \brief Exponential distribution ML estimator
  */
template <> class EstimatorMLOnline<ExponentialDistribution> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<ExponentialDistribution>& other);
  /// Assignment operator
  EstimatorMLOnline<ExponentialDistribution>& operator =
    (const EstimatorMLOnline<ExponentialDistribution>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(ExponentialDistribution& dist, const
    ExponentialDistribution::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for geometric distributions.
    \brief Geometric distribution ML estimator
  */
template <> class EstimatorMLOnline<GeometricDistribution> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<GeometricDistribution>& other);
  /// Assignment operator
  EstimatorMLOnline<GeometricDistribution>& operator =
    (const EstimatorMLOnline<GeometricDistribution>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(GeometricDistribution& dist, const
    GeometricDistribution::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

/** The class EstimatorMLOnline is implemented for Poisson distributions.
    \brief Poisson distribution ML estimator
  */
template <> class EstimatorMLOnline<PoissonDistribution> :
  public virtual Serializable {
public:
  /** \name Private constructors
    @{
    */
  /// Default constructor
  EstimatorMLOnline();
  /// Copy constructor
  EstimatorMLOnline(const EstimatorMLOnline<PoissonDistribution>& other);
  /// Assignment operator
  EstimatorMLOnline<PoissonDistribution>& operator =
    (const EstimatorMLOnline<PoissonDistribution>& other);
  /// Destructor
  virtual ~EstimatorMLOnline();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Sets the number of points
  void setNumPoints(size_t numPoints);
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Add a point to the estimator and estimate the distribution
  void addPoint(PoissonDistribution& dist, const
    PoissonDistribution::VariableType& point);
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
  /// Number of points in the estimator
  size_t mNumPoints;
  /** @}
    */

};

#include "statistics/EstimatorMLOnline.tpp"

#endif // ESTIMATORMLONLINE
