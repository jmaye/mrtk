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

#include "visualization/Plot2D.h"

#include <stdint.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Plot2D::Plot2D(const std::string& sName) {
  mpPlot = new QwtPlot(QwtText(sName.c_str()), this);
}

Plot2D::~Plot2D() {
  for (uint32_t i = 0; i < mCurvesVector.size(); i++)
    delete mCurvesVector[i];
  mCurvesVector.clear();
  delete mpPlot;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void Plot2D::addCurve(const std::vector<double>& xVector, const
  std::vector<double>& yVector, const std::string& sName)
  throw(InvalidOperationException) {
  if (xVector.size() != yVector.size())
    throw InvalidOperationException("Plot2D::addCurve(): xVector and yVector must have the same size");
  QwtPlotCurve* pCurve = new QwtPlotCurve(sName.c_str());
  mCurvesVector.push_back(pCurve);
  QVector<double> xQVector(xVector.size());
  QVector<double> yQVector(yVector.size());
  for (uint32_t i = 0; i < xVector.size(); i++) {
    xQVector[i] = xVector[i];
    yQVector[i] = yVector[i];
  }
  mDataVector.push_back(std::make_pair(xQVector, yQVector));
  pCurve->setData(mDataVector[mDataVector.size() - 1].first.data(),
    mDataVector[mDataVector.size() - 1].second.data(), xVector.size());
  pCurve->attach(mpPlot);
  mpPlot->replot();
  setFixedSize(mpPlot->sizeHint());
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

