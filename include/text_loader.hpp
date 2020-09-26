/*
  text_loader.hpp
  Purpose: Leverage the library tinyxml2 to store all of the game's constants 
           in a set of maps that can easily be accessed with functions.

  @author Jeremy Elkayam
 */

#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include "tinyxml2.h"

using std::string;
using std::unordered_map;
using std::stringstream;
using std::cout;
using std::endl;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;

class TextLoader {

private:

  //Maps storing values loaded in from XML files.
  unordered_map<string, string> strings;
  unordered_map<string, int> ints;
  unordered_map<string, double> doubles;

  /*
    Using tinyxml2, load in the appropriate values from an xml file and store them in
    an unordered map.
   */
  void load_strings();
  void load_ints();

  //todo: refactor into float
  void load_doubles();

public:

  /*
    Constructor for the TextLoader class. Retrieves data from the XML files and stores them in maps.
   */
  TextLoader();
  
  /*
    Retrieve a string constant.

    @param id: The unique identifier of the value as stored in strings.xml
   */
  string get_string(string id);

  /*
    Retrieve an integer constant.

    @param id: The unique identifier of the value as stored in values.xml
   */
  int get_integer(string id);

  /*
    Retrieve a double-precision floating-point constant.

    @param id: The unique identifier of the value as stored in values.xml
   */
  double get_double(string id);
};
