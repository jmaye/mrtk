#include "Image.h"

#include <highgui.h>

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

Image::Image(string filenameString) throw (IOException)
  : mImageMatrix(imread(filenameString)) {
  if (mImageMatrix.empty() == true)
    throw IOException("Image::Image(): unable to load image");
}

Image::Image(const Image& other) : mImageMatrix(other.mImageMatrix) {
}

Image& Image::operator = (const Image& other) {
  mImageMatrix = other.mImageMatrix;
  return *this;
}

Image::~Image() {
}

void Image::read(istream& stream) {
}

void Image::write(ostream& stream) const {
}

void Image::read(ifstream& stream) {
}

void Image::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream, const Image& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream, Image& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream, const Image& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream, Image& obj) {
  obj.read(stream);
  return stream;
}

const Mat& Image::getImageMatrix() const {
  return mImageMatrix;
}

cv::Mat& Image::getImageMatrix() {
  return mImageMatrix;
}
