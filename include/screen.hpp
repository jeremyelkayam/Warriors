//
// Created by jeremyelkayam on 9/28/20.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "color_grid.hpp"
#include "resource_manager.hpp"
#include "input_manager.hpp"

using std::unique_ptr;

struct game_options{
  unsigned int num_players;
};

class Screen {

protected:

  TextLoader &text_loader;
  ResourceManager &resource_manager;
  InputManager &input_manager;

public:
/**
 * Constructor for the Screen class. Sets up references to the text loader and
 * resource manager.
 */
  Screen(TextLoader &a_text_loader, ResourceManager &a_resource_manager, 
      InputManager& an_input_manager);

/**
 * Destructor for the Screen class. Frees up any resources that might've been used.
 * Mostly in here so that you can override it if necessary
 */
  virtual ~Screen();

/**
 * Draw the screen's components to the given RenderWindow and ColorGrid
 */
  virtual void draw(sf::RenderWindow &window, ColorGrid &color_grid) = 0;

/**
 * Perform any logic the Screen needs to do.
 * 
 * @param s_elapsed the amount of time elapsed, in seconds, since the last time
 *                  this function was called.
 */
  virtual void update(float s_elapsed){};

/**
 * Says whether it's time to go to the next screen.
 * 
 * @return true if the screen has determined that it's over and that going to the next
 *         screen is possible. False otherwise.
 */
  virtual bool go_to_next() = 0;

/**
 * Provides the next screen.
 * 
 * @return a unique_ptr to whatever screen this screen has determined as its next target
 */
  virtual unique_ptr<Screen> next_screen() = 0;

/**
 * Handles keyboard events
 */
  virtual void handle_event(sf::Event &evt){};
};