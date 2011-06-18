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

/** \file Plot2D.h
    \brief Plot2D
  */

#ifndef PLOT2D_H
#define PLOT2D_H

#include "exceptions/InvalidOperationException.h"

#include <QtGui/QWidget>
#include <QtCore/QVector>
#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>

#include <string>
#include <vector>

/** Plot2D
  */
class Plot2D : public QWidget {
  QwtPlot* mpPlot;
  std::vector<QwtPlotCurve*> mCurvesVector;
  std::vector<std::pair<QVector, QVector> > mDataVector;

public:
  /** Constructors
    */
  Plot2D(std::string sName);

  /** Destructor
    */
  ~Plot2D();

  /** Accessors
    */
  void addCurve(std::vector<double> xVector, std::vector<double> yVector,
    std::string sName) throw(InvalidOperationException);

protected:

};

#endif // PLOT2D_H
