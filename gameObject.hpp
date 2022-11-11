#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {
    private: 
        const std::string identifier;
    public:
        GameObject(std::string identifier);
        GameObject(const GameObject& other);


        virtual ~GameObject();
    public:
    // void to be redefine by child class
        virtual void handleEvent(const sf::Event& event, sf::RenderWindow& window) { };
        virtual void update() = 0;//to make pure virtual class, can not be initialize and child have toimplement this
        virtual void render(sf::RenderWindow& window) = 0;//to make pure virtual class
        std::string getIdentifier() const;
};

