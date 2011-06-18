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

#include <QtGui/QApplication>
/*#include <qwt-qt4/qwt_plot.h>
#include <qwt-qt4/qwt_plot_curve.h>

class Window : public QWidget {
  public:
    Window() :
      valueCount(100),
      x(valueCount),
      y1(valueCount),
      y2(valueCount) {
      QwtPlot *myPlot = new QwtPlot(QwtText("Two Curves" ), this);

      // add curves
      QwtPlotCurve *curve1 = new QwtPlotCurve("Curve 1" );
      QwtPlotCurve *curve2 = new QwtPlotCurve("Curve 2" );
      createCurveData();

      // copy the data into the curves
      curve1->setData(x.data(), y1.data(), 100);
      curve2->setData(x.data(), y2.data(), 100);
      curve1->attach(myPlot);
      curve2->attach(myPlot);

      // finally, refresh the plot
      myPlot->replot();

      setFixedSize(myPlot->sizeHint());
    }

  private:
    void createCurveData() {
      for (int i = 0; i < valueCount; i++) {
        x[i] = i;
        y1[i] = i;
        y2[i] = 100 - i;
      }
    }

  private:
    const int valueCount;
    QVector<double> x;
    QVector<double> y1;
    QVector<double> y2;
};*/

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  Plot2D plot("Test");
  plot.show();
  return app.exec();
}
