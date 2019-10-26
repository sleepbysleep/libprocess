#include "geometry.hpp"

int main()
{
  //std::cout << "testPointClass()" << std::endl;
  //testPointClass();

  //std::cout << "testLineClass()" << std::endl;
  //testLineClass();

  //std::cout << "testCircleClass()" << std::endl;
  //testCircleClass();

  std::cout << "testTriangleClass()" << std::endl;

  std::cout << "aTriangle(0,0,0,1,1,1,2,2,2)" << std::endl;
  Triangle<int> aTriangle(0,0,0,1,1,1,2,2,2);
  std::cout << aTriangle << std::endl;

  std::cout << "aPoint(3,3,3)" << std::endl;
  Point<int> aPoint(3,3,3);
  std::cout << aPoint << std::endl;

  std::cout << "bPoint(4,4,4)" << std::endl;
  Point<int> bPoint = Point<int>(4,4,4);
  std::cout << bPoint << std::endl;

  std::cout << "cPoint(5,5,5)" << std::endl;
  Point<int> cPoint(5,5,5);
  std::cout << cPoint << std::endl;

  std::cout << "bTriangle(aPoint, bPoint, cPoint)" << std::endl;
  Triangle<int> bTriangle(aPoint, bPoint, cPoint);
  std::cout << bTriangle << std::endl;
  
  std::cout << "cTriangle(std::move(aPoint), std::move(bPoint), std::move(cPoint))" << std::endl;
  Triangle<int> cTriangle(std::move(aPoint), std::move(bPoint), std::move(cPoint));
  std::cout << cTriangle << std::endl;

  std::cout << "dTriangle(Point<int>(6,6,6), Point<int>(7,7,7), Point<int>(8,8,8))" << std::endl;
  Triangle<int> dTriangle(Point<int>(6,6,6), Point<int>(7,7,7), Point<int>(8,8,8));
  std::cout << dTriangle << std::endl;

  std::cout << "eTriangle(aTriangle);" << std::endl;
  Triangle<int> eTriangle(aTriangle);
  std::cout << eTriangle << std::endl;

  std::cout << "fTriangle(std::move(aTriangle));" << std::endl;
  Triangle<int> fTriangle(std::move(aTriangle));
  std::cout << fTriangle << std::endl;
  
  std::cout << "End..." << std::endl;
  
  /*
  std::cout << "Point<int> bPoint = Point<int>(2,2,2);" << std::endl;
  Point<int> bPoint = Point<int>(2,2,2);
  std::cout << bPoint << std::endl;

  std::cout << "Point<int> cPoint = {3,3,3};" << std::endl;
  Point<int> cPoint = {3,3,3};
  std::cout << cPoint << std::endl;

  std::cout << "Point<int> dPoint = cPoint;" << std::endl;
  Point<int> dPoint = cPoint;
  std::cout << "dPoint allocation: " << dPoint << std::endl;

  std::cout << "Point<int> ePoint = std::move(ePoint);" << std::endl;
  Point<int> ePoint = std::move(cPoint);
  std::cout << "ePoint: " << ePoint << std::endl;

  std::cout << "ePoint = std::move(ePoint);" << std::endl;
  ePoint = std::move(cPoint);
  std::cout << "ePoint: " << ePoint << std::endl;
  */
  return 0;
}
