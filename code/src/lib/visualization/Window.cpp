#include "Window.h"

#include <highgui.h>

#include <iostream>
#include <fstream>

using namespace cv;
using namespace std;

Window::Window(const string& windowNameString)
  : mWindowNameString(windowNameString) {
  namedWindow(windowNameString, CV_WINDOW_AUTOSIZE);
}

Window::~Window() {
}

void Window::read(istream& stream) {
}

void Window::write(ostream& stream) const {
}

void Window::read(ifstream& stream) {
}

void Window::write(ofstream& stream) const {
}

ostream& operator << (ostream& stream,
  const Window& obj) {
  obj.write(stream);
  return stream;
}

istream& operator >> (istream& stream,
  Window& obj) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream& stream,
  const Window& obj) {
  obj.write(stream);
  return stream;
}

ifstream& operator >> (ifstream& stream,
  Window& obj) {
  obj.read(stream);
  return stream;
}

void Window::showImage(const Image& image, uint32_t u32Timeout) const {
  imshow(mWindowNameString, image.getImageMatrix());
  waitKey(u32Timeout);
}
