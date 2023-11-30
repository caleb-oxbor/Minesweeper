#pragma once
#include "tile.h"

struct Board {
	int cols;
	int rows;
	int num_bombs;
	bool debug_mode;
	vector<vector<Tile>> tiles;

	Board(int cols, int rows, int num_bombs);



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

Board::Board(int cols, int rows, int num_bombs) {
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