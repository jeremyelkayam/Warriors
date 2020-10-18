/*
  text_loader.hpp
  Purpose: Leverage the library tinyxml2 to store all of the game's constants 
           in a set of maps that can easily be accessed with functions.
  @author Jeremy Elkayam
 */

#include "text_loader.hpp"

TextLoader::TextLoader(){

  //cout<<"instantiating"<<endl;
  load_strings();
  //cout<<"got strings"<<endl;
  load_ints();
  //cout<<"got ints"<<endl;
  load_floats();
  //cout<<"got floats"<<endl;
  load_all_paths();
  
}

void TextLoader::load_strings(){
  XMLDocument doc;
  doc.LoadFile( "../assets/values/strings.xml" );
  XMLElement * root =  doc.FirstChildElement("strings");

  for(XMLElement* node = root->FirstChildElement("string"); node != nullptr; node= node->NextSiblingElement("string")) {
    string s(node->Attribute("id"));
    strings.insert({s, node -> Attribute("value")});
  }
}

void TextLoader::load_ints(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../assets/values/constants.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("constants")->FirstChildElement("ints");
  int int_value;

  for(tinyxml2::XMLElement* node = root->FirstChildElement("constant"); node != nullptr; node= node->NextSiblingElement("constant")) {
    string s(node->Attribute("id"));
    stringstream str_value;
    //converting the string value from xml to an int
    str_value << node -> Attribute("value");
    str_value >> int_value;
    ints.insert({s, int_value});
  }
}


void TextLoader::load_floats(){
  tinyxml2::XMLDocument doc;
  doc.LoadFile( "../assets/values/constants.xml" );
  tinyxml2::XMLElement * root =  doc.FirstChildElement("constants")->FirstChildElement("doubles");

  float float_value;

  for(tinyxml2::XMLElement* node = root->FirstChildElement("constant"); node != nullptr; node= node->NextSiblingElement("constant")) {
    string s(node->Attribute("id"));
    stringstream str_value;
    //converting the string value from xml to an double
    str_value << node -> Attribute("value");
    str_value >> float_value;

    floats.insert({s, float_value});
  }
}

void TextLoader::load_all_paths() {
  tinyxml2::XMLDocument doc;

  doc.LoadFile( "../assets/values/strings.xml" );

  tinyxml2::XMLElement * root =  doc.FirstChildElement("strings")->FirstChildElement("paths");

  for(tinyxml2::XMLElement* node = root->FirstChildElement("string"); node != nullptr; node= node->NextSiblingElement("string")) {
    //cout << "attribute: " << node->Attribute("id") << endl;

    string s(node->Attribute("id"));


    if(node -> Attribute("type") == string("texture")){
      tex_paths.insert({s, node -> Attribute("value")});
    }else if(node->Attribute("type") == string("sound")){
      sound_paths.insert({s, node -> Attribute("value")});
    }else throw logic_error("the paths section of strings.xml does not contain a valid path type.");

  }
}


std::string TextLoader::get_string(const std::string id){
  if(strings.find(id) == strings.end()) throw invalid_argument("String with ID "+id+" does not exist.");
  return strings.at(id);
}

int TextLoader::get_integer(const std::string id){
  if(ints.find(id) == ints.end()) throw invalid_argument("Integer with ID "+id+" does not exist.");
  return ints.at(id);
}


float TextLoader::get_float(const std::string id){
  if(floats.find(id) == floats.end()) throw invalid_argument("Floating-point number with ID "+id+" does not exist.");
  return floats.at(id);
}

