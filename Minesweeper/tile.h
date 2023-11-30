#pragma once
#include <SFML/Graphics.hpp>
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

	Tile(int col, int row, int total_cols, int total_rows, sf::Texture& tile, sf::Texture& flag, sf::Texture& mine) {
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



struct Board {
	int cols;
	int rows;
	int num_bombs;
	bool debug_mode;
	vector<vector<Tile>> tiles;

	Board(int cols, int rows, int num_bombs) {
		this->cols = cols;
		this->rows = rows;
		this->num_bombs = num_bombs;
		debug_mode = false;

		// generate board with appropriate dimensions

		for (int i = 0; i < rows; i++) {
			vector<Tile> v;
			tiles.push_back(v);
			for (int j = 0; j < cols; j++) {
				tiles[i].push_back(Tile(j, i, cols, rows, TextureManager::getTexture("tile_hidden"),
				TextureManager::getTexture("flag"), TextureManager::getTexture("mine")));
			}
		}

		// sprinkle in the mines randomly
		srand(static_cast<unsigned int>(std::time(nullptr)));
		int mines_placed = 0;
		int rand_row;
		int rand_col;
		// FIXME: this will give runtime error if num_bombs > total tiles
		while (mines_placed < num_bombs) {
			rand_row = rand() % (rows - 1);
			rand_col = rand() % (cols - 1);

			if (!tiles[rand_row][rand_col].has_mine) {
				tiles[rand_row][rand_col].has_mine = true;
				mines_placed++;
			}

		}

	}

	void draw_board(sf::RenderWindow& window) {
		if (!debug_mode) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					tiles[i][j].draw_tile(window);
				}
			}
		}
		else {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					tiles[i][j].draw_tile(window);
					if (tiles[i][j].has_mine) {
						window.draw(tiles[i][j].mine_sprite);
					}
				}
			}
		}
	}



};

