//
// Created by jeremyelkayam on 9/28/20.
//

#include "screen.hpp"

Screen::Screen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
        InputManager& an_input_manager) :
text_loader(a_text_loader),
resource_manager(a_resource_manager),
input_manager(an_input_manager) {

}

Screen::~Screen() {

}