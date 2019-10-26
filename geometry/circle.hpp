#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>
#include <array>
#include <cmath>
#include <type_traits>

#include <boost/log/trivial.hpp>
//#include "spdlog/spdlog.h"
#include "point.hpp"

template<typename T> class Circle {
  static_assert(std::is_arithmetic<T>::value, "non-arithmetic typed class is not defined!");
  template<typename U> friend class Circle;
public:
  // Default constructor
  Circle() { BOOST_LOG_TRIVIAL(info) << "Circle: Default constructor"; }
  // Normal constructor
  Circle(const T& centerX, const T& centerY, const T& centerZ, const T& radius) {
    BOOST_LOG_TRIVIAL(info) << "Circle: Normal constructor";
    this->center.reallocate();
    this->center.setXYZ(centerX, centerY, centerZ);
    this->radius = radius;
  }
  Circle(const Point<T>& center, const T& radius) {
    BOOST_LOG_TRIVIAL(info) << "Circle: Normal constructor with deep copy";
    if (center.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Circle: invalid argument in normal constructor";
      throw std::invalid_argument("Circle: center with nullptr in normal constructor");
    }
    this->center.reallocate();
    this->center = center;
    this->radius = radius;
  }
  Circle(const Point<T>&& center, const T& radius) {
    BOOST_LOG_TRIVIAL(info) << "Circle: Normal constructor with shallow copy";
    if (center.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Circle: invalid argument in normal constructor";
      throw std::invalid_argument("Circle: center with nullptr in normal constructor");
    }
    this->center = std::move(center);
    this->radius = radius;
  }
  // Copy constructor
  Circle(const Circle<T>& circle) {
    BOOST_LOG_TRIVIAL(info) << "Circle: Copy constructor";
    if (circle.center.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Circle: invalid argument in copy constructor";
      throw std::invalid_argument("Circle: circle with nullptr in copy constructor");
    }
    this->center.reallocate();
    this->center = circle.center;
    this->radius = circle.radius;
  }
  // Move constructor
  Circle(const Circle<T>&& circle) {
    BOOST_LOG_TRIVIAL(info) << "Circle: Move constructor";
    if (circle.center.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Circle: invalid argument in move constructor";
      throw std::invalid_argument("Circle: circle with nullptr in move constructor");
    }
    this->center = std::move(circle.center);
    this->radius = circle.radius;
  }
  // Desctructor
  ~Circle() { BOOST_LOG_TRIVIAL(info) << "Circle: Destructor"; }

  inline Point<T>& getCenter(void) { return this->center; } // when declaration is like "Circle<T> circle;"
  inline Point<T> getCenter(void) const { return this->center; } // when "const Circle<T> circle;"
  inline T Ox(void) const { return this->center.x(); }
  inline T Oy(void) const { return this->center.y(); }
  inline T Oz(void) const { return this->center.z(); }
  inline T r(void) const { return this->radius; }

  // copy assignment
  inline void setCenter(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Circle: setCenter() with copy assignment";
    this->center = point;
  }

  // move assignment
  inline void setCenter(const Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Circle: setCenter() with move assignment";
    this->center = std::move(point);
  }

  inline void setRadius(const T& radius) {
    BOOST_LOG_TRIVIAL(info) << "Circle: setRadius()";
    this->radius = radius;
  }

  // Copy assignment
  template<typename U> Circle<T>& operator =(const Circle<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator =(const Circle<U>&) with copy assignment";
    if (this != &rhs) {
      this->center = rhs.center, this->radius = rhs.radius;
    }
    return *this;
  }

  // Move assignment
  Circle<T>& operator =(const Circle<T>&& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator =(Circle<T>&&) with move assignment from const";
    if (this != &rhs) {
      this->center = std::move(rhs.center), this->radius = rhs.radius;
    }
    return *this;
  }

  template<typename U> inline bool operator ==(const Circle<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator ==(const Circle<U>&)";
    return (this->center == rhs.center and this->radius == rhs.radius);
  }

  template<typename U> inline bool operator !=(const Circle<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator !=(const Circle<U>&)";
    return (this->center != rhs.center or this->radius != rhs.radius);
  }

  // Override of operator with Point<T>
  Circle<T> operator +(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator +(const Point<T>&)";
    return Circle<T>(this->center+rhs, this->radius);
  }

  Circle<T> operator -(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator -(const Point<T>&)";
    return Circle<T>(this->center-rhs, this->radius);
  }

  Circle<T>& operator +=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator +=(const Point<T>&)";
    this->center += rhs;
    return *this;
  }

  Circle<T>& operator -=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator -=(const Point<T>&)";
    this->center -= rhs;
    return *this;
  }

  // Override of operator with scalar
  Circle<T> operator +(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator +(const T&)";
    return Circle<T>(this->center, this->radius+rhs);
  }

  Circle<T> operator -(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator -(const T&)";
    return Circle<T>(this->center, this->radius-rhs);
  }

  Circle<T> operator *(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator *(const T&)";
    return Circle<T>(this->center, this->radius*rhs);
  }

  Circle<T> operator /(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator -(const T&)";
    return Circle<T>(this->center, this->radius/rhs);
  }
  
  Circle<T>& operator +=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator +=(const T&)";
    this->radius += rhs;
    return *this;
  }

  Circle<T>& operator -=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator -=(const T&)";
    this->radius -= rhs;
    return *this;
  }

  Circle<T>& operator *=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator *=(const T&)";
    this->radius *= rhs;
    return *this;
  }

  Circle<T>& operator /=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Circle: operator /=(const T&)";
    this->radius /= rhs;
    return *this;
  }
  
  inline std::ostream& dump(std::ostream& os) const {
    os << "Circle: ";
    this->center.dump(os);
    os << " with " << this->radius;
    return os;
  }

protected:
  Point<T> center;
  T radius;
private:
};

template<typename T> std::ostream& operator <<(std::ostream& os, const Circle<T>& rhs)
{
  rhs.dump(os);
  return os;
}
