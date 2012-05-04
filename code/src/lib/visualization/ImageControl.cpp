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

#include "visualization/ImageControl.h"

#include <QtGui/QImage>
#include <QtGui/QMessageBox>
#include <QtGui/QFileDialog>

#include "visualization/View2d.h"

#include "ui_ImageControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ImageControl::ImageControl(bool showImage) :
    mUi(new Ui_ImageControl()) {
  mUi->setupUi(this);
  setImageFilename(QDir::current().path());
  setShowImage(showImage);
}

ImageControl::~ImageControl() {
  delete mUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

void ImageControl::setShowImage(bool showImage) {
  mUi->showImageCheckBox->setChecked(showImage);
  if (mGraphicsItems.find("image") != mGraphicsItems.end())
    mGraphicsItems["image"]->setVisible(showImage);
  }

void ImageControl::setImageFilename(const QString& filename) {
  mUi->imgEdit->setText(filename);
  QFileInfo fileInfo(filename);
  if (fileInfo.isFile() && fileInfo.isReadable()) {
    QImage image(filename);
    if (image.isNull()) {
      QMessageBox::information(this, "ImageControl",
        tr("Cannot load %1.").arg(filename));
      return;
    }
    QGraphicsItem* imageItem =
      View2d::getInstance().getScene().addPixmap(QPixmap::fromImage(image));
    if (mGraphicsItems.find("image") != mGraphicsItems.end()) {
      View2d::getInstance().getScene().removeItem(mGraphicsItems["image"]);
      delete mGraphicsItems["image"];
    }
    mGraphicsItems["image"]= imageItem;
    imageItem->setVisible(mUi->showImageCheckBox->isChecked());
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ImageControl::showImageToggled(bool checked) {
  setShowImage(checked);
}

void ImageControl::imgBrowseClicked() {
  QString filename = QFileDialog::getOpenFileName(this,
    "Open Image File", mUi->imgEdit->text(),
    "Image files (*.*)");
  if (!filename.isEmpty())
    setImageFilename(filename);
}
