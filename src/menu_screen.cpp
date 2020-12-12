#include "menu_screen.hpp"

MenuScreen::MenuScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager) :
Screen(a_text_loader, a_resource_manager), flash_interval(text_loader.get_float("IDS_MENU_FLASH_INTERVAL")) {


    vector<string> optstrs = {"1 QUICK 1P GAME", "2 GAME WITH OPTIONS", "3 KEY BINDINGS", "4 OTHER CRAP"};

    sf::Text quickstart;
    quickstart.setFont(resource_manager.get_font());
    quickstart.setString("1 QUICK 1P GAME");
    quickstart.setCharacterSize((unsigned int)resource_manager.get_font_size());
    quickstart.setPosition(10,40);
    quickstart.setFillColor(sf::Color::Red);

    options.emplace_back(quickstart);

    quickstart.setString("2 PLACEHOLDER");
    quickstart.setPosition(10,80);
    quickstart.setFillColor(sf::Color::Magenta);

    options.emplace_back(quickstart);

    selected = 0;
    reset_selector();
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
    return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager, 1));
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