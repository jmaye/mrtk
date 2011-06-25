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

/** \file DiscreteFunction1v.h
    \brief DiscreteFunction1v
  */

#ifndef DISCRETEFUNCTION1V_H
#define DISCRETEFUNCTION1V_H

#include <iosfwd>

/** DiscreteFunction1v
  */
class DiscreteFunction1v {
  friend std::ostream& operator << (std::ostream& stream, const DiscreteFunction1v& obj);
  friend std::istream& operator >> (std::istream& stream, DiscreteFunction1v& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const DiscreteFunction1v& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, DiscreteFunction1v& obj);

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  DiscreteFunction1v(const DiscreteFunction1v& other);

  //// Assignment operator
  DiscreteFunction1v& operator = (const DiscreteFunction1v& other);
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
  DiscreteFunction1v();
  /// Destructor
  ~DiscreteFunction1v();
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

#endif // DISCRETEFUNCTION1V_H
