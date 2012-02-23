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

/** \file EstimatorBayesPoisson.h
    \brief This file implements a Bayesian estimator for Poisson distributions
           with conjugate prior
  */

#include <vector>

#include "statistics/PoissonDistribution.h"
#include "statistics/GammaDistribution.h"
#include "statistics/NegativeBinomialDistribution.h"

/** The class EstimatorBayes is implemented for Poisson distributions with
    conjugate prior.
    \brief Poisson distribution Bayesian estimator
  */
template <> class EstimatorBayes<PoissonDistribution> :
  public virtual Serializable {
public:
  /** \name Types definitions
    @{
    */
  /// Point type
  typedef size_t Point;
  /// Points container
  typedef std::vector<Point> Container;
  /// Constant point iterator
  typedef Container::const_iterator ConstPointIterator;
  /** @}
    */

  /** \name Constructors/destructor
    @{
    */
  /// Constructs estimator with hyperparameters prior
  EstimatorBayes(double alpha = 1.0, double beta = 1.0);
  /// Copy constructor
  EstimatorBayes(const EstimatorBayes<PoissonDistribution>& other);
  /// Assignment operator
  EstimatorBayes<PoissonDistribution>& operator =
    (const EstimatorBayes<PoissonDistribution>& other);
  /// Destructor
  virtual ~EstimatorBayes();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the posterior mean distribution
  const GammaDistribution<double>& getPostMeanDist() const;
  /// Returns the posterior predictive distribution
  const NegativeBinomialDistribution& getPostPredDist() const;
  /// Add a point to the estimator
  void addPoint(const Point& point);
  /// Add points to the estimator
  void addPoints(const ConstPointIterator& itStart, const ConstPointIterator&
    itEnd);
  /// Add points to the estimator
  void addPoints(const Container& points);
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
  /// Posterior mean distribution
  GammaDistribution<double> mPostMeanDist;
  /// Posterior predictive distribution
  NegativeBinomialDistribution mPostPredDist;
  /// Hyperparameter alpha (alpha - 1 prior counts)
  double mAlpha;
  /// Hyperparameter beta (beta prior observations)
  double mBeta;
  /** @}
    */

};

#include "statistics/EstimatorBayesPoisson.tpp"
