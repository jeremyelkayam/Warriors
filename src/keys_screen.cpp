#include "keys_screen.hpp"

KeysMenuScreen::KeysMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
                InputManager &an_input_manager) :
MenuScreen(a_text_loader, a_resource_manager, an_input_manager) {
    for(auto it : an_input_manager.get_bindings()){
        sf::Text opt;
        opt.setFillColor(sf::Color::White);
        a_resource_manager.setup_text(opt, 0, 0, it.first);
        options.emplace_back(opt);
    }
    update_scroll();
}

void KeysMenuScreen::reset_selector(){
    MenuScreen::reset_selector();
    sf::Text &seltext = options.at(selected);

    selector.setSize(sf::Vector2f(seltext.getLocalBounds().width,
                                  seltext.getLocalBounds().height));
}

void KeysMenuScreen::handle_event(sf::Event &evt){
    MenuScreen::handle_event(evt);
    if(evt.type == sf::Event::KeyPressed){
        if(selected < scroll_position){
            scroll_position = selected;
        }else if(selected >= scroll_position + opts_per_screen) {
            scroll_position = selected - opts_per_screen + 1;
            //scroll_position++;
            cout << "trigger" << endl;
        }
        update_scroll();
        cout << " scroll pos + opts per screen = " << scroll_position + opts_per_screen << endl;

        cout << "selected" << selected << endl;
        cout << "scroll pos " << scroll_position << endl;
    }
}

void KeysMenuScreen::update_scroll(){
    float min_y = 10;
    float max_y = 180;

    float interval = (max_y - min_y) / opts_per_screen;
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){

        string lol = options.at(i).getString();
        options.at(i).setPosition(options.at(i).getPosition().x,
            min_y + (i - scroll_position) * interval);
    }
    reset_selector();
}

void KeysMenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(int i = scroll_position; i < scroll_position + opts_per_screen ; i++){
        window.draw(options[i]);
    }

    if(scroll_position > 0 ) {
        window.draw(up_arrow);
    }

    if(scroll_position < options.size() - opts_per_screen){
        window.draw(down_arrow);
    }
}

unique_ptr<Screen> KeysMenuScreen::next_screen(){
  assert(go_to_next());
  return unique_ptr<MenuScreen>(new MainMenuScreen(text_loader, resource_manager, 
      input_manager));
}