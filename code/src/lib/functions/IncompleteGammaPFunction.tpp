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

#include <gsl/gsl_sf_gamma.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IncompleteGammaPFunction::IncompleteGammaPFunction(double alpha) :
    mAlpha(alpha) {
}

IncompleteGammaPFunction::IncompleteGammaPFunction(const
    IncompleteGammaPFunction& other) :
    mAlpha(other.mAlpha) {
}

IncompleteGammaPFunction& IncompleteGammaPFunction::operator = (const
    IncompleteGammaPFunction& other) {
  if (this != &other) {
    mAlpha = other.mAlpha;
  }
  return *this;
}

IncompleteGammaPFunction::~IncompleteGammaPFunction() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void IncompleteGammaPFunction::read(std::istream& stream) {
}

void IncompleteGammaPFunction::write(std::ostream& stream) const {
  stream << "alpha: " << mAlpha;
}

void IncompleteGammaPFunction::read(std::ifstream& stream) {
}

void IncompleteGammaPFunction::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double IncompleteGammaPFunction::getValue(const VariableType& argument) const {
  return gsl_sf_gamma_inc_P(mAlpha, argument);
}

double IncompleteGammaPFunction::getAlpha() const {
  return mAlpha;
}

void IncompleteGammaPFunction::setAlpha(double alpha) {
  mAlpha = alpha;
}
