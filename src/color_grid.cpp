/*
 * color_grid.cpp
 * Purpose: Contain the Spectrum-imitating "color grid". The color grid is one eighth the height and
 *          width of the screen and holds one color per cell at a time. This is to imitate the
 *          Spectrum's "attribute clash", which was caused by the console's ability to only display
 *          two colors at a time.
 *
 * @author Jeremy Elkayam
 */

#include "color_grid.hpp"

ColorGrid::ColorGrid(int square_size, float view_width, float view_height) {
  this->square_size = square_size;

  //Populate the color grid. This is a grid of 8x8 squares with one color each.
  //The height of the array, the number of rows, should be
  for(int row=0;row<(((int)view_height)/square_size);row++){
    grid.emplace_back(
            vector<sf::RectangleShape>(
                    (unsigned long)view_width/square_size));
    //We have allocated the vector of RectangleShapes. Let's fill it up and initialize their
    //color (which will change) and position (which won't)
    for(int col=0;col<(((int)view_width)/square_size);col++){
      grid[row][col]=sf::RectangleShape(sf::Vector2f(square_size,square_size));
      //Because row corresponds to ycor and col is xcor, we have to do this. A bit weird, I know.
      grid[row][col].setPosition(square_size*col,square_size*row);

      //The reset() method should color them all in white for us, so we don't need to
      //do that here.
    }
  }

}

void ColorGrid::reset() {
  for(int row=0;row<grid.size();row++){
    for(int col=0;col<grid[row].size();col++){
      grid[row][col].setFillColor(sf::Color::White);
    }
  }
}

void ColorGrid::update(sf::FloatRect object_bounds, sf::Color color) {
  int paint_from_col = (int) object_bounds.left / square_size;
  int paint_from_row = (int) object_bounds.top / square_size;

  int how_many_cols = ceil(object_bounds.width / square_size);
  int how_many_rows = ceil(object_bounds.height / square_size);

  for (int row = paint_from_row; row <= paint_from_row + how_many_rows; row++) {
    if (row >= 0 && row < grid.size()) { //protect us from hitting nonexistent grid squares
      for (int col = paint_from_col; col <= paint_from_col + how_many_cols; col++) {
        if (col >= 0 && col < grid[row].size()) { //more protection
          //if we're sure we're hitting the a real square, let's paint.
          grid[row][col].setFillColor(color);
        }
      }
    }
  }
}


void ColorGrid::draw(sf::RenderWindow &window) {
  for(int row=0;row<grid.size();row++){
    for(int col=0;col<grid[row].size();col++){
      window.draw(grid[row][col],sf::BlendMultiply);
    }
  }
}