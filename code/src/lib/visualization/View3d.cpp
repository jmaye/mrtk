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

#include "visualization/View3d.h"

#include <cmath>

#include <QtCore/QFileInfo>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>

#include <FTGL/ftgl.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

View3d::View3d(QWidget* parent) :
    QGLWidget(parent),
    mFont(0),
    mMouse(2, 0),
    mViewport(4, 0),
    mProjection(16, 0.0),
    mModelview(16, 0.0) {
  setFont("/usr/share/fonts/truetype/msttcorefonts/Arial.ttf");
  connect(&mCamera, SIGNAL(positionChanged(const std::vector<double>&)), this,
    SLOT(cameraPositionChanged(const std::vector<double>&)));
  connect(&mCamera, SIGNAL(viewpointChanged(const std::vector<double>&)), this,
    SLOT(cameraViewpointChanged(const std::vector<double>&)));
  connect(&mCamera, SIGNAL(rangeChanged(const std::vector<double>&)), this,
    SLOT(cameraRangeChanged(const std::vector<double>&)));
  connect(&mScene, SIGNAL(translationChanged(const std::vector<double>&)), this,
    SLOT(sceneTranslationChanged(const std::vector<double>&)));
  connect(&mScene, SIGNAL(rotationChanged(const std::vector<double>&)), this,
    SLOT(sceneRotationChanged(const std::vector<double>&)));
  connect(&mScene, SIGNAL(scaleChanged(double)), this,
    SLOT(sceneScaleChanged(double)));
}

View3d::~View3d() {
  if (mFont)
    delete mFont;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

Camera& View3d::getCamera() {
  return mCamera;
}

const Camera& View3d::getCamera() const {
  return mCamera;
}

Scene3d& View3d::getScene() {
  return mScene;
}

const Scene3d& View3d::getScene() const {
  return mScene;
}

void View3d::setColor(const QColor& color) {
  glColor4f(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void View3d::setColor(const Palette& palette, const QString& role) {
  setColor(palette.getColor(role));
}

void View3d::setFont(const QString& filename) {
  if (mFontFilename != filename) {
    if (mFont) {
      delete mFont;
      mFont = 0;
    }
    mFontFilename = filename;
    emit fontChanged(mFontFilename);
    update();
  }
}

const QString& View3d::getFont() const {
  return mFontFilename;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

std::vector<double> View3d::unproject(const QPoint& point, double distance) {
  std::vector<double> result(3, 0.0);
  double near = mCamera.getRange()[0];
  double far = mCamera.getRange()[1];
  double z = (1.0 / near - 1.0 / distance) / (1.0 / near - 1.0 / far);
  gluUnProject(point.x(), -point.y(), z, &mModelview[0], &mProjection[0],
    &mViewport[0], &result[0], &result[1], &result[2]);
  return result;
}

void View3d::render(double x, double y, double z, const QString& text,
    double minScale, double maxScale, bool faceX, bool faceY, bool faceZ) {
  if (!mFont) {
    QFileInfo fileInfo(mFontFilename);
    if (fileInfo.isFile() && fileInfo.isReadable()) {
      mFont = new FTPolygonFont(mFontFilename.toAscii().constData());
      mFont->UseDisplayList(false);
      mFont->FaceSize(1);
    }
  }
  if (mFont) {
    glPushMatrix();
    glTranslatef(x, y, z);
    if (faceZ)
      glRotatef(-mScene.getRotation()[0] * 180.0 / M_PI, 0, 0, 1);
    if (faceY)
      glRotatef(-mScene.getRotation()[1] * 180.0 / M_PI, 0, 1, 0);
    if (faceX)
      glRotatef(-mScene.getRotation()[2] * 180.0 / M_PI, 1, 0, 0);
    glRotatef(90.0, 1, 0, 0);
    glRotatef(-90.0, 0, 1, 0);
    const double scale = std::max(minScale, std::min(maxScale,
      mScene.getScale()));
    glScalef(scale / mScene.getScale(), scale / mScene.getScale(),
      scale / mScene.getScale());
    mFont->Render(text.toAscii().constData());
    glPopMatrix();
  }
}

void View3d::mousePressEvent(QMouseEvent* event) {
  mMouse[0] = event->globalX();
  mMouse[1] = event->globalY();
}

void View3d::mouseMoveEvent(QMouseEvent* event) {
  int deltaX = event->globalX() - mMouse[0];
  int deltaY = event->globalY() - mMouse[1];
  if (event->buttons() == Qt::LeftButton) {
    mScene.setRotation(
      mScene.getRotation()[0] - M_PI / width() * deltaX,
      mScene.getRotation()[1] + M_PI / height() * deltaY,
      mScene.getRotation()[2]);
  }
  else if (event->buttons() == Qt::RightButton) {
    QPoint mouseLocal = mapFromGlobal(QPoint(mMouse[0], mMouse[1]));
    QPoint eventLocal = mapFromGlobal(QPoint(event->globalPos()));
    double distance = mCamera.getViewpointDistance();
    std::vector<double> mouseUnprojected = unproject(mouseLocal, distance);
    std::vector<double> eventUnprojected = unproject(eventLocal, distance);
    mScene.setTranslation(
      mScene.getTranslation()[0] + (eventUnprojected[0] -
        mouseUnprojected[0]),
      mScene.getTranslation()[1] + (eventUnprojected[1] -
        mouseUnprojected[1]),
      mScene.getTranslation()[2] + (eventUnprojected[2] -
        mouseUnprojected[2]));
  }
  mMouse[0] = event->globalX();
  mMouse[1] = event->globalY();
}

void View3d::wheelEvent(QWheelEvent* event) {
  double deltaScale = 1e-2;
  mScene.setScale(mScene.getScale() * (1.0 + deltaScale * event->delta() /
    8.0));
}

void View3d::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glEnable (GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  emit createDisplayLists();
}

void View3d::resizeGL(int width, int height) {
  glViewport(0, 0, width, height);
  mCamera.setup(*this, width, height);
}

void View3d::paintGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  mCamera.setup(*this, width(), height());
  mScene.setup(*this);
  glGetIntegerv(GL_VIEWPORT, &mViewport[0]);
  glGetDoublev(GL_PROJECTION_MATRIX, &mProjection[0]);
  glGetDoublev(GL_MODELVIEW_MATRIX, &mModelview[0]);
  mScene.render(*this);
}

void View3d::paintEvent(QPaintEvent* event) {
  QGLWidget::paintEvent(event);
  emit updated();
}

void View3d::cameraPositionChanged(const std::vector<double>& position) {
  update();
}

void View3d::cameraViewpointChanged(const std::vector<double>& viewpoint) {
  update();
}

void View3d::cameraRangeChanged(const std::vector<double>& range) {
  update();
}

void View3d::sceneTranslationChanged(const std::vector<double>& translation) {
  update();
}

void View3d::sceneRotationChanged(const std::vector<double>& rotation) {
  update();
}

void View3d::sceneScaleChanged(double scale) {
  update();
}

void View3d::resizeEvent(QResizeEvent* event) {
  QGLWidget::resizeEvent(event);
  emit resized();
}
