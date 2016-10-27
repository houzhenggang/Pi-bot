#include "Point.h"
#include "sstream"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch/catch.hpp"


using namespace std;

TEST_CASE( "Point object", "test methods" ) {
  //Test the constructor
  Point *test = new Point(5,4);
  //test get
  REQUIRE( test->getX() == 5 );
  REQUIRE( test->getY() == 4 );
  //test set
  //Test the set methods
  test->setX(6);
  test->setY(9);
  REQUIRE( test->getX() == 6 );
  REQUIRE( test->getY() == 9 );

  //test the stream out method
  std::stringstream sstream;
  Json::Value root;
  sstream << *test;
  sstream >> root;

  REQUIRE(root.get("x","0") == 6 );
  REQUIRE(root.get("y","0") == 9 );

  //Test the stream in mehtod
  root.clear();
  Point *second = new Point(0,0);
  stringstream ss;
  ss <<  "{ \"x\" : 10 , \"y\" : 10 }";
  ss << std::endl;

  ss >> *second;

  ss << *second;

  ss >> root;
  REQUIRE(root.get("x","0") == 10 );
  REQUIRE(root.get("y","0") == 10 );

  //test serialisation in jason
  *test << *second;

  REQUIRE( test->getX() == 10 );
  REQUIRE( test->getY() == 10 );

}
