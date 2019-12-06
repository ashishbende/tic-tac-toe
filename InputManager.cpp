#include "InputManager.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button mButton,
                                   sf::RenderWindow &window) {
    // check if button click collides with any sprite element
    if(sf::Mouse::isButtonPressed(mButton)){
        sf::IntRect rectCapture (object.getPosition().x,
                                object.getPosition().y,
                                object.getGlobalBounds().width, object.getGlobalBounds().height);
        
        // when object sprite collides with window position
        if(rectCapture.contains(sf::Mouse::getPosition(window))){
            return true;
        }
    }
    return false;
}


sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow &window) {
    return sf::Mouse::getPosition(window);
}

} // namespace TicTacToe
