#ifndef IMAGE_H
#define IMAGE_H

#include "IOException.h"

#include <cv.h>

#include <iosfwd>
#include <string>

class Image {
  friend std::ostream& operator << (std::ostream& stream, const Image& obj);
  friend std::istream& operator >> (std::istream& stream, Image& obj);
  friend std::ofstream& operator << (std::ofstream& stream, const Image& obj);
  friend std::ifstream& operator >> (std::ifstream& stream, Image& obj);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  cv::Mat mImageMatrix;

public:
  Image(std::string filenameString) throw (IOException);
  Image(const Image& other);
  Image& operator = (const Image& other);
  ~Image();

  const cv::Mat& getImageMatrix() const;
  cv::Mat& getImageMatrix();

protected:

};

#endif // IMAGE_H
