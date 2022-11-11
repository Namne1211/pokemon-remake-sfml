#pragma once

#include <string>
#include "gameObject.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Character :public GameObject{
    private:
        std::string name;
        std::string spriteFile;
        int hp;
        int attack;
        int defense;
        int mana;
        int maxHP;
        int maxMana;


        std::function<void()> behavior;
    public:

        Character(std::string identifier,std::string name, std::string spriteFile,
                    int hp, int attack, int defense,int mana);
        ~Character();

        void handleEvent(const sf::Event& event, sf::RenderWindow& window) override;

        void update() override;
        void render(sf::RenderWindow& window) override;

        int attackCharacter(const Character& character) const;

        int castMagic(const Character& character);
        int recover() const;

        bool heal(int healAmout);
        bool takeDamage(int damage);

        int getAttack() const;
        void setAttack(int attack);

        int getDefense() const;
        void setDefense(int defense);

        int getHP() const;
        void setHP(int hp);

        int getMana() const;
        void setMana(int mana);

        int getMaxMana() const;
        void setMaxMana(int maxMana);

        int getMaxHP() const;
        void setMaxHP(int MaxHP);

        std::string getName() const;
        void setName(std::string name);

        std::string getSpriteFile() const;

        void setSpriteFile(std::string spriteFile);

        void setBehavior(std::function<void()> behavior);
};


