#pragma once

#include <string>
#include <SFML/Graphics/RenderWindow.hpp>

#include "gameObject.hpp"

class Scene {
    private:
        const std::string identifier;

        //dynamic array cannot use reference
        //using pointer to iterate through the gameobject(polymorphism)
        std::vector<GameObject*> listOfGameObjects;
        std::function<void()> action;

    public:
        Scene(std::string identifier);
        ~Scene();

    public:
    //using preferense be for not create copy and check null
        void addGameObject(GameObject& object);
        //dont allow event to be change inside
        void handleEvent(const sf::Event& event, sf::RenderWindow& window);
        void update();
        void render(sf::RenderWindow& window);


        //cant make change to inside var
        std::string getIdentifier() const;

        void setUpdate(std::function<void()> action);
};