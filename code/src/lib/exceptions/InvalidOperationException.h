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

/** \file InvalidOperationException.h
    \brief InvalidOperationException
  */

#ifndef INVALIDOPERATIONEXCEPTION_H
#define INVALIDOPERATIONEXCEPTION_H

#include <stdexcept>
#include <string>

/** InvalidOperationException
  */
class InvalidOperationException : public std::runtime_error {
  InvalidOperationException& operator =
    (const InvalidOperationException &other);

public:
  InvalidOperationException(const std::string &msg = "");
  InvalidOperationException(const InvalidOperationException &other);

protected:

};

#endif // INVALIDOPERATIONEXCEPTION_H