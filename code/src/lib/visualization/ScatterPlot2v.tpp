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

#include <unordered_map>

#include <QtCore/QString>

#include <qwt-qt4/qwt_plot_canvas.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ScatterPlot<2>::ScatterPlot(const std::string& title, const
    PointCloud<double, 2>::Container& data) :
    mPanner(canvas()),
    mMagnifier(canvas()) {
  QwtPlot::setTitle(QString(title.c_str()));
  Color color;
  color.mRedColor = 0;
  color.mGreenColor = 0;
  color.mBlueColor = 1;
  addPoints(data, color);
  mGrid.enableX(true);
  mGrid.enableY(true);
  mGrid.enableXMin(false);
  mGrid.enableYMin(false);
  mGrid.setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  mGrid.attach(this);
  canvas()->setLineWidth(2);
  QPalette palette = canvas()->palette();
  palette.setColor(backgroundRole(), Qt::white);
  canvas()->setPalette(palette);
  canvas()->setAutoFillBackground(true);
  setAxisTitle(QwtPlot::xBottom, QString('x'));
  setAxisTitle(QwtPlot::yLeft, QString('y'));
  replot();
}

ScatterPlot<2>::ScatterPlot(const std::string& title, const
    std::vector<std::tuple<PointCloud<double, 2>::Point, size_t> >& data) :
    mPanner(canvas()),
    mMagnifier(canvas()) {
  QwtPlot::setTitle(QString(title.c_str()));
  mGrid.enableX(true);
  mGrid.enableY(true);
  mGrid.enableXMin(false);
  mGrid.enableYMin(false);
  mGrid.setMajPen(QPen(Qt::black, 0, Qt::DotLine));
  mGrid.attach(this);
  canvas()->setLineWidth(2);
  QPalette palette = canvas()->palette();
  palette.setColor(backgroundRole(), Qt::white);
  canvas()->setPalette(palette);
  canvas()->setAutoFillBackground(true);
  setAxisTitle(QwtPlot::xBottom, QString('x'));
  setAxisTitle(QwtPlot::yLeft, QString('y'));
  std::unordered_map<size_t, std::vector<PointCloud<double, 2>::Point> > points;
  for (auto it = data.cbegin(); it != data.cend(); ++it)
    points[std::get<1>(*it)].push_back(std::get<0>(*it));
  std::vector<Color> colors;
  randomColors(colors, points.size());
  std::vector<Color>::const_iterator itColors;
  for (auto itPoints = points.cbegin(), itColors = colors.cbegin();
      itPoints != points.cend(); ++itPoints, ++itColors)
    addPoints(itPoints->second, *itColors);
  replot();
}

ScatterPlot<2>::~ScatterPlot() {
  for (auto it = mPoints.cbegin(); it != mPoints.cend(); ++it)
    delete *it;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ScatterPlot<2>::addPoints(const PointCloud<double, 2>::Container& data,
    const Color& color) {
  QVector<double> xData;
  QVector<double> yData;
  xData.reserve(data.size());
  yData.reserve(data.size());
  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    xData.push_back((*it)(0));
    yData.push_back((*it)(1));
  }
  QwtPlotCurve* points = new QwtPlotCurve();
  points->setData(xData, yData);
  points->setPen(QPen(QColor(color.mRedColor * 255, color.mGreenColor * 255,
    color.mBlueColor * 255)));
  points->setStyle(QwtPlotCurve::Dots);
  points->attach(this);
  mPoints.push_back(points);
}
