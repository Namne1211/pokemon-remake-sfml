#include "scene.hpp"
#include "textObject.hpp"
#include "spriteObject.hpp"
#include "character.hpp"
#include "button.hpp"
#include "sceneHandler.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <mach-o/dyld.h>
#include <fstream>


void multiplybytwo(int num){

}


int main() {
    //---------------------------------------------------


    std::string exec_name="/498735-nam-2023";
    std::string s_path;

    //define exec file
    char path[PATH_MAX+1];
    uint32_t size = sizeof(path);
    if (_NSGetExecutablePath(path, &size) == 0)
        printf("executable path is %s\n", path);
    else
        printf("buffer too small; need size %u\n", size);
    //resize exec file
    s_path= path;
    s_path.resize(s_path.size()-exec_name.size());

    //highscore list
    std::vector<std::string> highScore;
    //points attribute for player

    int points=6;

    srand(time(nullptr));
    const std::string NameArray[10] = { "budz", "pain", "konan", "nagato", "itachi",
                                  "tobi", "madara", "naruto", "danzou", "kakashi" };
    //---------------------------------------------------


    //sound set up
    //---------------------------------------------------
    sf::SoundBuffer click;
    sf::SoundBuffer heal;
    sf::SoundBuffer cast;
    sf::SoundBuffer win;
    sf::SoundBuffer lose;

    sf::Music MenuSong;
    sf::Music FightingSong;

    sf::Sound clickS;
    sf::Sound healS;
    sf::Sound castS;
    sf::Sound winS;
    sf::Sound loseS;


    click.loadFromFile(s_path+"/click.wav");
    heal.loadFromFile(s_path+"/heal.wav");
    cast.loadFromFile(s_path+"/magic.wav");
    win.loadFromFile(s_path+"/win.wav");
    lose.loadFromFile(s_path+"/lose.wav");

    clickS.setBuffer(click);
    healS.setBuffer(heal);
    castS.setBuffer(cast);
    winS.setBuffer(win);
    loseS.setBuffer(lose);

    MenuSong.openFromFile(s_path+"/menuSong.flac");
    FightingSong.openFromFile(s_path+"/battleSong.flac");

    MenuSong.setVolume(50);
    MenuSong.setLoop(true);

    FightingSong.setVolume(50);
    FightingSong.setLoop(true);

    MenuSong.play();
    //---------------------------------------------------

    //---------------------------------------------------
    //window
    sf::RenderWindow window(sf::VideoMode(1400, 1000), "Hey it runn!!");
    window.setFramerateLimit(60);
    //scene
    Scene MainMenuScreen("MainMenuScreen");
    Scene characterScreen("characterScreen");
    Scene fightingScreen("fightingScreen");
    Scene gameOverScreen("gameOverScreen");
    //character
    Character character("character","", s_path+"/character.png", 40, 1, 1,20);

    Character enemy("enemy","", s_path+"/enemy.png", 40, 1, 1,20);
    //random name generate
    std::string random;
    random=NameArray[rand()%9];
    character.setName(random);

    //scene handler
    int counter = 0;
    SceneHandler handler;
    handler.addScene(MainMenuScreen);
    handler.addScene(characterScreen);
    handler.addScene(fightingScreen);
    handler.addScene(gameOverScreen);

    //fight var
    int maxHP =character.getHP();
    int fightstate=0;
    sf::Clock clock;
    bool restartTimer= false;
    bool moved=false;
    int move;
    //---------------------------------------------------

    //---------------------------------------------------

    //font and color setup
    sf::Font font;
    font.loadFromFile(s_path+"/Lato-Regular.ttf");
    sf::Color darkColor = sf::Color(71, 82, 94, 255);
    sf::Color darkGreyColor = sf::Color(132, 146, 166, 255);
    sf::Color lightGreyColor = sf::Color(129, 144, 165, 255);
    sf::Color white = sf::Color(255, 255, 255, 255);
    //---------------------------------------------------


    //text
    //---------------------------------------------------
    //mainmenu text
    TextObject p1Text("p1Text", font, "1: ");
    p1Text.setPosition(sf::Vector2f(850.0f, 250.0f));
    p1Text.setCharacterSize(26);
    p1Text.setFillColor(white);

    TextObject p2Text("p2Text", font, "2: ");
    p2Text.setPosition(sf::Vector2f(850.0f, 350.0f));
    p2Text.setCharacterSize(26);
    p2Text.setFillColor(white);

    TextObject p3Text("p3Text", font, "3: ");
    p3Text.setPosition(sf::Vector2f(850.0f, 450.0f));
    p3Text.setCharacterSize(26);
    p3Text.setFillColor(white);

    TextObject p4Text("p4Text", font, "4: ");
    p4Text.setPosition(sf::Vector2f(850.0f, 550.0f));
    p4Text.setCharacterSize(26);
    p4Text.setFillColor(white);

    TextObject p5Text("p5Text", font, "5: ");
    p5Text.setPosition(sf::Vector2f(850.0f, 650.0f));
    p5Text.setCharacterSize(26);
    p5Text.setFillColor(white);

    //character scene text
    TextObject characterName("characterNameText", font, character.getName());
    characterName.setPosition(sf::Vector2f(435.0f, 340.0f));
    characterName.setCharacterSize(45);
    characterName.setFillColor(darkColor);

    TextObject hpText("hpText", font, "HP: " + std::to_string(character.getMaxHP()));
    hpText.setPosition(sf::Vector2f(780.0f, 338.0f));
    hpText.setCharacterSize(26);
    hpText.setFillColor(darkColor);

    TextObject manaText("manaText", font, "MANA: " + std::to_string(character.getMaxMana()));
    manaText.setPosition(sf::Vector2f(900.0f, 338.0f));
    manaText.setCharacterSize(26);
    manaText.setFillColor(darkColor);

    TextObject attackText("attackText", font, "ATTACK: " + std::to_string(character.getAttack()));
    attackText.setPosition(sf::Vector2f(848.0f, 390.0f));
    attackText.setCharacterSize(26);
    attackText.setFillColor(darkColor);

    TextObject defenseText("defenseText", font, "DEFENSE: " + std::to_string(character.getDefense()));
    defenseText.setPosition(sf::Vector2f(840.0f, 445.0f));
    defenseText.setCharacterSize(26);
    defenseText.setFillColor(darkColor);

    TextObject pointsText("pointsText", font, "POINTS: " + std::to_string(points));
    pointsText.setPosition(sf::Vector2f(435.0f, 634.0f));
    pointsText.setCharacterSize(30);
    pointsText.setFillColor(darkColor);
    TextObject gameText("gameText", font, "a chicken eat a kitchen");
    gameText.setPosition(sf::Vector2f(100.0f, 700.0f));
    gameText.setCharacterSize(50);
    gameText.setFillColor(darkColor);

    TextObject inGameName("inGameName", font,  character.getName());
    inGameName.setPosition(sf::Vector2f(40.0f, 40.0f));
    inGameName.setCharacterSize(30);
    inGameName.setFillColor(darkColor);

    TextObject attackTextFS("attackTextFS", font, "ATTACK: " + std::to_string(character.getAttack()));
    attackTextFS.setPosition(sf::Vector2f(40.0f, 80.0f));
    attackTextFS.setCharacterSize(22);
    attackTextFS.setFillColor(darkColor);

    TextObject defenseTextFS("defenseTextFS", font, "DEFENSE: " + std::to_string(character.getDefense()));
    defenseTextFS.setPosition(sf::Vector2f(40.0f, 110.0f));
    defenseTextFS.setCharacterSize(22);
    defenseTextFS.setFillColor(darkColor);

    TextObject HPTextFS("HPTextFS", font, "HP: " + std::to_string(character.getHP()));
    HPTextFS.setPosition(sf::Vector2f(40.0f, 140.0f));
    HPTextFS.setCharacterSize(22);
    HPTextFS.setFillColor(darkColor);

    TextObject ManaTextFS("ManaTextFS", font, "MANA: " + std::to_string(character.getMana()));
    ManaTextFS.setPosition(sf::Vector2f(40.0f, 170.0f));
    ManaTextFS.setCharacterSize(22);
    ManaTextFS.setFillColor(darkColor);

    TextObject enemyName("enemyName", font,  enemy.getName());
    enemyName.setPosition(sf::Vector2f(1000.0f, 450.0f));
    enemyName.setCharacterSize(30);
    enemyName.setFillColor(darkColor);

    TextObject enemyAttack("enemyAttack", font, "ATTACK: " + std::to_string(enemy.getAttack()));
    enemyAttack.setPosition(sf::Vector2f(1000.0f, 490.0f));
    enemyAttack.setCharacterSize(22);
    enemyAttack.setFillColor(darkColor);

    TextObject enemyDeffense("enemyDeffense", font, "DEFENSE: " + std::to_string(enemy.getDefense()));
    enemyDeffense.setPosition(sf::Vector2f(1000.0f, 520.0f));
    enemyDeffense.setCharacterSize(22);
    enemyDeffense.setFillColor(darkColor);

    TextObject enemyHP("enemyHP", font, "HP: " + std::to_string(enemy.getHP()));
    enemyHP.setPosition(sf::Vector2f(1000.0f, 550.0f));
    enemyHP.setCharacterSize(22);
    enemyHP.setFillColor(darkColor);

    TextObject enemyMana("enemyMana", font, "MANA: " + std::to_string(enemy.getMana()));
    enemyMana.setPosition(sf::Vector2f(1000.0f, 580.0f));
    enemyMana.setCharacterSize(22);
    enemyMana.setFillColor(darkColor);
    //---------------------------------------------------


    //game over text

    TextObject GOText("GOText", font,"");
    GOText.setPosition(sf::Vector2f(485.0f, 400.0f));
    GOText.setCharacterSize(45);
    GOText.setFillColor(darkColor);

    TextObject GOInfoText("GOInfoText", font,"");
    GOInfoText.setPosition(sf::Vector2f(485.0f, 450.0f));
    GOInfoText.setCharacterSize(40);
    GOInfoText.setFillColor(darkColor);

    //sprite
    //---------------------------------------------------

    //character scene sprite
    //---------------------------------------------------
    SpriteObject characterAvatar("soldierSprite", character.getSpriteFile());
    characterAvatar.setPosition(sf::Vector2f(435.0f, 420.0f));
    characterAvatar.setScale(sf::Vector2f(0.2f, 0.2f));

    SpriteObject characterBG("characterBG", s_path+"/characterbg.png");
    characterBG.setPosition(sf::Vector2f(0, 0));
    characterBG.setScale(sf::Vector2f(1, 1));

    //mainmenu sprite
    SpriteObject MMBG("MMBG", s_path+"/mmbg.png");
    MMBG.setPosition(sf::Vector2f(0, 0));
    MMBG.setScale(sf::Vector2f(1, 1));

    //fighting sprite
    SpriteObject FightBG("FightBG", s_path+"/bg.png");
    FightBG.setPosition(sf::Vector2f(0, 0));
    FightBG.setScale(sf::Vector2f(1, 1));

    SpriteObject ingameAvatar("ingameAvatar", character.getSpriteFile());
    ingameAvatar.setPosition(sf::Vector2f(340.0f, 360.0f));
    ingameAvatar.setScale(sf::Vector2f(0.2f, 0.2f));

    SpriteObject enemyAvatar("enemyAvatar", enemy.getSpriteFile());
    enemyAvatar.setPosition(sf::Vector2f(890.0f, 150.0f));
    enemyAvatar.setScale(sf::Vector2f(0.15f, 0.15f));
    //---------------------------------------------------

    //button
    //---------------------------------------------------

    //character screen button
    Button fightButton("fightButton", font, "FIGHT",
                       sf::Vector2f(200.0f, 50.0f), darkColor);
    fightButton.setPosition(sf::Vector2f(808.0f, 500.0f));
    fightButton.setButtonAction([&handler, &counter, &character, &enemy, &NameArray,
                                        &inGameName,&HPTextFS,&ManaTextFS,&attackTextFS,&defenseTextFS,&gameText,&FightingSong,
                                        &enemyName,&enemyHP,&enemyMana,&enemyAttack,&enemyDeffense, &fightstate, &moved, &restartTimer, &MenuSong, &clickS]() {
        MenuSong.stop();
        FightingSong.play();
        clickS.play();
        //reset firght scene
        gameText.setText("Game started, you move first.");
        fightstate=0;
        moved= false;
        restartTimer= false;
        //name random
        std::string random;
        random=NameArray[rand()%9];
        enemy.setName(random);
        //attribute random
        enemy.setAttack(rand()%5 +1);
        enemy.setDefense(6-enemy.getAttack());
        enemy.setHP(enemy.getAttack()*20);
        enemy.setMaxHP(enemy.getAttack()*20);
        enemy.setMaxMana(enemy.getDefense()*20);
        enemy.setMana(enemy.getMaxMana());

        inGameName.setText(character.getName());
        HPTextFS.setText("HP: "+ std::to_string(character.getMaxHP()));
        ManaTextFS.setText("MANA: "+std::to_string(character.getMana()));
        attackTextFS.setText("ATTACK: "+std::to_string(character.getAttack()));
        defenseTextFS.setText("DEFEND: "+std::to_string(character.getDefense()));

        enemyName.setText(enemy.getName());
        enemyHP.setText("HP: "+ std::to_string(enemy.getMaxHP()));
        enemyMana.setText("MANA: "+std::to_string(enemy.getMaxMana()));
        enemyAttack.setText("ATTACK: "+std::to_string(enemy.getAttack()));
        enemyDeffense.setText("DEFEND: "+std::to_string(enemy.getDefense()));

        //change scene
        handler.popScene();
        handler.stackScene("fightingScreen");
        counter++;

    });

    Button randomizeButton("randomizeButton", font, "RANDOMIZE",
                       sf::Vector2f(200.0f, 50.0f), darkColor);
    randomizeButton.setPosition(sf::Vector2f(808.0f, 570.0f));
    randomizeButton.setButtonAction([&NameArray,&character,&characterName,&hpText,&attackText,&defenseText,&points, &pointsText,&manaText, &clickS](){
        clickS.play();
        //name random
        std::string random;
        random=NameArray[rand()%9];
        character.setName(random);
        characterName.setText(character.getName());
        //attribute random
        character.setAttack(rand()%7 +1);
        character.setDefense(8-character.getAttack());
        character.setHP(character.getAttack()*20);
        character.setMaxHP(character.getAttack()*20);
        character.setMaxMana(character.getDefense()*20);
        character.setMana(character.getMaxMana());
        //update text
        hpText.setText("HP: " + std::to_string(character.getMaxHP()));
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        manaText.setText("MANA: " + std::to_string(character.getMaxMana()));

        points=0;
        pointsText.setText("POINTS: " + std::to_string(points));
    });

    Button returnButton("returnButton", font, "RETURN", sf::Vector2f(200.0f, 50.0f), darkColor);
    returnButton.setPosition(sf::Vector2f(808.0f, 640.0f));
    returnButton.setButtonAction([&handler, &counter, &clickS]() {
        clickS.play();
        handler.popScene();
        counter--;
    });


    Button pAttack("plusAttack", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
    pAttack.setPosition(sf::Vector2f(740.0f, 390.0f));
    pAttack.setButtonAction([&character, &attackText,&hpText,&points,&pointsText, &clickS]() {
        clickS.play();
        if(character.getAttack()+character.getDefense()>=8) return ;
        points--;
        pointsText.setText("POINTS: " + std::to_string(points));
        character.setAttack(character.getAttack() + 1);
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        character.setMaxHP(character.getAttack()*20);
        character.setHP(character.getMaxHP());
        hpText.setText("HP: " + std::to_string(character.getMaxHP()));
    });

    Button rAttack("reduceAttack", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
    rAttack.setPosition(sf::Vector2f(1040.0f, 390.0f));
    rAttack.setButtonAction([&character, &attackText,&hpText,&points, &pointsText, &clickS]() {
        clickS.play();
        if(character.getAttack()<2) return ;
        points++;
        pointsText.setText("POINTS: " + std::to_string(points));
        character.setAttack(character.getAttack() - 1);
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        character.setMaxHP(character.getAttack()*20);
        character.setHP(character.getMaxHP());
        hpText.setText("HP: " + std::to_string(character.getMaxHP()));
    });

    Button pDefense("plusDefense", font, "+", sf::Vector2f(30.0f, 30.0f), darkColor);
    pDefense.setPosition(sf::Vector2f(740.0f, 445.0f));
    pDefense.setButtonAction([&character, &defenseText,&points, &pointsText,&manaText, &clickS]() {
        clickS.play();
        if(character.getAttack()+character.getDefense()>=8) return ;
        points--;
        pointsText.setText("POINTS: " + std::to_string(points));
        character.setDefense(character.getDefense() + 1);
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        character.setMaxMana(character.getDefense()*20);
        character.setMana(character.getMaxMana());
        manaText.setText("MANA: "+std::to_string(character.getMaxMana()));
    });

    Button rDefense("reduceDefense", font, "-", sf::Vector2f(30.0f, 30.0f), darkColor);
    rDefense.setPosition(sf::Vector2f(1040.0f, 445.0f));
    rDefense.setButtonAction([&character, &defenseText,&points, &pointsText, &manaText, &clickS]() {
        clickS.play();
        if(character.getDefense()<2) return ;
        points++;
        pointsText.setText("POINTS: " + std::to_string(points));
        character.setDefense(character.getDefense() - 1);
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        character.setMaxMana(character.getDefense()*20);
        character.setMana(character.getMaxMana());
        manaText.setText("MANA: "+std::to_string(character.getMaxMana()));
    });

    //main menu button

    Button ContinueButton("ContinueButton", font, "CONTINUE", sf::Vector2f(200.0f, 50.0f), darkColor);
    ContinueButton.setPosition(sf::Vector2f(108.0f, 330.0f));
    ContinueButton.setButtonAction([&handler, &counter, &points, &pointsText, &clickS,s_path,
                                    &character,&inGameName,&HPTextFS,&ManaTextFS,&attackTextFS,&defenseTextFS,
                                    &enemy,&enemyName,&enemyHP,&enemyMana,&enemyAttack,&enemyDeffense,&gameText,
                                    &MenuSong,&FightingSong

    ]() {
        clickS.play();
        //load
        std::ifstream myfileRead(s_path+"/data.cmgt");
        std::__fs::filesystem::path p{s_path+"/data.cmgt"};

        if (!myfileRead.fail()) {

            //check if file is large enough to read
            if(file_size(p)<8) return;
            MenuSong.stop();
            FightingSong.play();
            gameText.setText("game loaded its your turn..");
            std::string line;
            std::getline(myfileRead, line);
            character.setName(line);
            inGameName.setText(character.getName());
            std::getline(myfileRead, line);
            character.setAttack(std::stoi(line));
            attackTextFS.setText("ATTACK: "+std::to_string(character.getAttack()));
            std::getline(myfileRead, line);
            character.setDefense(std::stoi(line));
            defenseTextFS.setText("DEFENSE: "+std::to_string(character.getDefense()));
            std::getline(myfileRead, line);
            character.setHP(std::stoi(line));
            HPTextFS.setText("HP: "+std::to_string(character.getHP()));
            std::getline(myfileRead, line);
            character.setMana(std::stoi(line));
            ManaTextFS.setText("MANA: "+std::to_string(character.getMana()));
            std::getline(myfileRead, line);
            character.setMaxHP(std::stoi(line));
            std::getline(myfileRead, line);
            character.setMaxMana(std::stoi(line));

            std::getline(myfileRead, line);
            enemy.setName(line);
            enemyName.setText(enemy.getName());
            std::getline(myfileRead, line);
            enemy.setAttack(std::stoi(line));
            enemyAttack.setText("ATTACK: "+std::to_string(enemy.getAttack()));
            std::getline(myfileRead, line);
            enemy.setDefense(std::stoi(line));
            enemyDeffense.setText("DEFENSE: "+std::to_string(enemy.getDefense()));
            std::getline(myfileRead, line);
            enemy.setHP(std::stoi(line));
            enemyHP.setText("HP: "+std::to_string(enemy.getHP()));
            std::getline(myfileRead, line);
            enemy.setMana(std::stoi(line));
            enemyMana.setText("MANA: "+std::to_string(enemy.getMana()));
            std::getline(myfileRead, line);
            enemy.setMaxHP(std::stoi(line));
            std::getline(myfileRead, line);
            enemy.setMaxMana(std::stoi(line));



            myfileRead.close();
            pointsText.setText("POINTS: " + std::to_string(points));
            handler.stackScene("fightingScreen");
            counter=2;
        }

    });

    Button playButton("playButton", font, "PLAY", sf::Vector2f(200.0f, 50.0f), darkColor);
    playButton.setPosition(sf::Vector2f(108.0f, 400.0f));
    playButton.setButtonAction([&handler, &counter, &NameArray, &character, &characterName, &hpText, &attackText, &defenseText,
                                &manaText, &points, &pointsText, &clickS]() {
        clickS.play();
        //name random
        std::string random;
        random=NameArray[rand()%9];
        character.setName(random);
        characterName.setText(character.getName());
        //attribute random
        character.setAttack(rand()%7 +1);
        character.setDefense(8-character.getAttack());
        character.setHP(character.getAttack()*20);
        character.setMaxHP(character.getAttack()*20);
        character.setMaxMana(character.getDefense()*20);
        character.setMana(character.getMaxMana());
        //update text
        hpText.setText("HP: " + std::to_string(character.getMaxHP()));
        attackText.setText("ATTACK: " + std::to_string(character.getAttack()));
        defenseText.setText("DEFENSE: " + std::to_string(character.getDefense()));
        manaText.setText("MANA: " + std::to_string(character.getMaxMana()));

        points=0;
        pointsText.setText("POINTS: " + std::to_string(points));
        handler.stackScene("characterScreen");
        counter++;
    });

    Button DeleteButton("deleteButton", font, "DELETE RECORD", sf::Vector2f(200.0f, 50.0f), darkColor);
    DeleteButton.setPosition(sf::Vector2f(108.0f, 470.0f));
    DeleteButton.setButtonAction([&p1Text, &p2Text, &p3Text, &p4Text, &p5Text, &highScore, s_path, &clickS]() {
        clickS.play();
        std::ofstream myfileWrite(s_path+"/character.cmgt", std::ios::trunc);
        myfileWrite << "0" << std::endl;
        myfileWrite << "noob0001" << std::endl;
        myfileWrite << "noob0002" << std::endl;
        myfileWrite << "noob0003" << std::endl;
        myfileWrite << "noob0004" << std::endl;
        myfileWrite << "noob0005" << std::endl;


        std::ifstream myfileRead(s_path+"/character.cmgt");
        std::__fs::filesystem::path p{s_path+"/character.cmgt"};
        if (!myfileRead.fail()) {
            //check if file is large enough
            if(file_size(p)<8) return;
            std::string line;

            //reset file and high score vector
            std::getline(myfileRead, line);
            highScore.at(0) = line;

            std::getline(myfileRead, line);
            highScore.at(1) = line;
            p1Text.setText(std::to_string(1) + ": " + line);

            std::getline(myfileRead, line);
            highScore.at(2) = line;
            p2Text.setText(std::to_string(2) + ": " + line);

            std::getline(myfileRead, line);
            highScore.at(3) = line;
            p3Text.setText(std::to_string(3) + ": " + line);

            std::getline(myfileRead, line);
            highScore.at(4) = line;
            p4Text.setText(std::to_string(4) + ": " + line);

            std::getline(myfileRead, line);
            highScore.at(5) = line;
            p5Text.setText(std::to_string(5) + ": " + line);


            myfileRead.close();
        }
    });

    Button quitButton("quitButton", font, "QUIT", sf::Vector2f(200.0f, 50.0f), darkColor);
    quitButton.setPosition(sf::Vector2f(108.0f, 540.0f));
    quitButton.setButtonAction([&window, &clickS]() {
        clickS.play();
        window.close();
    });



    //fighting button
    Button attackButton("attackButton", font, "ATTACK", sf::Vector2f(200.0f, 50.0f), darkColor);
    attackButton.setPosition(sf::Vector2f(150.0f, 840.0f));
    attackButton.setButtonAction([&character,&enemy,&enemyHP,&gameText, &fightstate, &clickS]() {
        if(fightstate==0){
            clickS.play();
            int damage =character.attackCharacter(enemy);
            enemy.takeDamage(damage);
            enemyHP.setText("HP: "+std::to_string(enemy.getHP()));
            gameText.setText("You have attack "+ enemy.getName()+" for "+std::to_string(damage)+" damage.");
            fightstate=1;
        }

    });

    Button doNothingButton("doNothingButton", font, "DO NOTHING", sf::Vector2f(200.0f, 50.0f), darkColor);
    doNothingButton.setPosition(sf::Vector2f(450.0f, 840.0f));
    doNothingButton.setButtonAction([&fightstate,&gameText, &clickS]() {
        if(fightstate==0){
            clickS.play();
            gameText.setText("you have done nothing");
            fightstate=1;
        }
    });

    Button recoverButton("recoverButton", font, "RECOVER", sf::Vector2f(200.0f, 50.0f), darkColor);
    recoverButton.setPosition(sf::Vector2f(750.0f, 840.0f));
    recoverButton.setButtonAction([&character,&HPTextFS,&gameText,&maxHP,&fightstate, &clickS, &healS]() {
        if(fightstate==0){


            if(character.getHP()>=maxHP-30){
                clickS.play();
                gameText.setText("can not do this");
            }else{
                healS.play();
                int healAmount=character.recover();
                character.heal(healAmount);
                HPTextFS.setText("HP: "+std::to_string(character.getHP()));
                gameText.setText("you have heal yourself"+std::to_string(healAmount)+ " health");
                fightstate=1;
            }

        }


    });

    Button castMagicButton("castMagicButton", font, "CAST", sf::Vector2f(200.0f, 50.0f), darkColor);
    castMagicButton.setPosition(sf::Vector2f(1050.0f, 840.0f));
    castMagicButton.setButtonAction([&character,&enemy,&ManaTextFS,&enemyHP,&gameText, &fightstate, &clickS, &castS]() {
        if (fightstate == 0) {

            if(character.getMana()<15){
                clickS.play();
                gameText.setText("You have do not have enough mana.");
            }else{
                castS.play();

                int damage = character.castMagic(enemy);
                enemy.takeDamage(damage);
                enemyHP.setText("HP: " + std::to_string(enemy.getHP()));
                ManaTextFS.setText("MANA: " + std::to_string(character.getMana()));
                gameText.setText("You have cast magic to " + enemy.getName() + " deal " + std::to_string(damage) + " damage.");
                fightstate = 1;
            }
        }
    });

    Button quitButtonFS("quitButtonFS", font, "QUIT", sf::Vector2f(130.0f, 50.0f), darkColor);
    quitButtonFS.setPosition(sf::Vector2f(1220.0f, 900.0f));
    quitButtonFS.setButtonAction([ &handler, &counter, &MenuSong, &FightingSong, &clickS,s_path,&fightstate,&restartTimer,
                                            &moved,&enemy,&character
    ]() {
        clickS.play();
        MenuSong.play();
        FightingSong.stop();

        fightstate=0;
        restartTimer=false;
        moved= false;

        std::ofstream myfileWrite(s_path+"/data.cmgt", std::ios::trunc);
        myfileWrite << character.getName() << std::endl;
        myfileWrite << character.getAttack() << std::endl;
        myfileWrite << character.getDefense() << std::endl;
        myfileWrite << character.getHP() << std::endl;
        myfileWrite << character.getMana() << std::endl;
        myfileWrite << character.getMaxHP() << std::endl;
        myfileWrite << character.getMaxMana() << std::endl;

        myfileWrite << enemy.getName() << std::endl;
        myfileWrite << enemy.getAttack() << std::endl;
        myfileWrite << enemy.getDefense() << std::endl;
        myfileWrite << enemy.getHP() << std::endl;
        myfileWrite << enemy.getMana() << std::endl;
        myfileWrite << enemy.getMaxHP() << std::endl;
        myfileWrite << enemy.getMaxMana() << std::endl;

        myfileWrite.close();

        //button act
        handler.popScene();
        counter = 0;
    });



    //game over button
    Button returnButtonGO("returnButtonGO", font, "RETURN", sf::Vector2f(200.0f, 50.0f), darkColor);
    returnButtonGO.setPosition(sf::Vector2f(600.0f, 640.0f));
    returnButtonGO.setButtonAction([&handler, &counter, s_path, &p1Text, &p2Text, &p3Text, &p4Text, &p5Text, &clickS]() {
        clickS.play();
        //update start screen
        std::ifstream myfileRead(s_path+"/character.cmgt");
        std::ofstream datafilewrite(s_path+"/data.cmgt",std::ios::trunc);
        std::__fs::filesystem::path p{s_path+"/character.cmgt"};
        if (!myfileRead.fail()) {
                //check if file is empty
                if(file_size(p)<8) return;
                std::string line;
                std::getline(myfileRead, line);
                std::getline(myfileRead, line);
                p1Text.setText(std::to_string(1) + ": " + line);
                std::getline(myfileRead, line);
                p2Text.setText(std::to_string(2) + ": " + line);
                std::getline(myfileRead, line);
                p3Text.setText(std::to_string(3) + ": " + line);
                std::getline(myfileRead, line);
                p4Text.setText(std::to_string(4) + ": " + line);
                std::getline(myfileRead, line);
                p5Text.setText(std::to_string(5) + ": " + line);


                myfileRead.close();
            } else {
                std::ofstream myfileWrite(s_path+"/character.cmgt", std::ios::trunc);
                myfileWrite << "0" << std::endl;
                myfileWrite << "noob0001" << std::endl;
                myfileWrite << "noob0002" << std::endl;
                myfileWrite << "noob0003" << std::endl;
                myfileWrite << "noob0004" << std::endl;
                myfileWrite << "noob0005" << std::endl;
                myfileWrite.close();
            }
        handler.popScene();
        counter=0;

    });

    //---------------------------------------------------

    //update datafile the first time enter
    std::ifstream myfileRead(s_path+"/character.cmgt");
    if (!myfileRead.fail()) {
        //check if file is empty
        if(!myfileRead.eof()){
            std::string line;
            std::getline(myfileRead, line);
            highScore.push_back(line);

            std::getline(myfileRead, line);
            highScore.push_back(line);
            p1Text.setText("1: " + line);

            std::getline(myfileRead, line);
            highScore.push_back(line);
            p2Text.setText("2: " + line);

            std::getline(myfileRead, line);
            highScore.push_back(line);
            p3Text.setText("3: " + line);

            std::getline(myfileRead, line);
            highScore.push_back(line);
            p4Text.setText("4: " + line);

            std::getline(myfileRead, line);
            highScore.push_back(line);
            p5Text.setText("5: " + line);


            myfileRead.close();
        }

    }

    //update
    //---------------------------------------------------
    enemy.setBehavior([&fightstate,&gameText, &clock,&restartTimer,&enemy,&character,&HPTextFS,&enemyMana,&enemyHP
                       ,&moved, &move](){
        if(fightstate==1){

            //reset timer
            if(!restartTimer){
                clock.restart();
                restartTimer= true;
            }

            sf::Time timer=clock.getElapsedTime();
            if (timer.asSeconds() >=2.0f & timer.asSeconds() <=3.0f){
                gameText.setText(enemy.getName()+" is thinking...");
                move=rand()%4;
                if(enemy.getMana()<15){
                    while(move==3){
                        move=rand()%4;
                    }
                }else if(enemy.getHP()>=enemy.getMaxHP()-20){
                    while(move==2){
                        move=rand()%4;
                    }
                }

            }
            if(timer.asSeconds() >=4.0f){
                if(move==0){
                    //check if already done
                    if(!moved){
                        gameText.setText(enemy.getName()+" do nothing.");
                        moved= true;
                    }
                }else if(move==1){
                    if(!moved) {
                        int damage = enemy.attackCharacter(character);
                        character.takeDamage(damage);
                        HPTextFS.setText("HP: " + std::to_string(character.getHP()));
                        gameText.setText(enemy.getName() + " attack you for " + std::to_string(damage) + " damage.");
                        moved= true;
                    }
                }else if(move==2){
                    //check if already done
                    if(!moved) {
                        int healAmount=enemy.recover();
                        enemy.heal(healAmount);
                        gameText.setText(enemy.getName() + " recover "+std::to_string(healAmount));
                        enemyHP.setText("HP: "+std::to_string(enemy.getHP()));
                        moved= true;
                    }
                }else if(move==3){
                    //check if already done
                    if(!moved) {

                        int damage=enemy.castMagic(character);
                        character.takeDamage(damage);
                        HPTextFS.setText("HP: " + std::to_string(character.getHP()));
                        enemyMana.setText("MANA:" +std::to_string(enemy.getMana()));
                        gameText.setText(enemy.getName() + " cast magic to you deal "+std::to_string(damage));
                        moved= true;
                    }
                }
                //reset phase
                if(timer.asSeconds()>=6.0f){
                    gameText.setText("your turn");
                    fightstate=0;
                    restartTimer= false;
                    moved= false;
                }
            }
        }
    });


    fightingScreen.setUpdate([&character,&enemy,&handler,&counter,&highScore,s_path,
                              &gameText, &GOText, &GOInfoText, &FightingSong, &MenuSong, &loseS, &winS](){
        if(character.getHP()<=0||enemy.getHP()<=0){
            MenuSong.play();
            FightingSong.stop();
            if(character.getHP()<=0){
                loseS.play();
                GOText.setText("GAME OVER");
            }else if(enemy.getHP()<=0){
                winS.play();
                GOText.setText("FLAWLESS VICTORY");
            }
            GOInfoText.setText("played as "+character.getName());
            //restart fight scene
            gameText.setText("your turn...");


            //update score board
            //update highscore board
            std::ifstream myfileRead(s_path+"/character.cmgt");
            std::__fs::filesystem::path p{s_path+"/character.cmgt"};
            //save score
            //input file
            if (!myfileRead.fail()) {
                std::string line;
                //check if file is empty
                if(file_size(p)<8) return;
                std::getline(myfileRead, line);
                int currentHS = std::stoi(line);
                myfileRead.close();
                //printf("%d\n",currentHS);
                //replace high score
                switch (currentHS) {
                    default:

                    case 0:
                        highScore.at(0) = "1";
                        highScore.at(1) = character.getName();
                        break;
                    case 1:
                        highScore.at(0) = "2";
                        highScore.at(2) = character.getName();
                        break;
                    case 2:
                        highScore.at(0) = "3";
                        highScore.at(3) = character.getName();
                        break;
                    case 3:
                        highScore.at(0) = "4";
                        highScore.at(4) = character.getName();
                        break;
                    case 4:
                        highScore.at(0) = "5";
                        highScore.at(5) = character.getName();
                        break;
                }
                //closing read file

            } else {
                std::ofstream myfileWrite(s_path+"/character.cmgt", std::ios::trunc);
                //redid the file if been deleted
                myfileWrite << "1" << std::endl;
                myfileWrite << character.getName() << std::endl;
                myfileWrite << "noob0002" << std::endl;
                myfileWrite << "noob0003" << std::endl;
                myfileWrite << "noob0004" << std::endl;
                myfileWrite << "noob0005" << std::endl;
                myfileWrite.close();
            }

            std::ofstream myfileWrite(s_path+"/character.cmgt", std::ios::trunc);
            for (auto& i: highScore) {

                myfileWrite << i << std::endl;
            }

            handler.popScene();
            handler.stackScene("gameOverScreen");
            counter++;
        }
    });

    //---------------------------------------------------

    //---------------------------------------------------
    //adding obj to character scene
    //sprite
    characterScreen.addGameObject(characterBG);
    characterScreen.addGameObject(characterAvatar);
    //text
    characterScreen.addGameObject(characterName);
    characterScreen.addGameObject(manaText);
    characterScreen.addGameObject(hpText);
    characterScreen.addGameObject(attackText);
    characterScreen.addGameObject(defenseText);
    characterScreen.addGameObject(pointsText);
    //button
    characterScreen.addGameObject(fightButton);
    characterScreen.addGameObject(returnButton);
    characterScreen.addGameObject(randomizeButton);
    characterScreen.addGameObject(pDefense);
    characterScreen.addGameObject(rDefense);
    characterScreen.addGameObject(rAttack);
    characterScreen.addGameObject(pAttack);

    //adding thing to main menu
    //sprite
    MainMenuScreen.addGameObject(MMBG);
    //text
    MainMenuScreen.addGameObject(p1Text);
    MainMenuScreen.addGameObject(p2Text);
    MainMenuScreen.addGameObject(p3Text);
    MainMenuScreen.addGameObject(p4Text);
    MainMenuScreen.addGameObject(p5Text);
    //button
    MainMenuScreen.addGameObject(DeleteButton);
    MainMenuScreen.addGameObject(playButton);
    MainMenuScreen.addGameObject(quitButton);
    MainMenuScreen.addGameObject(ContinueButton);


    //adding obj to fighting scene
    //bg and text
    fightingScreen.addGameObject(FightBG);
    fightingScreen.addGameObject(gameText);

    //buton
    fightingScreen.addGameObject(attackButton);
    fightingScreen.addGameObject(doNothingButton);
    fightingScreen.addGameObject(recoverButton);
    fightingScreen.addGameObject(castMagicButton);
    fightingScreen.addGameObject(quitButtonFS);

    //character info
    fightingScreen.addGameObject(character);
    fightingScreen.addGameObject(ingameAvatar);
    fightingScreen.addGameObject(inGameName);
    fightingScreen.addGameObject(attackTextFS);
    fightingScreen.addGameObject(defenseTextFS);
    fightingScreen.addGameObject(HPTextFS);
    fightingScreen.addGameObject(ManaTextFS);

    //enemy info
    fightingScreen.addGameObject(enemy);
    fightingScreen.addGameObject(enemyAvatar);
    fightingScreen.addGameObject(enemyName);
    fightingScreen.addGameObject(enemyAttack);
    fightingScreen.addGameObject(enemyDeffense);
    fightingScreen.addGameObject(enemyHP);
    fightingScreen.addGameObject(enemyMana);


    //adding gamoeobject to game over scene
    gameOverScreen.addGameObject(characterBG);
    gameOverScreen.addGameObject(returnButtonGO);
    gameOverScreen.addGameObject(GOText);
    gameOverScreen.addGameObject(GOInfoText);
    //---------------------------------------------------

    //game loop
    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            //handle game event
            if (event.type == sf::Event::Closed) {
                window.close();
            } else {
                //handle scene event
                if (counter == 0) {
                    MainMenuScreen.handleEvent(event, window);
                } else if (counter == 1) {
                    characterScreen.handleEvent(event, window);
                }else if (counter == 2) {
                    fightingScreen.handleEvent(event, window);
                } else {
                    gameOverScreen.handleEvent(event, window);
                }
            }
        }

        //update scene
        window.clear(sf::Color::White);
        handler.update();
        handler.render(window);
        window.display();
    }

    return 0;
}





