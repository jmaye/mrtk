#ifndef WINDOW_H
#define WINDOW_H

#include <Image.h>

#include <iosfwd>
#include <string>

#include <stdint.h>

class Window {
  friend std::ostream& operator << (std::ostream& stream,
    const Window& obj);
  friend std::istream& operator >> (std::istream& stream,
    Window& obj);
  friend std::ofstream& operator << (std::ofstream& stream,
    const Window& obj);
  friend std::ifstream& operator >> (std::ifstream& stream,
    Window& obj);

  Window(const Window& other);
  Window& operator = (const Window& other);

  virtual void read(std::istream& stream);
  virtual void write(std::ostream& stream) const;
  virtual void read(std::ifstream& stream);
  virtual void write(std::ofstream& stream) const;

  std::string mWindowNameString;

public:
  Window(const std::string& windowNameString);
  ~Window();

  void showImage(const Image& image, uint32_t u32Timeout = 0) const;

protected:

};

#endif // WINDOW_H
