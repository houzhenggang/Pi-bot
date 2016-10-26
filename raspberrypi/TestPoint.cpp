#include "Point.h"

int main(int argc, char const *argv[]) {
  Point *test = new Point(5,4);
  cout << *test;
  test->setX(6);
  test->setY(9);
  cout << *test;

  Point *second = new Point(0,0);
  "{ x : 10 , y : 10 }" >> *second;
  cout << second;
  /* code */
  return 0;
}
