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

/** \file Randomizer.h
    \brief Randomizer
  */

#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include "misc/Timestamp.h"
#include "exceptions/OutOfBoundException.h"
#include "statistics/MvNormalDistribution.h"

#include <Eigen/Core>

#include <iosfwd>

#include <stdint.h>

/** This class implements a random sampler for different kind of distributions.
  */
class Randomizer {
  friend std::ostream& operator << (std::ostream& stream,
    const Randomizer& obj);
  friend std::istream& operator >> (std::istream& stream, Randomizer& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Randomizer& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Randomizer& obj);

  /** Copy constructor
    */
  Randomizer(const Randomizer& other);

  /** Assignment operator
    */
  Randomizer& operator = (const Randomizer& other);

  /** Stream methods
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  double mf64Seed;

public:
  /** Constructors
    */
  Randomizer(double f64Seed = Timestamp::now());

  /** Destructor
    */
  ~Randomizer();

  /** Accessors
    */
  void setSeed(double f64Seed);
  double getSeed() const;

  /** Methods
    */
  double sampleUniform(double f64MinSupport = 0.0, double f64MaxSupport = 1.0)
    const throw (OutOfBoundException);
  int32_t sampleUniform(int32_t i32MinSupport, int32_t i32MaxSupport)
    const throw (OutOfBoundException);
  double sampleNormal(double f64Mean = 0.0, double f64Variance = 1.0) const
    throw (OutOfBoundException);
  const Eigen::VectorXd sampleNormal(const Eigen::VectorXd& meanVector,
    const Eigen::MatrixXd& covarianceMatrix) const
    throw (OutOfBoundException);
  const Eigen::VectorXd sampleNormal(const MvNormalDistribution& dist) const;

protected:

};

#endif // RANDOMIZER_H
