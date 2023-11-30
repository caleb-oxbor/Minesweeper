#pragma once
#include "tile.h"

struct Board {
	int cols;
	int rows;
	int num_bombs;
	bool debug_mode;
	vector<vector<Tile>> tiles;

	Board(int cols, int rows, int num_bombs);

	void board_draw(sf::RenderWindow& window);

	void assign_neighbors();

	void board_clear();

	void place_mines();

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



}

void Board::board_draw(sf::RenderWindow& window) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tiles[i][j].tile_draw(window, debug_mode);
		}
	}
}

void Board::assign_neighbors() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (tiles[i][j].neighbors[0] != nullptr)
				tiles[i][j].neighbors[0] = &tiles[i - 1][j - 1];
			if (tiles[i][j].neighbors[1] != nullptr)
				tiles[i][j].neighbors[1] = &tiles[i - 1][j];
			if (tiles[i][j].neighbors[2] != nullptr)
				tiles[i][j].neighbors[2] = &tiles[i - 1][j + 1];
			if (tiles[i][j].neighbors[3] != nullptr)
				tiles[i][j].neighbors[3] = &tiles[i][j - 1];
			if (tiles[i][j].neighbors[4] != nullptr)
				tiles[i][j].neighbors[4] = &tiles[i][j + 1];
			if (tiles[i][j].neighbors[5] != nullptr)
				tiles[i][j].neighbors[5] = &tiles[i + 1][j - 1];
			if (tiles[i][j].neighbors[6] != nullptr)
				tiles[i][j].neighbors[6] = &tiles[i + 1][j];
			if (tiles[i][j].neighbors[7] != nullptr)
				tiles[i][j].neighbors[7] = &tiles[i + 1][j + 1];

			tiles[i][j].neighbor_bombs = 0;
			for (int k = 0; k < 8; k++) {
				if (tiles[i][j].neighbors[k] != nullptr) {
					if (tiles[i][j].neighbors[k]->has_mine) {
						tiles[i][j].neighbor_bombs++;
					}

				}
			}
			// set the tile sprite to display_num
		}
	}
}

void Board::board_clear() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tiles[i][j].has_mine = false;
		}
	}
}

void Board::place_mines() {
	srand(static_cast<unsigned int>(time(nullptr)));
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