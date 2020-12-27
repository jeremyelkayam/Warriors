#include "menu_screen.hpp"

MenuScreen::MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
        InputManager &an_input_manager) :
Screen(a_text_loader, a_resource_manager, an_input_manager),
flash_interval(text_loader.get_float("IDS_MENU_FLASH_INTERVAL")) {

    resource_manager.setup_text(header, 10, 10,"WARRIORS GAME SELECTION");


    //todo: fix this because it sucks
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

    copyright.setTexture(resource_manager.get_texture("IDS_PATH_COPYRIGHT_TEX"));
    copyright.setPosition(8,180);
    resource_manager.setup_text(footer, 18, 180,"1987 J.N.E. ALL RIGHTS RESERVED");

    selected = 0;
    reset_selector();

    screen_over = false;
}

void MenuScreen::reset_selector(){
    sf::Text &seltext = options.at(selected);

    selector.setFillColor(sf::Color::Black);
    selector.setSize(sf::Vector2f(seltext.getLocalBounds().width,
                                  seltext.getLocalBounds().height - 1));
    selector.setPosition(seltext.getPosition().x, seltext.getPosition().y - 1);
}

void MenuScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid){
    window.draw(selector);
    for(auto &option : options){
        window.draw(option);
    }
    window.draw(header);
    window.draw(footer);
    window.draw(copyright);
}

bool MenuScreen::go_to_next(){
    return screen_over;
}

void MenuScreen::handle_event(sf::Event &evt){
    assert(selected < options.size());
    if(evt.type == sf::Event::KeyPressed){

        screen_over = (evt.key.code == sf::Keyboard::Return);
    
        //swap the colors of the rect and the shape
        if(flash_time > flash_interval / 2){
            options.at(selected).setFillColor(selector.getFillColor());
            selector.setFillColor(sf::Color::Black);
            flash_time = 0;
        }

        //move our menu position forward or backward depending
        if(evt.key.code == sf::Keyboard::Down){
            selected++;
        }else if(evt.key.code == sf::Keyboard::Up){
            selected--;
        }
        selected %= options.size();

        reset_selector();
    }
}

unique_ptr<Screen>MenuScreen:: next_screen(){
    if(!go_to_next()) throw logic_error("error: next_screen called before go_to_next");

    game_options opts;
    if(selected == 0){
        opts.num_players = 1;
        opts.epilepsy = true;
        return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager,
            input_manager, opts));
    }else if(selected == 2){
        return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager,
            input_manager, opts));
    }
}

void MenuScreen::update(float s_elapsed){
    flash_time += s_elapsed;


    // reset the timer if we went over
    if(flash_time > flash_interval){
        flash_time = 0;
        //swap the colors of the rect and the shape
        options.at(selected).setFillColor(selector.getFillColor());
        selector.setFillColor(sf::Color::Black);
    }

    //halfway through the interval, we swap the colors  
    if(flash_time > flash_interval / 2){
        //make sure we haven't swapped yet
        if(selector.getFillColor() == sf::Color::Black){
            //swap the colors
            selector.setFillColor(options.at(selected).getFillColor());
            options.at(selected).setFillColor(sf::Color::Black);
        }
    }
}