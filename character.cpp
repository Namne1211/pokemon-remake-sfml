#include "character.hpp"
#include <stdlib.h>  

#include <algorithm>

Character::Character(std::string identifier,std::string name, std::string spriteFile, int hp, int attack, int defense,int mana) :
        GameObject(identifier),name(name), spriteFile(spriteFile), hp(hp), attack(attack), defense(defense), mana(mana)
{
    this->maxHP=20;
    this->maxMana=20;

}

Character::~Character() { }

int Character::attackCharacter(const Character& character) const {
    //Just a random function
    
    //attack + 0~3 
    int attackPower = attack + rand() % 4; 
    // defense + -1~1
    int defensePower = character.getDefense() + (-1 + rand() % 3);


    return std::max(attackPower - defensePower, 1);
}

int Character::castMagic(const Character &character) {
    //Just a random function
    int power[3]={10,15,20};
    //attack + 0~3
    int Power = power[rand()%3];
    this->mana-=15;
    return Power;
}

int Character::recover() const {
    int healing[2]={10,20};
    int healAmount = healing[rand()%2];

    return healAmount;
}

bool Character::heal(int healAmout) {
    this->hp=this->hp+healAmout;
}

bool Character::takeDamage(int damage) {
    hp = std::max(hp - damage, 0);
    return hp == 0;
}

int Character::getAttack() const {
    return this->attack;
}

void Character::setAttack(int attack) {
    this->attack = attack;
}

int Character::getMana() const {
    return this->mana;
}

void Character::setMana(int mana) {
    this->mana = (mana > 0) ? mana : 0;
}

int Character::getDefense() const {
    return this->defense;
}

int Character::getHP() const {
    return this->hp;
}

int Character::getMaxHP() const {
    return this->maxHP;
}

int Character::getMaxMana()  const {
    return this->maxMana;
}

std::string Character::getName() const {
    return this->name;
}

std::string Character::getSpriteFile() const {
    return this->spriteFile;
}

void Character::setSpriteFile(std::string spriteFile) {
    this->spriteFile=spriteFile;
}

void Character::setDefense(int defense) {
    this->defense = defense;
}

void Character::setHP(int hp) {
    this->hp = (hp > 0) ? hp : 0;
}

void Character::setMaxHP(int maxHP) {
    this->maxHP = (maxHP > 0) ? maxHP : 0;
}

void Character::setMaxMana(int maxMana) {
    this->maxMana = (maxMana > 0) ? maxMana : 0;
}

void Character::setName(std::string name) {
    this->name = name;
}

void Character::setBehavior(std::function<void()> behavior) {
    this->behavior=behavior;
}
void Character::handleEvent(const sf::Event& event, sf::RenderWindow& window) {}

void Character::update() {
    if(this->behavior!= nullptr){
        this->behavior();
    }

}

void Character::render(sf::RenderWindow& window) {}



