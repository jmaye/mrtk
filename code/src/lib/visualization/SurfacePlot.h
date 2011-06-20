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

/** \file SurfacePlot.h
    \brief SurfacePlot
  */

#ifndef SURFACEPLOT_H
#define SURFACEPLOT_H

#include "visualization/Function.h"

#include <qwtplot3d-qt4/qwt3d_surfaceplot.h>

#include <string>

/** SurfacePlot
  */
class SurfacePlot :
  public Qwt3D::SurfacePlot {

public:
  /** Constructors
    */
  SurfacePlot(const std::string& sName);

  /** Destructor
    */
  ~SurfacePlot();

  /** Accessors
    */
  void addFunction(Function& function);

protected:

};

#endif // SURFACEPLOT_H
