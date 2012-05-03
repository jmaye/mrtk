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

#include "visualization/View2dControl.h"

#include <QtCore/QDir>
#include <QtGui/QFileDialog>
#include <QtGui/QImage>
#include <QtGui/QPainter>

#include "visualization/View2d.h"

#include "ui_View2dControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

View2dControl::View2dControl() :
    mUi(new Ui_View2dControl()) {
  mUi->setupUi(this);
  mUi->colorChooser->setPalette(&mPalette);
  connect(&mPalette, SIGNAL(colorChanged(const QString&, const QColor&)),
    this, SLOT(colorChanged(const QString&, const QColor&)));
  connect(&View2d::getInstance(), SIGNAL(resized()), this, SLOT(resized()));
  connect(&View2d::getInstance(),
    SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(viewTranslationChanged(const std::vector<double>&)));
  viewTranslationChanged(View2d::getInstance().getTranslation());
  connect(&View2d::getInstance(),
    SIGNAL(rotationChanged(double)), this,
    SLOT(viewRotationChanged(double)));
  viewRotationChanged(View2d::getInstance().getRotation());
  connect(&View2d::getInstance(), SIGNAL(scaleChanged(double)),
    this, SLOT(viewScaleChanged(double)));
  viewScaleChanged(View2d::getInstance().getScale());
  setBackgroundColor(Qt::white);
  setDumpDirectory(QDir::current().path());
  setDumpAll(false);
  drawAxes(1000);
}

View2dControl::~View2dControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void View2dControl::setShowAxes(bool showAxes) {
  mUi->showAxesCheckBox->setChecked(showAxes);
  mGraphicsItems["axes"]->setVisible(showAxes);
}

void View2dControl::setBackgroundColor(const QColor& color) {
  mPalette.setColor("Background", color);
}

void View2dControl::setDumpDirectory(const QString& dirname) {
  QDir dir(dirname);
  mUi->dumpDirEdit->setText(dir.absolutePath());
}

void View2dControl::setDumpFrameSize(size_t width, size_t height) {
  mUi->frameWidthSpinBox->setValue(width);
  mUi->frameHeightSpinBox->setValue(height);
}

void View2dControl::setDumpFormat(const QString& format) {
  mUi->dumpFormatEdit->setText(format);
}

void View2dControl::setDumpAll(bool dumpAll) {
  if (dumpAll)
    connect(&View2d::getInstance(), SIGNAL(updated()), this, SLOT(dumpFrame()));
  else
    View2d::getInstance().disconnect(SIGNAL(updated()));
  mUi->dumpAllCheckBox->setChecked(dumpAll);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void View2dControl::dumpFrame() {
  static bool dumping = false;
  if (dumping)
    return;
  dumping = true;
  QApplication::processEvents();
  dumpFrame(mUi->dumpFormatEdit->text(), mUi->frameSpinBox->value(),
    mUi->frameWidthSpinBox->value(), mUi->frameHeightSpinBox->value());
  dumping = false;
}

void View2dControl::dumpFrame(const QString& format, int frame, size_t width,
    size_t height) {
  QDir dir(mUi->dumpDirEdit->text());
  if (dir.isReadable()) {
    QString filename;
    filename.sprintf(format.toAscii().constData(), frame);
    QImage image(QSize(width, height), QImage::Format_RGB32);
    QPainter painter(&image);
    View2d::getInstance().render(&painter);
    QFileInfo fileInfo(dir, filename);
    if (image.save(fileInfo.absoluteFilePath()))
      mUi->frameSpinBox->setValue(frame + 1);
  }
}

void View2dControl::drawAxes(double length) {
  QGraphicsItem* axes = View2d::getInstance().getScene().addLine(0, 0, 0,
    length, QPen(Qt::green, 1));
  QGraphicsLineItem* axesXLine = new QGraphicsLineItem(0, 0, length, 0, axes);
  axesXLine->setPen(QPen(Qt::red, 1));
  QGraphicsSimpleTextItem* axesXLabel = new QGraphicsSimpleTextItem(
    QString("x"), axesXLine);
  axesXLabel->setBrush(Qt::red);
  axesXLabel->setPos(length, 0);
  QGraphicsSimpleTextItem* axesYLabel = new QGraphicsSimpleTextItem(
    QString("y"), axes);
  axesYLabel->setBrush(Qt::green);
  axesYLabel->setPos(0, length);
  mGraphicsItems["axes"] = axes;
}

void View2dControl::showAxesToggled(bool checked) {
  setShowAxes(checked);
}

void View2dControl::colorChanged(const QString& role, const QColor& color) {
  View2d::getInstance().getScene().setBackgroundBrush(
    mPalette.getColor("Background"));
}

void View2dControl::dumpDirBrowseClicked() {
  QString dirname = QFileDialog::getExistingDirectory(this,
    "Select Dump Directory", mUi->dumpDirEdit->text());
  if (!dirname.isNull())
    mUi->dumpDirEdit->setText(dirname);
}

void View2dControl::dumpClicked() {
  dumpFrame();
}

void View2dControl::dumpAllToggled(bool checked) {
  setDumpAll(checked);
}

void View2dControl::resized() {
  setDumpFrameSize(View2d::getInstance().rect().width(),
    View2d::getInstance().rect().height());
}

void View2dControl::viewTransformChanged() {
  View2d::getInstance().setRotation(mUi->viewYawSpinBox->value());
  View2d::getInstance().setTranslation(mUi->viewXSpinBox->value(),
    mUi->viewYSpinBox->value());
  View2d::getInstance().setScale(mUi->viewScaleSpinBox->value());
}

void View2dControl::viewTranslationChanged(const std::vector<double>&
    translation) {
  mUi->viewXSpinBox->blockSignals(true);
  mUi->viewYSpinBox->blockSignals(true);
  mUi->viewXSpinBox->setValue(translation[0]);
  mUi->viewYSpinBox->setValue(translation[1]);
  mUi->viewXSpinBox->blockSignals(false);
  mUi->viewYSpinBox->blockSignals(false);
}

void View2dControl::viewRotationChanged(double rotation) {
  mUi->viewYawSpinBox->blockSignals(true);
  mUi->viewYawSpinBox->setValue(rotation);
  mUi->viewYawSpinBox->blockSignals(false);
}

void View2dControl::viewScaleChanged(double scale) {
  mUi->viewScaleSpinBox->blockSignals(true);
  mUi->viewScaleSpinBox->setValue(scale);
  mUi->viewScaleSpinBox->blockSignals(false);
}
