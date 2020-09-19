/*
 * color_grid.hpp
 * Purpose: Contain the Spectrum-imitating "color grid". The color grid is one eighth the height and
 *          width of the screen and holds one color per cell at a time. This is to imitate the
 *          Spectrum's "attribute clash", which was caused by the console's ability to only display
 *          two colors at a time.
 *
 * @author Jeremy Elkayam
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "text_loader.hpp"

using std::shared_ptr;
using std::vector;

class ColorGrid {

private:

  shared_ptr<TextLoader>text_loader;

  //The color grid itself.
  vector<vector<sf::RectangleShape>>grid;

public:

  ColorGrid(shared_ptr<TextLoader> text_loader, float view_width, float view_height);

  /*
   * Reset the grid to all white. Should be called once every render loop.
   */
  void reset();

  /*
   * Paint in the grid squares of the given rectangle with the given color.
   */
  void update(float x, float y, int width, int height, sf::Color color);

  /*
   * Draw the colors. Should be called at the end of every render loop.
   */
  void draw(shared_ptr<sf::RenderWindow>window);

};


