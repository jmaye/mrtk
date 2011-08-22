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

/** \file EstimatorBayesNormal1v.h
    \brief This file implements a Bayesian estimator for univariate normal
           distributions.
  */

#include "statistics/NormalDistribution.h"
#include "statistics/GammaDistribution.h"

#include <vector>

/** The class EstimatorBayes is implemented for univariate normal
    distributions.
    \brief Univariate normal distribution Bayesian estimator
  */
template <> class EstimatorBayes<NormalDistribution<1> > :
  public virtual Serializable {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  EstimatorBayes(const NormalDistribution<1>& meanPrior =
    NormalDistribution<1>(), const GammaDistribution<double>& variancePrior =
    GammaDistribution<double>());
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<NormalDistribution<1> >& other);
  /// Assignment operator
  EstimatorBayes<NormalDistribution<1> >& operator =
    (const EstimatorBayes<NormalDistribution<1> >& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the number of points
  size_t getNumPoints() const;
  /// Returns the validity state of the estimator
  bool getValid() const;
  /// Add a point to the estimator
  void addPoint(double point);
  /// Add points to the estimator
  void addPoints(const std::vector<double>& points);
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
  /// Mean posterior
  NormalDistribution<1> mMeanPosterior;
  /// Variance posterior
  GammaDistribution<double> mVariancePosterior;
  /// Number of points in the estimator
  size_t mNumPoints;
  /// Valid flag
  bool mValid;
  /** @}
    */

};

#include "statistics/EstimatorBayesNormal1v.tpp"
