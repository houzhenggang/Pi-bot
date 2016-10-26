#include "Point.h"
using namespace std;

int main(int argc, char const *argv[]) {
  Point *test = new Point(5,4);
  cout << *test;
  test->setX(6);
  test->setY(9);
  cout << *test;

  Point *second = new Point(0,0);
  stringstream ss (stringstream::in | stringstream::out);
  ss <<  "{ x : 10 , y : 10 }";

  ss >> *second;
  cout << second;
  /* code */
  return 0;
}
