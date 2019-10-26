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

template<typename T> class Line {
  static_assert(std::is_arithmetic<T>::value, "non-arithmetic typed class is not defined!");
  template<typename U> friend class Line;
  
public:
  Line() { BOOST_LOG_TRIVIAL(info) << "Line: Default constructor"; }
  Line(const T& aX, const T& aY, const T& aZ, const T& bX, const T& bY, const T& bZ) {
    BOOST_LOG_TRIVIAL(info) << "Line: Normal constructor";
    this->a.reallocate();
    this->a.setXYZ(aX, aY, aZ);
    this->b.reallocate();
    this->b.setXYZ(bX, bY, bZ);
  }
  Line(const Point<T>& a, const Point<T>& b) {
    BOOST_LOG_TRIVIAL(info) << "Line: Normal constructor with deep copy";
    this->a.reallocate();
    this->a = a; // copy assignment with deep copy
    this->b.reallocate();
    this->b = b; // copy assignment with deep copy
  }
  Line(const Point<T>&& a, const Point<T>&& b) {
    BOOST_LOG_TRIVIAL(info) << "Line: Normal constructor with shallow copy";
    this->a = std::move(a); // move assignment with shallow copy
    this->b = std::move(b); // move assignment with shallow copy
  }
  // Copy constructor
  Line(const Line<T>& line) {
    BOOST_LOG_TRIVIAL(info) << "Line: Copy constructor";
    if (line.a.isNotAllocated() or line.b.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Line: invalid argument in copy constructor";
      throw std::invalid_argument("Line: invalid argument in copy constructor");
    }
    this->a.reallocate();
    this->a = line.a;
    this->b.reallocate();
    this->b = line.b;
  }
  // Move constructor
  Line(Line<T>&& line) {
    BOOST_LOG_TRIVIAL(info) << "Line: Move constructor";
    if (line.a.isNotAllocated() or line.b.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Line: invalid argument in move constructor";
      throw std::invalid_argument("Line: invalid argument in move constructor");
    }      
    this->a = std::move(line.a);
    this->b = std::move(line.b);
  }
  // Destructor
  ~Line() {
    BOOST_LOG_TRIVIAL(info) << "Line: Destructor";
  }

  inline Point<T>& getA(void) { return this->a; } // when Line<T> line;
  inline Point<T>& getB(void) { return this->b; } // when LIne<T> line;
  inline Point<T> getA(void) const { return this->a; } // when const Line<T> line;
  inline Point<T> getB(void) const { return this->b; } // when const Line<T> line;
  
  inline T Ax(void) const { return this->a.x(); }
  inline T Ay(void) const { return this->a.y(); }
  inline T Az(void) const { return this->a.z(); }
  inline T Bx(void) const { return this->b.x(); }
  inline T By(void) const { return this->b.y(); }
  inline T Bz(void) const { return this->b.z(); }

  inline void setA(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Line: setA() with copy assignment";
    this->a = point;
  }

  inline void setB(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Line: setB() with copy assignment";
    this->b = point;
  }

  inline void setPoints(const Point<T>& a, const Point<T>& b) {
    BOOST_LOG_TRIVIAL(info) << "Line: setPoints() with copy assignment";
    this->a = a, this->b = b;
  }

  inline void setA(const Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Line: setA() with move assignment";
    this->a = std::move(point);
  }

  inline void setB(const Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Line: setB() with move assignment";
    this->b = std::move(point);
  }    
  
  inline void setPoints(const Point<T>&& a, const Point<T>&& b) {
    BOOST_LOG_TRIVIAL(info) << "Line: setPoints() with move assignment";
    this->a = std::move(a), this->b = std::move(b);
  }

  double getLength(void) const {
    double dx = this->a[0] - this->b[0];
    double dy = this->a[1] - this->b[1];
    double dz = this->a[2] - this->b[2];
    return std::sqrt(dx*dx + dy*dy + dz*dz);
  }

  // Copy assignment
  template<typename U> Line<T>& operator =(const Line<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator =(const Line<U>&) with copy assignment";
    if (this != &rhs) {
      this->a = rhs.a, this->b = rhs.b;
    }
    return *this;
  }

  // Move assignment
  Line<T>& operator =(const Line<T>&& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator =(const Line<T>&&) with move assignment from const";
    if (this != &rhs) {
      this->a = std::move(rhs.a), this->b = std::move(rhs.b);
    }
    return *this;
  }

  template<typename U> inline bool operator ==(const Line<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator ==(const Line<U>&)";
    return (this->a == rhs.a and this->b == rhs.b) or (this->a == rhs.b and this->b == rhs.a);
  }

  template<typename U> inline bool operator !=(const Line<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator !=(const Line<U>&)";
    return (this->a != rhs.a or this->b != rhs.b) and (this->a != rhs.b or this->b != rhs.a);
  }

  // Override of operator with Point<T>
  Line<T> operator +(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator +(const Point<T>&)";
    return Line<T>(this->a+rhs, this->b+rhs);
  }

  Line<T> operator -(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator -(const Point<T>&)";
    return Line<T>(this->a-rhs, this->b-rhs);
  }

  Line<T>& operator +=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator +=(const Point<T>&)";
    this->a += rhs, this->b += rhs;
    return *this;
  }

  Line<T>& operator -=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator -=(const Point<T>&)";
    this->a -= rhs, this->b -= rhs;
    return *this;
  }

  // Override of operator with scalar
  Line<T> operator +(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator +(const T&)";
    return Line<T>(this->a+rhs, this->b+rhs);
  }

  Line<T> operator -(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator -(const T&)";
    return Line<T>(this->a-rhs, this->b-rhs);
  }

  Line<T> operator *(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator *(const T&)";
    return Line<T>(this->a*rhs, this->b*rhs);
  }

  Line<T> operator /(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Line: operator -(const T&)";
    return Line<T>(this->a/rhs, this->b/rhs);
  }
  
  Line<T>& operator +=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator +=(const T&)";
    this->a += rhs, this->b += rhs;
    return *this;
  }

  Line<T>& operator -=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator -=(const T&)";
    this->a -= rhs, this->b -= rhs;
    return *this;
  }

  Line<T>& operator *=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator *=(const T&)";
    this->a *= rhs, this->b *= rhs;
    return *this;
  }

  Line<T>& operator /=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Line: operator /=(const T&)";
    this->a /= rhs, this->b /= rhs;
    return *this;
  }
  
  inline std::ostream& dump(std::ostream& os) const {
    os << "Line: ";
    this->a.dump(os);
    os << " -> ";
    this->b.dump(os);
    return os;
  }

protected:
  Point<T> a;
  Point<T> b;
};

template<typename T> std::ostream& operator <<(std::ostream& os, const Line<T>& rhs)
{
  rhs.dump(os);
  return os;
}
