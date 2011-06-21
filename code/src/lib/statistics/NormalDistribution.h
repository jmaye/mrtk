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

/** \file NormalDistribution.h
    \brief NormalDistribution
  */

#ifndef NORMALDISTRIBUTION_H
#define NORMALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <iosfwd>

/** NormalDistribution
  */
class NormalDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const NormalDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    NormalDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const NormalDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    NormalDistribution& obj);

  /** Copy constructor
    */
  NormalDistribution(const NormalDistribution& other);

  /** Assignment operator
    */
  NormalDistribution& operator = (const NormalDistribution& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Mean;
  double mf64Variance;
  double mf64Precision;
  double mf64StandardDeviation;
  double mf64Normalizer;

public:
  /** Constructors
    */
  NormalDistribution(double f64Mean = 0.0, double f64Variance = 1.0);

  /** Destructor
    */
  ~NormalDistribution();

  /** Accessors
    */
  void setMean(double f64Mean);
  double getMean() const;
  void setVariance(double f64Variance) throw (OutOfBoundException);
  double getVariance() const;
  double getPrecision() const;
  double getStandardDeviation() const;
  double getNormalizer() const;

  /** Methods
    */
  double pdf(double f64X) const;
  double logpdf(double f64X) const;
  double sample() const;
  double KLDivergence(const NormalDistribution& other) const;
  double mahalanobisDistance(double f64Value) const;

protected:

};

#endif // NORMALDISTRIBUTION_H
