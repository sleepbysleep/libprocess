#include "geometry.hpp"

void testPointClass(void)
{
  std::cout << "Point<int> aPoint(1,1,1);" << std::endl;
  Point<int> aPoint(1,1,1);
  std::cout << aPoint <<std::endl;

  std::cout << "Point<int> bPoint = Point<int>(2,2,2);" << std::endl;
  Point<int> bPoint = Point<int>(2,2,2);
  std::cout << bPoint << std::endl;

  std::cout << "Point<int> cPoint = {3,3,3};" << std::endl;
  Point<int> cPoint = {3,3,3};
  std::cout << cPoint << std::endl;

  std::cout << "Point<int> dPoint = cPoint+aPoint;" << std::endl;
  Point<int> dPoint = cPoint+aPoint;
  std::cout << dPoint << std::endl;

  std::cout << "Point<int> ePoint = std::move(cPoint);" << std::endl;
  Point<int> ePoint = std::move(cPoint);
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = std::move(cPoint);" << std::endl;
  ePoint = std::move(cPoint);
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint;" << std::endl;
  ePoint = cPoint;
  std::cout << ePoint << std::endl;
  
  std::cout << "ePoint = cPoint+dPoint;" << std::endl;
  ePoint = cPoint+dPoint;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint-dPoint;" << std::endl;
  ePoint = cPoint-dPoint;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint+1;" << std::endl;
  ePoint = cPoint+1;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint-1;" << std::endl;
  ePoint = cPoint-1;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint*11;" << std::endl;
  ePoint = cPoint*11;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint/1;" << std::endl;
  ePoint = cPoint/1;
  std::cout << ePoint << std::endl;

  std::cout << "ePoint = cPoint.xProduct(dPoint);" << std::endl;
  ePoint = cPoint.xProduct(dPoint);
  std::cout << ePoint << std::endl;

  std::cout << "cPoint.dotProduct(dPoint);" << cPoint.dotProduct(dPoint) << std::endl;
  
  std::cout << "getDistance(aPoint, cPoint): " << getDistance(aPoint, cPoint) << std::endl;
}

void testLineClass(void)
{
  std::cout << "aLine:" << std::endl;
  Line<int> aLine(0,0,0, 1,1,1);
  std::cout << aLine << std::endl;

  std::cout << "aPoint(0,0,0);" << std::endl;
  Point<int> aPoint(0,0,0);
  std::cout << aPoint << std::endl;

  std::cout << "bPoint(1,1,1);" << std::endl;
  Point<int> bPoint(1,1,1);
  std::cout << bPoint << std::endl;
  
  std::cout << "bLine(aPoint, bPoint);" << std::endl;
  Line<int> bLine(aPoint, bPoint);
  std::cout << bLine << std::endl;

  std::cout << "cLine(std::move(aPoint), std::move(bPoint));" << std::endl;
  Line<int> cLine(std::move(aPoint), std::move(bPoint));
  std::cout << cLine << std::endl;

  std::cout << "dLine(aLine):" << std::endl;
  Line<int> dLine(aLine);
  std::cout << dLine << std::endl;

  std::cout << "eLine(std::move(aLine));" << std::endl;
  Line<int> eLine(std::move(aLine));
  std::cout << eLine << std::endl;

  std::cout << "Line<int> fLine = eLine + aPoint" << std::endl;
  Line<int> fLine = eLine + aPoint;
  std::cout << fLine << std::endl;
  
  std::cout << "cLine == dLine" << std::endl;
  std::cout << (cLine == dLine) << std::endl;

  std::cout << "eLine != cLine" << std::endl;
  std::cout << (eLine != cLine) << std::endl;

  std::cout << "eLine += bPoint" << std::endl;
  eLine += bPoint;
  std::cout << eLine << std::endl;

  std::cout << "dLine = eLine - bPoint" << std::endl;
  dLine = eLine - bPoint;
  std::cout << dLine << std::endl;
}  

void testCircleClass(void)
{
  std::cout << "aCircle(0,0,0,1)" << std::endl;
  Circle<int> aCircle(0,0,0,1);
  std::cout << aCircle << std::endl;

  std::cout << "aPoint(1,2,3)" << std::endl;
  Point<int> aPoint(1,2,3);
  std::cout << aPoint << std::endl;
  
  std::cout << "bCircle(aPoint, 1)" << std::endl;
  Circle<int> bCircle(aPoint, 1);
  std::cout << bCircle << std::endl;

  std::cout << "cCircle(std::move(aPoint), 1)" << std::endl;
  Circle<int> cCircle(std::move(aPoint), 1);
  std::cout << cCircle << std::endl;

  std::cout << "dCircle(aCircle)" << std::endl;
  Circle<int> dCircle(aCircle);
  std::cout << dCircle << std::endl;

  std::cout << "eCircle(std::move(aCircle))" << std::endl;
  Circle<int> eCircle(std::move(aCircle));
  std::cout << eCircle << std::endl;
}
