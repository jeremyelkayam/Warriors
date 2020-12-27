//
// Created by jeremyelkayam on 9/30/20.
//

#include "end_screen.hpp"
EndScreen::EndScreen(TextLoader &a_text_loader, ResourceManager &a_resource_manager,
    InputManager &an_input_manager, vector<postmortem_info> dead_players_info, 
    game_options game_opts) :
        Screen(a_text_loader, a_resource_manager, an_input_manager),
        min_screen_time(a_text_loader.get_float("IDS_MIN_SCREEN_TIME")),
        opts(game_opts){

  screen_over = false;
  play_again = false;
  time_so_far = 0;

  sf::Text loss_text;

  resource_manager.setup_text(loss_text, a_text_loader.get_float("IDS_VIEW_X")/2, a_text_loader.get_float("IDS_VIEW_X")/10,
          a_text_loader.get_string("IDS_LOSS_TEXT"), true);

  screen_texts.emplace_back(loss_text);
  cout << "dead players:"  << dead_players_info.size() << endl;

  for(unsigned long i = 0 ; i < dead_players_info.size() ; ++i){
    screen_texts.emplace_back(sf::Text());
    //Let's get the number of digits BEFORE the decimal point
    unsigned long whole_digits = std::to_string((int)dead_players_info.at(i).age).length();

    string time_trunc = std::to_string(dead_players_info.at(i).age);

    time_trunc.resize(whole_digits + 2);

    resource_manager.setup_text(screen_texts.back(), a_text_loader.get_float("IDS_VIEW_X")/2,
            a_text_loader.get_float("IDS_VIEW_Y") * (i+1) / (dead_players_info.size() + 2) ,
            "Player "+std::to_string(i+1)+" lasted " + time_trunc + " seconds\nand killed "+
            std::to_string(dead_players_info.at(i).num_kills)+" enemies.", true);
  }
  
  screen_texts.emplace_back(sf::Text());

  resource_manager.setup_text(screen_texts.back(), a_text_loader.get_float("IDS_VIEW_X")/2,
            a_text_loader.get_float("IDS_VIEW_Y") * (dead_players_info.size()+1) / (dead_players_info.size() + 2) ,
            "Press 1 to play again with\n same options.\n\nPress 2 to return to main menu.", true);

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
  
  if(play_again)
    return unique_ptr<Screen>(new PlayingScreen(text_loader, resource_manager, 
        input_manager, opts));

  return unique_ptr<Screen>(new MainMenuScreen(text_loader, resource_manager, input_manager));
}

void EndScreen::handle_event(sf::Event &evt) {

  if(time_so_far > 2.f) {
    //if the mouse was clicked or a key was pressed, we can move on.
    play_again = evt.key.code == sf::Keyboard::Num1;

    screen_over = (evt.key.code == sf::Keyboard::Num1 || evt.key.code == sf::Keyboard::Num2);
  }
}

void EndScreen::update(float s_elapsed) {
  time_so_far += s_elapsed;
}