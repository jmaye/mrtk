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

/** \file MvNormalDistribution.h
    \brief MvNormalDistribution
  */

#ifndef MVNORMALDISTRIBUTION_H
#define MVNORMALDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"

#include <vector>
#include <iosfwd>

/** MvNormalDistribution
  */
class MvNormalDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const MvNormalDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    MvNormalDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const MvNormalDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    MvNormalDistribution& obj);

  /** Copy constructor
    */
  MvNormalDistribution(const MvNormalDistribution& other);

  /** Assignment operator
    */
  MvNormalDistribution& operator = (const MvNormalDistribution& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::vector<double> mMeanVector;
  std::vector<std::vector<double> > mCovarianceMatrix;

public:
  /** Constructors
    */
  MvNormalDistribution(const std::vector<double>& meanVector,
    const std::vector<std::vector<double> >& covarianceMatrix)
    throw (OutOfBoundException);

  /** Destructor
    */
  ~MvNormalDistribution();

  /** Accessors
    */
  void setMean(const std::vector<double>& meanVector)
    throw (OutOfBoundException);
  const std::vector<double>& getMean() const;
  void setCovariance(const std::vector<std::vector<double> >& covarianceMatrix)
    throw (OutOfBoundException);
  const std::vector<std::vector<double> >& getCovariance() const;

  /** Methods
    */
  double pdf(const std::vector<double>& xVector) const
    throw (OutOfBoundException);
  const std::vector<double>& sample() const;
  double KLDivergence(const MvNormalDistribution& other) const
    throw (OutOfBoundException);

protected:

};

#endif // MVNORMALDISTRIBUTION_H
