#pragma once

#include <fstream>

class Color {
  public:
    Color();
    Color(double red, double green, double blue);
    double red() const;
    double green() const;
    double blue() const;

  private:
    double r{};
    double g{};
    double b{};
  
  friend std::istream& operator>>(std::istream& stream, Color& color);
};

std::istream& operator>>(std::istream& stream, Color& color);
