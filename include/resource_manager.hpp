//
// Created by jeremyelkayam on 9/29/20.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cassert>
#include <SFML/Graphics.hpp>
#include "text_loader.hpp"

using std::string;
using std::unordered_map;
using std::vector;

class ResourceManager {
private:
  unordered_map<string, sf::Texture> textures;

  sf::Font font;

  //for later
  unordered_map<string, vector<sf::Texture>> animations;

  void load_textures(unordered_map<string,string> &texpaths);

public:
  explicit ResourceManager(TextLoader &text_loader);

  sf::Texture &get_texture(string id);

  sf::Font &get_font() {return font;}

};
