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

/** \file MvContinuousDistribution.h
    \brief MvContinuousDistribution
  */

#ifndef MVCONTINUOUSDISTRIBUTION_H
#define MVCONTINUOUSDISTRIBUTION_H

#include <iosfwd>

/** MvContinuousDistribution
  */
class MvContinuousDistribution {
  friend std::ostream& operator << (std::ostream& stream, const MvContinuousDistribution& obj);
  friend std::istream& operator >> (std::istream& stream, MvContinuousDistribution& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const MvContinuousDistribution& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, MvContinuousDistribution& obj);

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  MvContinuousDistribution(const MvContinuousDistribution& other);

  //// Assignment operator
  MvContinuousDistribution& operator = (const MvContinuousDistribution& other);
  /** @}
    */

  /** \name Stream methods
    @{
    */
  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;
  /** @}
    */

  /** \name Private methods
    @{
    */

  /** @}
    */

  /** \name Private members
    @{
    */

  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  MvContinuousDistribution();
  /// Destructor
  ~MvContinuousDistribution();
  /** @}
    */

  /** \name Accessors
    @{
    */

  /** @}
    */

  /** \name Methods
    @{
    */

  /** @}
    */

protected:

};

#endif // MVCONTINUOUSDISTRIBUTION_H
