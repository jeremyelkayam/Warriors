//
// Created by jeremyelkayam on 9/29/20.
//

#include "resource_manager.hpp"

sf::Texture &ResourceManager::get_texture(string id) {
  //cout << "id: " << id << endl;
  assert(textures.find(id) != textures.end());
  return textures.at(id);
}

ResourceManager::ResourceManager(TextLoader &text_loader) {

  load_textures(text_loader.get_all_paths());

  font.loadFromFile(text_loader.get_string("IDS_PATH_FONT"));

  //tHIS IS TERRIBLE! BUT I GUESS SFML DOESN'T HAVE A GOOD WAY TO SET THE SMOOTHING OFF ON THE TEXTURE.
  auto& texture = const_cast<sf::Texture&>(font.getTexture((unsigned int)text_loader.get_integer("IDS_FONT_SIZE")));
  texture.setSmooth(false);

}

void ResourceManager::load_textures(unordered_map<string, string> &texpaths) {
  cout << texpaths.size() << endl;
  for (auto it : texpaths){
    sf::Texture tex;
    tex.loadFromFile(it.second);

    cout << it.first << endl;

    textures.insert({it.first, tex});
  }
}