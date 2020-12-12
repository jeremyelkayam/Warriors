//
// Created by jeremyelkayam on 9/29/20.
//

#include "resource_manager.hpp"

sf::Texture &ResourceManager::get_texture(string id) {
  //cout << "id: " << id << endl;
  if(textures.find(id) == textures.end()) throw invalid_argument("Texture with ID "+id+" does not exist.");
  return textures.at(id);
}

sf::SoundBuffer &ResourceManager::get_sound_buffer(string id) {
  //cout << "id: " << id << endl;
  if(sound_buffers.find(id) == sound_buffers.end()) throw invalid_argument("Sound with ID "+id+" does not exist.");
  return sound_buffers.at(id);
}

ResourceManager::ResourceManager(TextLoader &a_text_loader) : text_loader(a_text_loader) {

  load_textures(text_loader.get_all_texture_paths());
  load_sounds(text_loader.get_all_sound_paths());

  for(int z = 0; z < text_loader.get_integer("IDS_NUM_PIXEL_FONTS") ; z++){
    sf::Font default_font;
    default_font.loadFromFile(text_loader.get_string("IDS_PATH_FONT_" + std::to_string(z)));

    // tHIS IS TERRIBLE! BUT I GUESS THE CURRENT VERSION OF SFML DOESN'T HAVE A GOOD WAY TO SET THE SMOOTHING OFF ON
    // THE TEXTURE.
    auto& texture = const_cast<sf::Texture&>(default_font.getTexture((unsigned int)text_loader.get_integer("IDS_FONT_SIZE_" + std::to_string(z))));
    texture.setSmooth(false);
    fonts.emplace_back(default_font);
  }

  // sf::Font readable_font;
  // readable_font.loadFromFile(text_loader.get_string("IDS_PATH_READABLE_FONT"));
  // fonts.emplace_back(readable_font);
  font_index = 1;
}

void ResourceManager::load_textures(unordered_map<string, string> &paths) {
  //cout << texpaths.size() << endl;
  for (const auto &it : paths){
      sf::Texture tex;
      tex.loadFromFile(it.second);

      //cout << it.first << endl;

      textures.insert({it.first, tex});

  }
}

void ResourceManager::load_sounds(unordered_map<string, string> &paths) {
  //cout << texpaths.size() << endl;
  for (const auto &it : paths){
    sf::SoundBuffer buf;
    buf.loadFromFile(it.second);

    sound_buffers.insert({it.first, buf});

  }
}

void ResourceManager::move_font(bool forward){
  if(forward){
    font_index++;
  }else{
    font_index--;
  }
  //wrap around
  font_index %= fonts.size();
}

int ResourceManager::get_font_size(){
  return text_loader.get_integer("IDS_FONT_SIZE_" + std::to_string(font_index)); 
}