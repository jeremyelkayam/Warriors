//
// Created by jeremyelkayam on 9/29/20.
//

#pragma once

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <cassert>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "text_loader.hpp"

using std::string;
using std::unordered_map;
using std::vector;
using std::pair;
using std::map;

class ResourceManager {
private:

TextLoader &text_loader;

  unordered_map<string, sf::Texture> textures;
  unordered_map<string, sf::SoundBuffer> sound_buffers;

  vector<sf::Font> fonts;
  unsigned int font_index;

  //for later
  unordered_map<string, vector<sf::Texture>> animations;

  void load_textures(unordered_map<string, string> &paths);

  void load_sounds(unordered_map<string, string> &paths);

public:
  explicit ResourceManager(TextLoader &text_loader);

  sf::Texture &get_texture(string id);

  sf::SoundBuffer &get_sound_buffer(string id);

  sf::Font &get_font() {return fonts.at(font_index);}

  void move_font(bool forward);

  int get_font_size();

};
