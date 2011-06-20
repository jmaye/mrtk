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

#include "visualization/SurfacePlot.h"

#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SurfacePlot::SurfacePlot(const std::string& sName) {
  setTitle(sName.c_str());
  setRotation(30, 0, 15);
  setScale(1, 1, 1);
  setShift(0.15, 0, 0);
  setZoom(0.9);
  for (uint32_t i = 0; i != coordinates()->axes.size(); i++) {
    coordinates()->axes[i].setMajors(7);
    coordinates()->axes[i].setMinors(4);
  }

  coordinates()->axes[Qwt3D::X1].setLabelString("x-axis");
  coordinates()->axes[Qwt3D::Y1].setLabelString("y-axis");
  coordinates()->axes[Qwt3D::Z1].setLabelString(QChar (0x38f));

  setCoordinateStyle(Qwt3D::BOX);

  updateData();
  updateGL();
}

SurfacePlot::~SurfacePlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void SurfacePlot::addFunction(Function& function) {
  function.setMesh(100, 100);
  function.setDomain(-10.0, 10.0, -10.0, 10.0);
  function.setMinZ(-10);
  function.create(*this);
  updateData();
  updateGL();
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

