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

/** \file UniformDistributionDiscrete.h
    \brief UniformDistributionDiscrete
  */

#ifndef UNIFORMDISTRIBUTIONDISCRETE_H
#define UNIFORMDISTRIBUTIONDISCRETE_H

#include "exceptions/OutOfBoundException.h"
#include "exceptions/InvalidOperationException.h"

#include <iosfwd>

#include <stdint.h>

/** UniformDistributionDiscrete
  */
class UniformDistributionDiscrete {
  friend std::ostream& operator << (std::ostream& stream,
    const UniformDistributionDiscrete& obj);
  friend std::istream& operator >> (std::istream& stream,
    UniformDistributionDiscrete& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const UniformDistributionDiscrete& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    UniformDistributionDiscrete& obj);

  /** Copy constructor
    */
  UniformDistributionDiscrete(const UniformDistributionDiscrete& other);

  /** Assignment operator
    */
  UniformDistributionDiscrete& operator = (const UniformDistributionDiscrete&
    other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  int32_t mi32MinSupport;
  int32_t mi32MaxSupport;

public:
  /** Constructors
    */
  UniformDistributionDiscrete(int32_t i32MinSupport = 0,
    int32_t i32MaxSupport = 1) throw (OutOfBoundException);

  /** Destructor
    */
  ~UniformDistributionDiscrete();

  /** Accessors
    */
  void setMinSupport(int32_t i32Value) throw (OutOfBoundException);
  int32_t getMinSupport() const;
  void setMaxSupport(int32_t i32Value) throw (OutOfBoundException);
  int32_t getMaxSupport() const;

  /** Methods
    */
  double pdf(int32_t i32X) const;
  double logpdf(int32_t i32X) const throw (InvalidOperationException);
  double sample() const;

protected:

};

#endif // UNIFORMDISTRIBUTIONDISCRETE_H
