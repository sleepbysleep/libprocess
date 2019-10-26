#pragma once

#include <iostream>
#include <stdexcept>
#include <memory>
#include <array>
#include <cmath>
#include <type_traits>

#include <boost/log/trivial.hpp>
//#include "spdlog/spdlog.h"

template<typename T> class Point {
  static_assert(std::is_arithmetic<T>::value, "non-arithmetic typed class is not defined!");
  template<typename U> friend class Point;

public:
  // Empty constructor
  Point():coordPtr(nullptr) {
    BOOST_LOG_TRIVIAL(info) << "Point: default constructor";
  }
  // Valued constructor with deep copy
  Point(const T& x, const T& y, const T& z) {
    BOOST_LOG_TRIVIAL(info) << "Point: normal constructor (const T&, const T&, const T&)";
    this->coordPtr = std::make_shared<std::array<T,3>>();
    std::array<T,3>& coord = *this->coordPtr;
    coord[0] = x, coord[1] = y, coord[2] = z;
  }

  // Deep Copy constructor(ctor)
  template<typename U> Point(const Point<U>& point) {
    BOOST_LOG_TRIVIAL(info) << "Point: copy constructor";
    this->coordPtr = std::make_shared<std::array<T,3>>();
    std::array<T,3>& thisArray = *this->coordPtr;
    std::array<U,3>& thatArray = *point.coordPtr;
    std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
  }

  Point(const Point<T>& point) {
    BOOST_LOG_TRIVIAL(info) << "Point: deep copy constructor from non-const";
    if (point.coordPtr == nullptr) {
      BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in copy constructor";
      throw std::invalid_argument("Argument with nullptr");
    }
    this->coordPtr = std::make_shared<std::array<T,3>>();
    std::array<T,3>& thisArray = *this->coordPtr;
    std::array<T,3>& thatArray = *point.coordPtr;
    std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
  }

  // move constructor
  Point(const Point<T>&& point) {
    BOOST_LOG_TRIVIAL(info) << "Point: move constructor";
    if (point.coordPtr == nullptr) {
      BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in move constructor";
      throw std::invalid_argument("Argument with nullptr");
    }
    this->coordPtr = point.coordPtr;
  }

  // dtor
  ~Point() {
    BOOST_LOG_TRIVIAL(info) << "Point: destructor";
    //delete this->coordPtr;
  }

  inline T x(void) const { return (*this->coordPtr)[0]; }
  inline T y(void) const { return (*this->coordPtr)[1]; }
  inline T z(void) const { return (*this->coordPtr)[2]; }
  //inline T getX(void) const { return (*this->coordPtr)[0]; }
  //inline T getY(void) const { return (*this->coordPtr)[1]; }
  //inline T getZ(void) const { return (*this->coordPtr)[2]; }
  inline void setXYZ(const T& x, const T& y, const T& z) {
    BOOST_LOG_TRIVIAL(info) << "Point: setXYZ(const T&, const T&, const T&)";
    /*
    if (this->coordPtr == nullptr) {
      BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in setXYZ";
      throw std::invalid_argument("Argument with nullptr");
    }
    */
    std::array<T,3>& coord = *this->coordPtr;
    coord[0] = x, coord[1] = y, coord[2] = z;
  }
  
  inline int use_count() const { return this->coordPtr.use_count(); }

  // Deep copy assignment
  /*
  template<typename U> Point<T>& operator =(Point<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: Deep copy assignment from non-const";
    if (this != &rhs) {
      if (this->coordPtr == nullptr or rhs.coordPtr == nullptr) {
	BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in deep copy assignment";
	throw std::runtime_error("Faulty reference to nullptr in =@Point<>");
      }
      std::array<T,3>& thisArray = *this->coordPtr;
      std::array<U,3>& thatArray = *rhs.coordPtr;
      std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
    }
    return *this;
  }
  */
  
  template<typename U> Point<T>& operator =(const Point<U>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: copy assignment";
    if (this != &rhs) {
      /*
      if (this->coordPtr == nullptr or rhs.coordPtr == nullptr) {
	BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in deep copy assignment";
	throw std::invalid_argument("Faulty reference to nullptr in =@Point<>");
      }
      */
      std::array<T,3>& thisArray = *this->coordPtr;
      std::array<U,3>& thatArray = *rhs.coordPtr;
      std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
    }
    return *this;
  }

  Point<T>& operator =(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: copy assignment";
    if (this != &rhs) {
      /*
      if (this->coordPtr == nullptr or rhs.coordPtr == nullptr) {
	BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in deep copy assignment";
	throw std::invalid_argument("Faulty reference to nullptr in =@Point<>");
      }
      */
      std::array<T,3>& thisArray = *this->coordPtr;
      std::array<T,3>& thatArray = *rhs.coordPtr;
      std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
    }
    return *this;
  }
  
  // Move assignment
  //Point<T>& operator=(Point<T>&& rhs) = default;
  Point<T>& operator =(const Point<T>&& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: move assignment";
    if (this != &rhs) this->coordPtr = rhs.coordPtr;
    return *this;
  }

  template<typename U> bool operator ==(const Point<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator ==(const Point<U>& )";
    std::array<T,3>& p = *this->coordPtr;
    std::array<U,3>& q = *rhs.coordPtr;
    return p[0] == q[0] && p[1] == q[1] && p[2] == q[2];
  }

  template<typename U> bool operator !=(const Point<U>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator !=(const Point<U>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<U,3>& q = *rhs.coordPtr;
    return p[0] != q[0] || p[1] != q[1] || p[2] != q[2];
  }

  Point<T> operator +(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator +(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    return Point<T>(p[0]+q[0], p[1]+q[1], p[2]+q[2]);
  }

  Point<T> operator -(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator -(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    return Point<T>(p[0]-q[0], p[1]-q[1], p[2]-q[2]);
  }

  Point<T>& operator +=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator +=(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    p[0] += q[0], p[1] += q[1], p[2] += q[2];
    return *this;
  }

  Point<T>& operator -=(const Point<T>& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator -=(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    p[0] -= q[0], p[1] -= q[1], p[2] -= q[2];
    return *this;
  }

  Point<T> xProduct(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: xProduct(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    return Point<T>(p[1]*q[2] - p[2]*q[1], p[2]*q[0] - p[0]*q[2], p[0]*q[1] + p[1]*q[0]);
  }

  double dotProduct(const Point<T>& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: dotProduct(const Point<T>&)";
    std::array<T,3>& p = *this->coordPtr;
    std::array<T,3>& q = *rhs.coordPtr;
    return static_cast<double>(p[0]*q[0] + p[1]*q[1] + p[2]*q[2]);
  }
  
  // Operator override for scalar
  Point<T> operator +(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator +(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    return Point<T>(p[0]+rhs, p[1]+rhs, p[2]+rhs);
  }

  Point<T> operator -(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator -(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    return Point<T>(p[0]-rhs, p[1]-rhs, p[2]-rhs);
  }
  
  Point<T> operator *(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator *(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    return Point<T>(p[0]*rhs, p[1]*rhs, p[2]*rhs);
  }

  Point<T> operator /(const T& rhs) const {
    BOOST_LOG_TRIVIAL(info) << "Point: operator /(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    return Point<T>(p[0]/rhs, p[1]/rhs, p[2]/rhs);
  }

  Point<T>& operator +=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator +=(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    p[0] += rhs, p[1] += rhs, p[2] += rhs;
    return *this;
  }

  Point<T>& operator -=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator -=(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    p[0] -= rhs, p[1] -= rhs, p[2] -= rhs;
    return *this;
  }

  Point<T>& operator *=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator *=(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    p[0] *= rhs, p[1] *= rhs, p[2] *= rhs;
    return *this;
  }

  Point<T>& operator /=(const T& rhs) {
    BOOST_LOG_TRIVIAL(info) << "Point: operator /=(const T&)";
    std::array<T,3>& p = *this->coordPtr;
    p[0] /= rhs, p[1] /= rhs, p[2] /= rhs;
    return *this;
  }
  
  T& operator [](int index) { return (*this->coordPtr)[index]; } // In the case of "Point<T> point"

  T operator [](int index) const { return (*this->coordPtr)[index]; } // In the case of "const Point<T> point"

  inline void reallocate(void) { this->coordPtr = std::make_shared<std::array<T,3>>(); }
  inline bool isAllocated(void) const { return this->coordPtr != nullptr; }
  inline bool isNotAllocated(void) const { return this->coordPtr == nullptr; }

  inline std::ostream& dump(std::ostream& os) const {
    os << "Point: (" << this->x() << ", " << this->y() << ", " << this->z() << "), use_count(" << this->use_count() << ")";
    return os;
  }

protected:
  std::shared_ptr<std::array<T,3>> coordPtr;
private:
  inline void shallowCopy(const Point<T>& point) { this->coordPtr = point.coordPtr; }
  template<typename U> void deepCopy(const Point<U>& point) {
    if (this->coordPtr == nullptr or point.coordPtr == nullptr) {
      BOOST_LOG_TRIVIAL(error) << "Point: Faulty reference to nullptr in deepCopy";
      throw std::runtime_error("Faulty reference to nullptr in deepCopy@Point<>");
    }
    std::array<T,3>& thisArray = *this->coordPtr;
    std::array<U,3>& thatArray = *point.coordPtr;
    std::copy(std::begin(thatArray), std::end(thatArray), std::begin(thisArray));
  }
};

template<typename T> std::ostream& operator <<(std::ostream& os, const Point<T>& point)
{
  point.dump(os);
  return os;
}

template<typename T, typename U> double getDistance(const Point<T>& a, const Point<U>& b)
{
  BOOST_LOG_TRIVIAL(info) << "getDistance: ";
  double dx = a[0] - b[0];
  double dy = a[1] - b[1];
  double dz = a[2] - b[2];
  return std::sqrt(dx*dx + dy*dy + dz*dz);
}
