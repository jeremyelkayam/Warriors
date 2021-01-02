#include "main_menu_screen.hpp"

MainMenuScreen::MainMenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
        InputManager &an_input_manager) :
MenuScreen(a_text_loader, a_resource_manager, an_input_manager) {
    resource_manager.setup_text(header, 10, 10,"WARRIORS GAME SELECTION");

    copyright.setTexture(resource_manager.get_texture("IDS_PATH_COPYRIGHT_TEX"));
    copyright.setPosition(8,180);
    
    resource_manager.setup_text(footer, 18, 180,"1987 J.N.E. ALL RIGHTS RESERVED");


   vector<pair<string,sf::Color>> optstrs = {
        { "1 QUICK 1P GAME", sf::Color::Red},
        { "2 GAME WITH OPTIONS", sf::Color::Magenta},
        { "3 KEY BINDINGS", sf::Color::Green},
        { "4 OTHER CRAP" , sf::Color::Cyan} };

    sf::Text quickstart;

    float ycor = 50;

    for(int i = 0 ; i < optstrs.size(); i++){
        resource_manager.setup_text(quickstart, 60, 50 + (30*i),optstrs[i].first);
            quickstart.setFillColor(optstrs[i].second);

        options.emplace_back(quickstart);
    }
    reset_selector();
}

void MainMenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    MenuScreen::draw(window, color_grid);
    window.draw(header);
    window.draw(footer);
    window.draw(copyright);
}

unique_ptr<Screen> MainMenuScreen::next_screen(){
    if(!go_to_next()) throw logic_error("error: next_screen called before go_to_next");

    game_options opts;
    if(selected == 0){
        opts.num_players = 1;
        opts.epilepsy = true;
        return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager,
            input_manager, opts));
    }else if(selected == 2){
        return unique_ptr<Screen>(new KeysMenuScreen(text_loader, resource_manager,
            input_manager));
    }
}

void MainMenuScreen::handle_event(sf::Event &evt){
    MenuScreen::handle_event(evt);

    if(evt.type == sf::Event::KeyPressed){
        screen_over = (evt.key.code == sf::Keyboard::Return);
    
    }
}