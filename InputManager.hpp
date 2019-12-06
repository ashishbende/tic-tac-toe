#pragma once

#include<SFML/Graphics.hpp>


namespace TicTacToe{
    class InputManager{
        public:
        InputManager(){}
        ~InputManager(){}

        bool IsSpriteClicked(sf::Sprite object, sf::Mouse::Button mButton, sf::RenderWindow &window);
        sf::Vector2i GetMousePosition(sf::RenderWindow &window);
    };
}
