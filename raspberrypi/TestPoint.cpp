#include "Point.h"

int main(int argc, char const *argv[]) {
  Point *test = new Point(5,4);
  cout << *test;
  test->setX(6);
  test->setY(9);
  cout << *test;

  Point *second = new Point(0,0);
  std::string str = "{ x : 10 , y : 10 }";
  std::istringstream in(str);
  in >> *second;
  cout << second;
  /* code */
  return 0;
}
