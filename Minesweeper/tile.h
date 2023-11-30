#pragma once
#include "TextureManager.h"
#include <vector>
#include <iostream>
#include <cstdlib>
using namespace std;

struct Tile {
	sf::Sprite tile_sprite;
	sf::Sprite flag_sprite;
	sf::Sprite mine_sprite;
	bool hidden;
	bool has_mine;
	bool flagged;
	int x_index;
	int y_index;
	Tile* neighbors[8];
	int neighbor_bombs;
	sf::FloatRect rect;

	Tile(int col, int row, int total_cols, int total_rows, sf::Texture& tile, sf::Texture& flag, sf::Texture& mine);

	

	void draw_tile(sf::RenderWindow& window) {
		window.draw(tile_sprite);
		if (flagged)
			window.draw(flag_sprite);
	}



	void toggle_flag(sf::Texture& flag, sf::Texture& no_flag) {
		if (hidden)
			flagged = !flagged;
	}

};

Tile::Tile(int col, int row, int total_cols, int total_rows, sf::Texture& tile, sf::Texture& flag, sf::Texture& mine) {
	tile_sprite.setTexture(tile);
	flag_sprite.setTexture(flag);
	mine_sprite.setTexture(mine);
	hidden = true;
	has_mine = false;
	flagged = false;
	x_index = col;
	y_index = row;

	// adjust sprite position based on index
	tile_sprite.setPosition(32 * col, 32 * row);
	flag_sprite.setPosition(32 * col, 32 * row);
	mine_sprite.setPosition(32 * col, 32 * row);
	rect = tile_sprite.getLocalBounds();

	if (col == 0) {
		neighbors[0] = nullptr;
		neighbors[3] = nullptr;
		neighbors[5] = nullptr;
	}
	else if (col == total_cols) {
		neighbors[2] = nullptr;
		neighbors[4] = nullptr;
		neighbors[7] = nullptr;
	}
}


