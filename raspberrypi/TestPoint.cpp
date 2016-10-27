#include "Point.h"
#include "sstream"
using namespace std;


int main(int argc, char const *argv[]) {
  //Test the constructor
  Point *test = new Point(5,4);
  cout <<"x should be 5, y should be 4"<< *test << std::endl;

  //Test the set methods
  test->setX(6);
  test->setY(9);

  //Test the stream out method
  cout <<"x should be 5, y should be 4"<< *test << std::endl;

  //test  the get methods
  cout <<"x should be 6"<< test->getX() << std::endl;
  cout <<"y should be 9"<< test->getY() << std::endl;

  //Test the stream in mehtod
  Point *second = new Point(0,0);
  stringstream ss;
  ss <<  "{ \"x\" : 10 , \"y\" : 10 }";
  ss << std::endl;

  ss >> *second;
  cout <<"x should be 10: y should be 10"<< *second;

  // test to make sure we can stream from one point to another

  *second >> *test;
  coud <<"x should be 5, y should be 4"<< *test << std::endl;



  return 0;
}
