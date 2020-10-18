//
// Created by jeremyelkayam on 9/30/20.
//

#include "end_screen.hpp"
EndScreen::EndScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager, vector<postmortem_info> dead_players_info) :
        Screen(a_text_loader, a_resource_manager),
        min_screen_time(a_text_loader.get_float("IDS_MIN_SCREEN_TIME")){

  screen_over = false;
  time_so_far = 0;

  sf::Text loss_text;

  setup_text(loss_text, a_text_loader.get_float("IDS_VIEW_X")/2, a_text_loader.get_float("IDS_VIEW_X")/4,
          a_text_loader.get_string("IDS_LOSS_TEXT"), 1);

  screen_texts.emplace_back(loss_text);
  cout << "dead players:"  << dead_players_info.size() << endl;

  for(unsigned long i = 0 ; i < dead_players_info.size() ; ++i){
    screen_texts.emplace_back(sf::Text());
    //Let's get the number of digits BEFORE the decimal point
    unsigned long whole_digits = std::to_string((int)dead_players_info.at(i).age).length();

    string time_trunc = std::to_string(dead_players_info.at(i).age);

    time_trunc.resize(whole_digits + 2);

    setup_text(screen_texts.back(), a_text_loader.get_float("IDS_VIEW_X")/2,
            a_text_loader.get_float("IDS_VIEW_Y") * (i+1) / (dead_players_info.size() + 1) ,
            "Player "+std::to_string(i)+" lasted " + time_trunc + " seconds\nand killed "+
            std::to_string(dead_players_info.at(i).num_kills)+" enemies.", 1);
  }

  end_game_sound.setBuffer(a_resource_manager.get_sound_buffer("IDS_PATH_LOSE_MUSIC"));
  end_game_sound.play();

}

void EndScreen::draw(sf::RenderWindow &window, ColorGrid &color_grid) {
  for(const auto &text : screen_texts) {
    window.draw(text);
  }
}

bool EndScreen::go_to_next() {
  return screen_over;
}

unique_ptr<Screen> EndScreen::next_screen(){
  assert(go_to_next());
  end_game_sound.stop();
  return unique_ptr<Screen>(new TitleScreen(text_loader, resource_manager));
}

void EndScreen::handle_event(sf::Event &evt) {

  if(time_so_far > 2.f) {
    //if the mouse was clicked or a key was pressed, we can move on.
    screen_over = (evt.type == sf::Event::EventType::MouseButtonPressed ||
                   evt.type == sf::Event::EventType::KeyPressed);
  }
}

void EndScreen::update(float s_elapsed) {
  time_so_far += s_elapsed;
}


void EndScreen::setup_text(sf::Text &text, float xcor, float ycor, string content, int size_multiplier){
  text.setFont(resource_manager.get_font());
  text.setString(content);
  text.setCharacterSize((unsigned int)text_loader.get_integer("IDS_FONT_SIZE") * size_multiplier);
  sf::FloatRect textRect=text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width/2,
                 textRect.top + textRect.height/2);

  text.setPosition(xcor,ycor);
}