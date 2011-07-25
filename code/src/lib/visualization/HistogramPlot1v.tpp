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

#include <QtCore/QString>
#include <qwt-qt4/qwt_plot_canvas.h>
#include <qwt-qt4/qwt_symbol.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

template <typename Y, typename X>
HistogramPlot<Y, X, 1>::HistogramPlot(const std::string& title) :
  QwtPlot(0) {
//  QwtPlot::setTitle(QString(title.c_str()));
//  mXData.resize(round((maximum - minimum) / resolution));
//  mYData.resize(round((maximum - minimum) / resolution));
//  X xValue = minimum;
//  for (size_t i = 0; i < (size_t)mXData.size(); ++i) {
//    mXData[i] = xValue;
//    mYData[i] = function(xValue);
//    xValue += resolution;
//  }
//  mCurve.setData(mXData, mYData);
//  mCurve.setPen(QPen(QColor(Qt::blue)));
//  //mCurve.setCurveAttribute(QwtPlotCurve::Fitted, true);
//  //mCurve.setBrush(QBrush(QColor(Qt::blue)));
//  //mCurve.setSymbol(QwtSymbol(QwtSymbol::Cross, Qt::NoBrush,
//    //QPen(Qt::black), QSize(5, 5)));
//  mCurve.setStyle(QwtPlotCurve::Lines);
//  mCurve.attach(this);
//  mGrid.enableX(true);
//  mGrid.enableY(true);
//  mGrid.enableXMin(false);
//  mGrid.enableYMin(false);
//  mGrid.setMajPen(QPen(Qt::black, 0, Qt::DotLine));
//  mGrid.attach(this);
//  canvas()->setLineWidth(2);
//  QPalette palette = canvas()->palette();
//  palette.setColor(backgroundRole(), QColor(255, 255, 255));
//  canvas()->setPalette(palette);
//  canvas()->setAutoFillBackground(true);
//  setAxisTitle(QwtPlot::xBottom, QString('x'));
//  setAxisTitle(QwtPlot::yLeft, QString('y'));
//  replot();
//  //setFixedSize(sizeHint());
}

template <typename Y, typename X>
HistogramPlot<Y, X, 1>::HistogramPlot(const HistogramPlot<Y, X, 1>& other) :
  QwtPlot(other),
  mCurve(other.mCurve),
  mXData(other.mXData),
  mYData(other.mYData) {
}

template <typename Y, typename X>
HistogramPlot<Y, X, 1>& HistogramPlot<Y, X, 1>::operator =
  (const HistogramPlot<Y, X, 1>& other) {
  if (this != &other) {
    this->QwtPlot::operator=(other);
    mCurve = other.mCurve;
    mXData = other.mXData;
    mYData = other.mYData;
  }
  return *this;
}

template <typename Y, typename X>
HistogramPlot<Y, X, 1>::~HistogramPlot() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

template <typename Y, typename X>
void HistogramPlot<Y, X, 1>::show() {
  QWidget::show();
}
