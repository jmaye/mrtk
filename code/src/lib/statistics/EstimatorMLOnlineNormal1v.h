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

/** \file EstimatorMLOnlineNormal1v.h
    \brief This file implements an online ML estimator for univariate normal
           distributions.
  */

#ifndef ESTIMATORMLONLINENORMAL1V_H
#define ESTIMATORMLONLINENORMAL1V_H

#include "statistics/NormalDistribution.h"
#include "base/Serializable.h"

template <typename D, size_t M = 1> class EstimatorMLOnline;

/** The class EstimatorMLOnline is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution online ML estimator
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

#include "statistics/EstimatorMLOnlineNormal1v.tpp"

#endif // ESTIMATORMLONLINENORMAL1V
