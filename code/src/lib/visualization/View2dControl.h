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

/** \file View2dControl.h
    \brief This file defines a Qt control for viewing a 2d scene
  */

#ifndef VIEW2DCONTROL_H
#define VIEW2DCONTROL_H

#include <map>
#include <string>

#include <QtGui/QGraphicsItem>
#include <QtGui/QColor>
#include <QtCore/QString>

#include "visualization/Control.h"
#include "base/Singleton.h"
#include "visualization/Palette.h"

class Ui_View2dControl;

/** The View2dControl class represents a Qt control for viewing a 2d scene.
    \brief Qt control for viewing a 2d scene
  */
class View2dControl :
  public Control,
  public Singleton<View2dControl> {

Q_OBJECT

  /** \name Private constructors
    @{
    */
  /// Copy constructor
  View2dControl(const View2dControl& other);
  /// Assignment operator
  View2dControl& operator = (const View2dControl& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs control from parameters
  View2dControl();
  /// Destructor
  ~View2dControl();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Show axes
  void setShowAxes(bool showAxes);
    /// Sets the background color
  void setBackgroundColor(const QColor& color);
  /// Sets the dump directory
  void setDumpDirectory(const QString& dirname);
  /// Sets the dump frame size
  void setDumpFrameSize(size_t width, size_t height);
  /// Sets the dump format
  void setDumpFormat(const QString& format);
  /// Dump all frames
  void setDumpAll(bool dumpAll);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Draw the axes
  void drawAxes(double length);
  /// Dump a frame
  void dumpFrame(const QString& format, int frame, size_t width, size_t height);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Qt user interface
  Ui_View2dControl* mUi;
  /// Color palette
  Palette mPalette;
  /// Graphic items associated with this control
  std::map<std::string, QGraphicsItem*> mGraphicsItems;
  /** @}
    */

protected slots:
  /** \name Qt slots
    @{
    */
  /// Show axes
  void showAxesToggled(bool checked);
  /// Color changed
  void colorChanged(const QString& role, const QColor& color);
  /// Dump directory browse clicked
  void dumpDirBrowseClicked();
  /// Dump clicked
  void dumpClicked();
  /// Dump all toggled
  void dumpAllToggled(bool checked);
  /// Dump frame
  void dumpFrame();
  /// View resized
  void resized();
  /// View transformation changed
  void viewTransformChanged();
  /// View translation has changed
  void viewTranslationChanged(const std::vector<double>& translation);
  /// View rotation has changed
  void viewRotationChanged(double rotation);
  /// View scale has changed
  void viewScaleChanged(double scale);
  /** @}
    */

};

#endif // VIEW2DCONTROL_H
