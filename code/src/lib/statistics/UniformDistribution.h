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

/** \file UniformDistribution.h
    \brief UniformDistribution
  */

#ifndef UNIFORMDISTRIBUTION_H
#define UNIFORMDISTRIBUTION_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <iosfwd>

/** UniformDistribution
  */
class UniformDistribution {
  friend std::ostream& operator << (std::ostream& stream,
    const UniformDistribution& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniformDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniformDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniformDistribution& obj);

  /** Copy constructor
    */
  UniformDistribution(const UniformDistribution& other);

  /** Assignment operator
    */
  UniformDistribution& operator = (const UniformDistribution& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64MinSupport;
  double mf64MaxSupport;

public:
  /** Constructors
    */
  UniformDistribution(double f64MinSupport = 0.0, double f64MaxSupport = 1.0)
    throw (OutOfBoundException);

  /** Destructor
    */
  ~UniformDistribution();

  /** Accessors
    */
  void setMinSupport(double f64Value) throw (OutOfBoundException);
  double getMinSupport() const;
  void setMaxSupport(double f64Value) throw (OutOfBoundException);
  double getMaxSupport() const;

  /** Methods
    */
  double pdf(double f64X) const;
  double logpdf(double f64X) const throw (InvalidOperationException);
  double sample() const;

protected:

};

#endif // UNIFORMDISTRIBUTION_H
