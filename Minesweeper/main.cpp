#include "board.h"
#include <string>
#include <fstream>
using namespace std;


int main() {

	int cols;
	int rows;
	int num_mines;

	// Read in the number of rows and cols from cfg file
	ifstream cFile("board_config.cfg");
	if (cFile.is_open()) {
		string token;
		getline(cFile, token);
		cols = stoi(token);
		getline(cFile, token);
		rows = stoi(token);
		getline(cFile, token);
		num_mines = stoi(token);
	}


	// Render window object with dimensions based on number of rows and cols
	sf::RenderWindow welcomeWindow(sf::VideoMode(cols * 32, (rows * 32) + 100), "Welcome Window", sf::Style::Close);
	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		std::cout << "can't load :(" << std::endl;
		return 0;
	}

	// Welcome message
	sf::Text welcomeText("WELCOME TO MINESWEEPER!", font, 24);
	welcomeText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	welcomeText.setFillColor(sf::Color::White);
	sf::FloatRect welcomeTextRect = welcomeText.getLocalBounds();
	welcomeText.setOrigin(welcomeTextRect.left + welcomeTextRect.width / 2.0f, welcomeTextRect.top + welcomeTextRect.height / 2.0f);
	welcomeText.setPosition(sf::Vector2f((cols * 32) / 2, (((rows * 32) + 100) / 2) - 150));

	// "Enter name" prompt
	sf::Text namePrompt("Enter your name:", font, 20);
	namePrompt.setStyle(sf::Text::Bold);
	namePrompt.setFillColor(sf::Color::White);
	sf::FloatRect namePromptRect = namePrompt.getLocalBounds();
	
	namePrompt.setOrigin(namePromptRect.left + namePromptRect.width / 2.0f, namePromptRect.top + namePromptRect.height / 2.0f);
	namePrompt.setPosition(sf::Vector2f((cols * 32) / 2, (((rows * 32) + 100) / 2) - 75));

	// Username
	sf::Text userName("|", font, 20);
	userName.setStyle(sf::Text::Bold);
	userName.setFillColor(sf::Color::Yellow);
	sf::FloatRect userNameRect = userName.getLocalBounds();
	
	userName.setOrigin(userNameRect.left + userNameRect.width / 2.0f, userNameRect.top + userNameRect.height / 2.0f);
	userName.setPosition(sf::Vector2f((cols * 32) / 2, (((rows * 32) + 100) / 2) - 45));
	string name_str = "";

	while (welcomeWindow.isOpen()) {
			sf::Event event;
		while (welcomeWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed) { // Click X on the window
				welcomeWindow.close();
				return 0;
			}
			if (event.type == sf::Event::TextEntered) {
				// check if the key is a letter, accept lowercase and uppercase
				if ((event.text.unicode > 64 && event.text.unicode < 91) || (event.text.unicode > 96 && event.text.unicode < 123)) {
					if (name_str.size() == 0) {
						name_str += toupper(static_cast<char>(event.text.unicode));
					}
					else if (name_str.size() < 10) {
						name_str += tolower(static_cast<char>(event.text.unicode));
					}
					// add cursor and recenter
					userName.setString(name_str + '|');
					userNameRect = userName.getLocalBounds();
					userName.setOrigin(userNameRect.left + userNameRect.width / 2.0f, userNameRect.top + userNameRect.height / 2.0f);
					userName.setPosition(sf::Vector2f((cols * 32) / 2, (((rows * 32) + 100) / 2) - 45));
					welcomeWindow.draw(userName);
				}
			}
			if (event.type == sf::Event::KeyPressed) { // Getting user input
				if (event.key.code == sf::Keyboard::Enter && name_str.size() > 0) { // event.key.code == ASCII values
					welcomeWindow.close();
				}
				if (event.key.code == sf::Keyboard::Backspace) {
					if (name_str.size() > 0) {
						name_str = name_str.substr(0, name_str.size() - 1);

						userName.setString(name_str + '|');
						userNameRect = userName.getLocalBounds();
						userName.setOrigin(userNameRect.left + userNameRect.width / 2.0f, userNameRect.top + userNameRect.height / 2.0f);
						userName.setPosition(sf::Vector2f((cols * 32) / 2, (((rows * 32) + 100) / 2) - 45));
						welcomeWindow.draw(userName);
					}
				}

			}
		}
		welcomeWindow.clear(sf::Color::Blue); // Set background color
		welcomeWindow.draw(welcomeText); 
		welcomeWindow.draw(namePrompt);
		welcomeWindow.draw(userName);
		welcomeWindow.display();
	}

	

	/*sf::Text text("Welcome to SFML", font, 24);
	text.setFillColor(sf::Color::White); // White text
	sf::FloatRect textRect = text.getLocalBounds();
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
	text.setPosition(sf::Vector2f(800 / 2.0f, (600 / 2.0f) - 150));

	
	// Create rectangle object
	sf::RectangleShape rect1(sf::Vector2f(100, 100));
	rect1.setFillColor(sf::Color(255, 165, 0));
	rect1.setPosition(250, 250);
	// Create second rectangle object
	sf::RectangleShape rect2(sf::Vector2f(100, 100));
	rect2.setFillColor(sf::Color::Blue);
	rect2.setPosition(rect1.getPosition().x + 200, rect1.getPosition().y); // Getting relative position of the new rect
	*/

	// digit configuration, positions are not set
	sf::Texture& digit_pic = TextureManager::getTexture("digits");
	sf::Sprite digits[10];
	for (int i = 0; i < 10; i++) {
		digits[i].setTexture(digit_pic);
		digits[i].setTextureRect(sf::IntRect(21 * i, 0, 21, 32));
	}

	// game window

	sf::Texture& happyFaceTexture = TextureManager::getTexture("face_happy");
	sf::Sprite happyFaceSprite;
	happyFaceSprite.setTexture(happyFaceTexture);
	happyFaceSprite.setPosition(((cols/2.0f) * 32) - 32, (rows + 0.5) * 32);

	sf::Texture& debugTexture = TextureManager::getTexture("debug");
	sf::Sprite debugSprite;
	debugSprite.setTexture(debugTexture);
	debugSprite.setPosition((cols * 32) - 304, (rows + 0.5) * 32);

	sf::Texture& pauseTexture = TextureManager::getTexture("pause");
	sf::Texture& playTexture = TextureManager::getTexture("play");
	sf::Sprite pausePlaySprite;
	pausePlaySprite.setTexture(pauseTexture);
	pausePlaySprite.setPosition((cols * 32) - 240, (rows + 0.5) * 32);

	sf::Texture& leaderboardButtonTexture = TextureManager::getTexture("leaderboard");
	sf::Sprite leaderboardButtonSprite;
	leaderboardButtonSprite.setTexture(leaderboardButtonTexture);
	leaderboardButtonSprite.setPosition((cols * 32) - 176, (rows + 0.5) * 32);

	/*
	sf::Texture& pikachuTexture = TextureManager::getTexture("pikachu");
	sf::Sprite pikachuSprite;
	pikachuSprite.setTexture(pikachuTexture);
	pikachuSprite.setScale(0.25, 0.25);
	pikachuSprite.setOrigin(pikachuTexture.getSize().x / 2.0f,
		pokeballTexture.getSize().y / 2.0f);
	pikachuSprite.setPosition(pokeballSprite.getPosition().x,
		pokeballSprite.getPosition().y - 69);
	bool pikachuVisible = false;
	*/

	// generate board

	Board board = Board(cols, rows, num_mines);

	//make the game window based on number of rows and cols

	sf::RenderWindow window(sf::VideoMode(cols * 32, (rows * 32) + 100), "Minesweeper", sf::Style::Close);
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			// Event for when user clicks the mouse
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse; // 2-dimensional vector of floating point coordinates x, y
				mouse = sf::Mouse::getPosition(window); // Storing the values of where the event occurred in window
				auto translated_pos = window.mapPixelToCoords(mouse);
				std::cout << "Mouse button pressed at X: " << mouse.x;
				std::cout << " Y: " << mouse.y << std::endl;

				if (event.mouseButton.button == sf::Mouse::Right && mouse.y <= rows * 32) {
					board.tiles[mouse.y / 32][mouse.x / 32].toggle_flag(TextureManager::getTexture("flag"), TextureManager::getTexture("tile_hidden"));
					
				}
				if (event.mouseButton.button == sf::Mouse::Left) {
					//trying debug button first, seems fitting
					if (debugSprite.getGlobalBounds().contains(translated_pos)) {
						cout << "left clicked debug button!" << endl;
						board.debug_mode = !board.debug_mode;
					}
				}
				/*if
					(rect1.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
					if (rect1.getFillColor() == sf::Color(255, 165, 0))
						rect1.setFillColor(sf::Color::Blue);
					else
						rect1.setFillColor(sf::Color(255, 165, 0));
				}
				if
					(rect2.getGlobalBounds().contains(window.mapPixelToCoords(mouse))) {
					if (rect2.getFillColor() == sf::Color(255, 165, 0))
						rect2.setFillColor(sf::Color::Blue);
					else
						rect2.setFillColor(sf::Color(255, 165, 0));
				}
				// Toggle between pokeball and pikachu
				if (pokeballSprite.getGlobalBounds().contains(window.mapPixelToCoords(mouse)))
					pikachuVisible = !pikachuVisible;
					*/
			}
			
		}

		/*window.draw(text);
		window.draw(rect1);
		window.draw(rect2);
		if (!pikachuVisible)
			window.draw(pokeballSprite);
		if (pikachuVisible)
			window.draw(pikachuSprite);*/

		window.clear(sf::Color::White);
		window.draw(happyFaceSprite);
		window.draw(debugSprite);
		window.draw(pausePlaySprite);
		window.draw(leaderboardButtonSprite);

	
		board.draw_board(window);

		window.display();

	}
	return 0;
}