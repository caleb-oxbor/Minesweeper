#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include <iostream>
using namespace std;

struct Tile {
	sf::Sprite tile_sprite;
	bool hidden;
	bool has_mine;
	int x_index;
	int y_index;
	Tile* neighbors[8];
	int neighbor_bombs;

	Tile(int col, int row, int total_cols, int total_rows, sf::Texture& image) {
		tile_sprite.setTexture(image);
		hidden = true;
		has_mine = false;
		x_index = col;
		y_index = row;

		// adjust sprite position based on index
		tile_sprite.setPosition(32 * col, 32 * row);
		// determine neighbors, nullptr if on edge

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

};

struct Board {
	int cols;
	int rows;
	int num_bombs;
	vector<vector<Tile>> tiles;

	Board(int cols, int rows, int num_bombs) {
		for (int i = 0; i < rows; i++) {
			vector<Tile> v;
			tiles.push_back(v);
			for (int j = 0; j < cols; j++) {
				tiles[i].push_back(Tile(j, i, cols, rows, TextureManager::getTexture("tile_hidden")));
			}
		}
	}

};