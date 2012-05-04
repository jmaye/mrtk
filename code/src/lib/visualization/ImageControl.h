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

/** \file ImageControl.h
    \brief This file defines a Qt control for images.
  */

#ifndef IMAGECONTROL_H
#define IMAGECONTROL_H

#include <string>
#include <map>

#include <QtCore/QString>
#include <QtGui/QGraphicsItem>

#include "visualization/Control.h"
#include "base/Singleton.h"

class Ui_ImageControl;

/** The ImageControl class represents a Qt control for images.
    \brief Qt control for images
  */
class ImageControl :
  public Control,
  public Singleton<ImageControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  ImageControl(const ImageControl& other);
  /// Assignment operator
  ImageControl& operator = (const ImageControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the control with parameters
  ImageControl(bool showImage = true);
  /// Destructor
  ~ImageControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Shows the image
  void setShowImage(bool showImage);
  /// Sets the file to read the image from
  void setImageFilename(const QString& filename);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_ImageControl* mUi;
  /// Graphic items associated with this control
  std::map<std::string, QGraphicsItem*> mGraphicsItems;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Show image toggled
  void showImageToggled(bool checked);
  /// Image file browse clicked
  void imgBrowseClicked();
  /** @}
    */

signals:
  /** \name Qt signals
    @{
    */
  /** @}
    */

};

#endif // IMAGECONTROL_H
