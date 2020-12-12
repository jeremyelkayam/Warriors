#include "menu_screen.hpp"

MenuScreen::MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
Screen(a_text_loader, a_resource_manager) {
    
}

void MenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    
}

bool MenuScreen::go_to_next(){
    return false;
}

void MenuScreen::handle_event(sf::Event &evt){

}

unique_ptr<Screen>MenuScreen:: next_screen(){
    if(!go_to_next()) throw logic_error("error: next_screen called before go_to_next");
    return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager, 1));
}