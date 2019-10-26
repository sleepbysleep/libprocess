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
#include "circle.hpp"

template<typename T> class Triangle {
  static_assert(std::is_arithmetic<T>::value, "non-arithmetic typed class is not defined!");
  template<typename U> friend class Triangle;
  
public:
  Triangle() { BOOST_LOG_TRIVIAL(info) << "Triangle: Default constructor"; }
  Triangle(const T& aX, const T& aY, const T& aZ,
	   const T& bX, const T& bY, const T& bZ,
	   const T& cX, const T& cY, const T& cZ) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Normal constructor";
    this->a.reallocate();
    this->a.setXYZ(aX, aY, aZ);
    this->b.reallocate();
    this->b.setXYZ(bX, bY, bZ);
    this->c.reallocate();
    this->c.setXYZ(cX, cY, cZ);
  }
  Triangle(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Normal constructor with deep copy";
    if (a.isNotAllocated() or b.isNotAllocated() or c.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Triangle: invalid argument in normal constructor with deep copy";
      throw std::invalid_argument("Triangle: argument(s) with nullptr in normal constructor with deep copy");
    }
    this->a.reallocate();
    this->a = a; // copy assignment with deep copy
    this->b.reallocate();
    this->b = b; // copy assignment with deep copy
    this->c.reallocate();
    this->c = c;
  }
  Triangle(Point<T>&& a, Point<T>&& b, Point<T>&& c) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Normal constructor with shallow copy";
    if (a.isNotAllocated() or b.isNotAllocated() or c.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Triangle: invalid argument in normal constructor with shallow copy";
      throw std::invalid_argument("Triangle: argument(s) with nullptr in normal constructor with shallow copy");
    }
    this->a = std::move(a); // move assignment with shallow copy
    this->b = std::move(b); // move assignment with shallow copy
    this->c = std::move(c);
  }
  // Copy constructor
  Triangle(const Triangle<T>& triangle) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Copy constructor";
    if (triangle.a.isNotAllocated() or triangle.b.isNotAllocated() or triangle.c.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Triangle: invalid argument in copy constructor";
      throw std::invalid_argument("Triangle: argument(s) with nullptr in copy constructor");
    }
    this->a.reallocate();
    this->a = triangle.a;
    this->b.reallocate();
    this->b = triangle.b;
    this->c.reallocate();
    this->c = triangle.c;
  }
  // Move constructor
  Triangle(Triangle<T>&& triangle) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Move constructor";
    if (triangle.a.isNotAllocated() or triangle.b.isNotAllocated() or triangle.c.isNotAllocated()) {
      BOOST_LOG_TRIVIAL(error) << "Triangle: invalid argument in move constructor";
      throw std::invalid_argument("Triangle: argument(s) with nullptr in move constructor");
    }
    this->a = std::move(triangle.a);
    this->b = std::move(triangle.b);
    this->c = std::move(triangle.c);
  }
  // Destructor
  ~Triangle() {
    BOOST_LOG_TRIVIAL(info) << "Triangle: Destructor";
  }

  inline Point<T>& getA(void) { return this->a; } // when declaration is Triangle<T> triangle;
  inline Point<T>& getB(void) { return this->b; } // when declaration is Triangle<T> triangle;
  inline Point<T>& getC(void) { return this->c; } // when declaration is Triangle<T> triangle;
  inline Point<T> getA(void) const { return this->a; } // when const Triangle<T> triangle;
  inline Point<T> getB(void) const { return this->b; } // when const Triangle<T> triangle;
  inline Point<T> getC(void) const { return this->c; } // when const Triangle<T> triangle;
  inline T Ax(void) const { return this->a.x(); }
  inline T Ay(void) const { return this->a.y(); }
  inline T Az(void) const { return this->a.z(); }
  inline T Bx(void) const { return this->b.x(); }
  inline T By(void) const { return this->b.y(); }
  inline T Bz(void) const { return this->b.z(); }
  inline T Cx(void) const { return this->c.x(); }
  inline T Cy(void) const { return this->c.y(); }
  inline T Cz(void) const { return this->c.z(); }

  // copy assignment
  inline void setA(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setA() with copy assignment";
    this->a = point;
  }

  inline void setB(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setB() with copy assignment";
    this->b = point;
  }

  inline void setC(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setC() with copy assignment";
    this->c = point;
  }

  inline void setPoints(const Point<T>& a, const Point<T>& b, const Point<T>& c) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setPoints() with copy assignment";
    this->a = a, this->b = b, this->c = c;
  }

  // move assignment
  inline void setA(Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setA() with move assignment";
    this->a = std::move(point);
  }

  inline void setB(Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setB() with move assignment";
    this->b = std::move(point);
  }    

  inline void setC(Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setC() with move assignment";
    this->c = std::move(point);
  }    
    
  inline void setPoints(Point<T>&& a, Point<T>&& b, Point<T>&& c) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: setPoints() with move assignment";
    this->a = std::move(a), this->b = std::move(b), this->c = std::move(c);
  }

  // Copy assignment
  template<typename U> Triangle<T>& operator =(const Triangle<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator =() with copy assignment";
    if (this != &rhs) {
      this->a = rhs.a, this->b = rhs.b, this->c = rhs.c;
    }
    return *this;
  }

  // Move assignment
  Triangle<T>& operator =(Triangle<T>&& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator =() with move assignment from const";
    if (this != &rhs) {
      this->a = std::move(rhs.a), this->b = std::move(rhs.b), this->c = std::move(rhs.c);
    }
    return *this;
  }

  template<typename U> inline bool operator ==(const Triangle<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator ==()";
    return (this->a == rhs.a and this->b == rhs.b and this->c == rhs.c) or
      (this->a == rhs.a and this->b == rhs.c and this->c == rhs.b) or
      (this->a == rhs.b and this->b == rhs.c and this->c == rhs.a) or
      (this->a == rhs.b and this->b == rhs.a and this->c == rhs.c) or
      (this->a == rhs.c and this->b == rhs.a and this->c == rhs.b) or
      (this->a == rhs.c and this->b == rhs.b and this->c == rhs.a);
  }

  template<typename U> inline bool operator !=(const Line<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "triangle: operator !=()";
    return (this->a != rhs.a or this->b != rhs.b or this->c != rhs.c) and
      (this->a != rhs.a or this->b != rhs.c or this->c != rhs.b) and
      (this->a != rhs.b or this->b != rhs.c or this->c != rhs.a) and
      (this->a != rhs.b or this->b != rhs.a or this->c != rhs.c) and
      (this->a != rhs.c or this->b != rhs.a or this->c != rhs.b) and
      (this->a != rhs.c or this->b != rhs.b or this->c != rhs.a);
  }

  template<typename U> Triangle<T> operator +(const Point<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator +()";
    return Triangle<T>(this->a+rhs, this->b+rhs, this->c+rhs);
  }

  template<typename U> Triangle<T> operator -(const Point<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator -()";
    return Triangle<T>(this->a-rhs, this->b-rhs, this->c-rhs);
  }

  template<typename U> Triangle<T>& operator +=(const Point<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator +=()";
    this->a += rhs, this->b += rhs, this->c += rhs;
    return *this;
  }

  template<typename U> Triangle<T>& operator -=(const Point<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Triangle: operator -=()";
    this->a -= rhs, this->b -= rhs, this->c -= rhs;
    return *this;
  }

  inline std::ostream& dump(std::ostream& os) const {
    this->a.dump(os);
    os << " -> ";
    this->b.dump(os);
    os << " -> ";
    this->c.dump(os);
    return os;
  }

  // Special members

  // Heron's formula
  inline double getArea(void) const {
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double s = (a + b + c) / 2.0;
    double area = std::sqrt(s*(s-a)*(s-b)*(s-c));
    return area;
  }
  
  Circle<T>& getIncircle(void) const {
    //BOOST_LOG_TRIVIAL(info) << "Triangle: getI
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double ss = a + b + c;
    double s = ss / 2.0;
    double inradius = std::sqrt((s-a)*(s-b)*(s-c) / s);
    
    Circle<T> incircle((a*this->a.x() + b*this->b.x() + c*this->c.x()) / ss,
		       (a*this->a.y() + b*this->b.y() + c*this->c.y()) / ss,
		       (a*this->a.z() + b*this->b.z() + c*this->c.z()) / ss,
		       inradius);
    return incircle;
  }

  Circle<T>& getExcircleOfA(void) const {
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double s = (a + b + c) / 2;
    double exradius = std::sqrt(s*(s-b)*(s-c) / (s-a));
    double denom = -a + b + c;
    Circle<T> excircle((-a*this->a.x() + b*this->b.x() + c*this->c.x()) / denom,
		       (-a*this->a.y() + b*this->b.y() + c*this->c.y()) / denom,
		       (-a*this->a.z() + b*this->b.z() + c*this->c.z()) / denom,
		       exradius);
    return excircle;
  }

  Circle<T>& getExcircleOfB(void) const {
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double s = (a + b + c) / 2;
    double exradius = std::sqrt(s*(s-a)*(s-c) / (s-b));
    double denom = a - b + c;
    Circle<T> excircle((a*this->a.x() - b*this->b.x() + c*this->c.x()) / denom,
		       (a*this->a.y() - b*this->b.y() + c*this->c.y()) / denom,
		       (a*this->a.z() - b*this->b.z() + c*this->c.z()) / denom,
		       exradius);
    return excircle;
  }

  Circle<T>& getExcircleOfC(void) const {
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double s = (a + b + c) / 2;
    double exradius = std::sqrt(s*(s-a)*(s-b) / (s-c));
    double denom = a + b - c;
    Circle<T> excircle((a*this->a.x() + b*this->b.x() - c*this->c.x()) / denom,
		       (a*this->a.y() + b*this->b.y() - c*this->c.y()) / denom,
		       (a*this->a.z() + b*this->b.z() - c*this->c.z()) / denom,
		       exradius);
    return excircle;
  }
  
  Circle<T>& getCircumcircle(void) const {
    double a = getDistance(this->b, this->c);
    double b = getDistance(this->c, this->a);
    double c = getDistance(this->a, this->b);
    double ss = a + b + c; // perimeter
    double s = ss / 2.0; // semiperimeter
    double area = std::sqrt(s*(s-a)*(s-b)*(s-c));
    double circumradius = (a * b * c) / (4*area);
    double eight_sqr_area = 8 * area * area;
    
    Point<T> d1, d2;
    
    d1 = this->a - this->b;
    d2 = this->a - this->c;
    double alpha = a * a * d1.dotProduct(d2) / eight_sqr_area;

    d1 = this->b - this->a;
    d2 = this->b - this->c;
    double beta = b * b * d1.dotProdcut(d2) / eight_sqr_area;

    d1 = this->c - this->a;
    d2 = this->c - this->b;
    double gamma = c * c * d1.dotProduct(d2) / eight_sqr_area;

    Circle<T> circum(alpha * this->a.x() + beta * this->b.x() + gamma * this->c.x(),
		     alpha * this->a.y() + beta * this->b.y() + gamma * this->c.y(),
		     alpha * this->a.z() + beta * this->b.z() + gamma * this->c.z(),
		     circumradius);
    return circum;
  }
  
  /*
  void getInnerCircle(void) const {
  }

  void getOuterCircle(void) const {
  }
  
  double getArea(void) const {
    double dx = this->a[0] - this->b[0];
    double dy = this->a[1] - this->b[1];
    double dz = this->a[2] - this->b[2];
    return std::sqrt(dx*dx + dy*dy + dz*dz);
  }
  */

protected:
  //Point<T> a = Point<T>(0,0,0);
  //Point<T> b = Point<T>(0,0,0);
  Point<T> a;
  Point<T> b;
  Point<T> c;
};

template<typename T> std::ostream& operator <<(std::ostream& os, const Triangle<T>& rhs)
{
  rhs.dump(os);
  return os;
}
