#include "scene.hpp"

Scene::Scene(std::string identifier) : identifier(identifier) { }//initialization list

Scene::~Scene() { }

void Scene::addGameObject(GameObject& object) {
    this->listOfGameObjects.push_back(&object);
}

void Scene::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->handleEvent(event, window);
    }
}

void Scene::update() { 
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
        this->listOfGameObjects[i]->update();
    }
    if(this->action!= nullptr){
        this->action();
    }
}

void Scene::render(sf::RenderWindow& window) {
    //for loop create copy when added
    for(unsigned int i = 0; i < this->listOfGameObjects.size(); i++) {
       this->listOfGameObjects[i]->render(window);
    }
}

std::string Scene::getIdentifier() const {
    return this->identifier;
}
void Scene::setUpdate(std::function<void()> action) {
    this->action=action;
}