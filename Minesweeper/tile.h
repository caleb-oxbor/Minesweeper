#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include <iostream>
using namespace std;

struct Tile {
	sf::Sprite tile_sprite;
	sf::Sprite flag_sprite;
	bool hidden;
	bool has_mine;
	bool flagged;
	int x_index;
	int y_index;
	Tile* neighbors[8];
	int neighbor_bombs;
	sf::FloatRect rect;

	Tile(int col, int row, int total_cols, int total_rows, sf::Texture& tile, sf::Texture& flag) {
		tile_sprite.setTexture(tile);
		flag_sprite.setTexture(flag);
		hidden = true;
		has_mine = false;
		flagged = false;
		x_index = col;
		y_index = row;

		// adjust sprite position based on index
		tile_sprite.setPosition(32 * col, 32 * row);
		flag_sprite.setPosition(32 * col, 32 * row);
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

	void draw_tile(sf::RenderWindow& window);



	void toggle_flag(sf::Texture& flag, sf::Texture& no_flag) {
		if (hidden)
			flagged = !flagged;
	}

};

void Tile::draw_tile(sf::RenderWindow& window) {
	window.draw(tile_sprite);
	if (flagged)
		window.draw(flag_sprite);
}

struct Board {
	int cols;
	int rows;
	int num_bombs;
	vector<vector<Tile>> tiles;

	Board(int cols, int rows, int num_bombs) {
		this->cols = cols;
		this->rows = rows;
		this->num_bombs = num_bombs;
		for (int i = 0; i < rows; i++) {
			vector<Tile> v;
			tiles.push_back(v);
			for (int j = 0; j < cols; j++) {
				tiles[i].push_back(Tile(j, i, cols, rows, TextureManager::getTexture("tile_hidden"), TextureManager::getTexture("flag")));
			}
		}
	}

	void draw_board(sf::RenderWindow& window);



};

void Board::draw_board(sf::RenderWindow& window) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			tiles[i][j].draw_tile(window);
		}
	}
}