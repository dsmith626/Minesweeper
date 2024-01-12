#include <SFML/Graphics.hpp>
#include <vector>
#include "Tile.h"
#include <ctime>
#include <fstream>
using namespace std;

int main()
{
    //create window, customize size
    sf::RenderWindow window(sf::VideoMode(800, 600), "minesweeper: David Smith");
    window.setFramerateLimit(60);

    ///--------------------LOAD NECESSARY TEXTURES AND RESPECTIVE SPRITES---------------------------------------
    sf::Texture tile;
    tile.loadFromFile("images/tile_hidden.png");
    sf::Sprite sprite;
    sprite.setTexture(tile);

    sf::Texture opentile;
    opentile.loadFromFile("images/tile_revealed.png");

    sf::Texture digits;
    digits.loadFromFile("images/digits.png");
    sf::Sprite digitSprite;
    digitSprite.setTexture(digits);

    sf::Texture smily;
    smily.loadFromFile("images/face_happy.png");
    sf::Sprite smilySprite;
    smilySprite.setTexture(smily);

    sf::Texture debug;
    debug.loadFromFile("images/debug.png");
    sf::Sprite dbsprite;
    dbsprite.setTexture(debug);

    sf::Texture test1;
    test1.loadFromFile("images/test_1.png");
    sf::Sprite t1sprite;
    t1sprite.setTexture(test1);

    sf::Texture test2;
    test2.loadFromFile("images/test_2.png");
    sf::Sprite t2sprite;
    t2sprite.setTexture(test2);

    sf::Texture test3;
    test3.loadFromFile("images/test_3.png");
    sf::Sprite t3sprite;
    t3sprite.setTexture(test3);

    sf::Texture mine;
    mine.loadFromFile("images/mine.png");
    sf::Sprite minesprite;
    minesprite.setTexture(mine);

    sf::Texture flag;
    flag.loadFromFile("images/flag.png");
    sf::Sprite flagsprite;
    flagsprite.setTexture(flag);

    sf::Texture one;
    one.loadFromFile("images/number_1.png");
    sf::Sprite sprite1;
    sprite1.setTexture(one);

    sf::Texture two;
    two.loadFromFile("images/number_2.png");
    sf::Sprite sprite2;
    sprite2.setTexture(two);

    sf::Texture three;
    three.loadFromFile("images/number_3.png");
    sf::Sprite sprite3;
    sprite3.setTexture(three);

    sf::Texture four;
    four.loadFromFile("images/number_4.png");
    sf::Sprite sprite4;
    sprite4.setTexture(four);

    sf::Texture five;
    five.loadFromFile("images/number_5.png");
    sf::Sprite sprite5;
    sprite5.setTexture(five);

    sf::Texture six;
    six.loadFromFile("images/number_6.png");
    sf::Sprite sprite6;
    sprite6.setTexture(six);

    sf::Texture seven;
    seven.loadFromFile("images/number_7.png");
    sf::Sprite sprite7;
    sprite7.setTexture(seven);

    sf::Texture eight;
    eight.loadFromFile("images/number_8.png");
    sf::Sprite sprite8;
    sprite8.setTexture(eight);

    sf::Texture lose;
    lose.loadFromFile("images/face_lose.png");
    sf::Sprite lostsprite;
    lostsprite.setTexture(lose);

    sf::Texture won;
    won.loadFromFile("images/face_win.png");
    sf::Sprite victorySprite;
    victorySprite.setTexture(won);

    ///--------------------END SPRITE LOAD---------------------------------------

    ///-------------------BOARD LOAD---------------------------------------------

    ifstream board1("boards/testboard1.brd");
    if(!board1.is_open()){
        cout << "Error opening board 1" << endl;
    }
    ifstream board2("boards/testboard2.brd");
    if(!board1.is_open()){
        cout << "Error opening board 1" << endl;
    }
    ifstream board3("boards/testboard3.brd");
    if(!board1.is_open()){
        cout << "Error opening board 1" << endl;
    }
    bool mineboard1[400];
    bool mineboard2[400];
    bool mineboard3[400];

    int count = 0;
    while(!board1.eof()){
        string line;
        getline(board1, line);
        for(int i = 0; i < line.length(); i++){
            char cur = line[i];
            if(cur == '1'){
                mineboard1[count] = true;
                count++;
            }else{
                mineboard1[count] = false;
                count++;
            }
        }
    }
    count = 0;
    while(!board2.eof()){
        string line;
        getline(board2, line);
        for(int i = 0; i < line.length(); i++){
            char cur = line[i];
            if(cur == '1'){
                mineboard2[count] = true;
                count++;
            }else{
                mineboard2[count] = false;
                count++;
            }
        }
    }
    count = 0;
    while(!board3.eof()){
        string line;
        getline(board3, line);
        for(int i = 0; i < line.length(); i++){
            char cur = line[i];
            if(cur == '1'){
                mineboard3[count] = true;
                count++;
            }else{
                mineboard3[count] = false;
                count++;
            }
        }
    }

    Board testboard1 = Board(mineboard1);
    Board testboard2 = Board(mineboard2);
    Board testboard3 = Board(mineboard3);

    ///-------------------END BOARD LOAD--------------------------------
    ///-------------------MISCELLANEOUS VARIABLE LOAD-------------------

    srand(time(0));
    Board board;
    bool gameover = false;

    vector<Tile> tiles;
    vector<sf::Sprite> boardSprites;

    for(int i = 0; i < 400; i++){
        sf::Sprite cur;
        cur.setTexture(tile);
        boardSprites.push_back(cur);

        Tile curTile;
        if(board.getMineBoard()[i])
            curTile.setContainsMine(true);
        tiles.push_back(curTile);
    }

    vector<int> openup;
    bool debugMode = false;
    bool victory = false;

    int numMines;
    for(int i = 0; i < 400; i++){
        if(board.getMineBoard()[i])
            numMines++;
    }
    int numHidden = 0;
    for(int i = 0; i < tiles.size(); i++){
        if(tiles.at(i).isHidden())
            numHidden++;
    }

    int numFlagged = 0;
    int scoreboardValue;

    ///-------------------END MISCELLANEOUS VARIABLE LOAD-----------------



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            /// user clicks the reset button
            if (tiles.at(0).isMouseOver(smilySprite.getGlobalBounds(),
                                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    scoreboardValue = 0;
                    boardSprites.clear();
                    openup.clear();
                    tiles.clear();
                    gameover = false;
                    victory = false;
                    Board b;
                    board = b;
                    numFlagged = 0;
                    numMines = 0;
                    for(int i = 0; i < 400; i++){
                        sf::Sprite cur;
                        cur.setTexture(tile);
                        boardSprites.push_back(cur);

                        Tile curTile;
                        if(board.getMineBoard()[i])
                            curTile.setContainsMine(true);
                        tiles.push_back(curTile);
                    }
                }
            }

            /// user clicks debug mode button
            if (tiles.at(0).isMouseOver(dbsprite.getGlobalBounds(),
                                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    debugMode = !debugMode;
                }
            }

            /// user clicks test 1
            if (tiles.at(0).isMouseOver(t1sprite.getGlobalBounds(),
                                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    scoreboardValue = 0;
                    boardSprites.clear();
                    openup.clear();
                    tiles.clear();
                    gameover = false;
                    victory = false;
                    board = testboard1;
                    numFlagged = 0;
                    numMines = 0;
                    for(int i = 0; i < 400; i++){
                        sf::Sprite cur;
                        cur.setTexture(tile);
                        boardSprites.push_back(cur);

                        Tile curTile;
                        if(board.getMineBoard()[i])
                            curTile.setContainsMine(true);
                        tiles.push_back(curTile);
                    }
                }
            }

            /// user clicks test 2
            if (tiles.at(0).isMouseOver(t2sprite.getGlobalBounds(),
                                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    scoreboardValue = 0;
                    boardSprites.clear();
                    openup.clear();
                    tiles.clear();
                    gameover = false;
                    victory = false;
                    board = testboard2;
                    numFlagged = 0;
                    numMines = 0;
                    for(int i = 0; i < 400; i++){
                        sf::Sprite cur;
                        cur.setTexture(tile);
                        boardSprites.push_back(cur);

                        Tile curTile;
                        if(board.getMineBoard()[i])
                            curTile.setContainsMine(true);
                        tiles.push_back(curTile);
                    }
                }
            }

            /// user clicks test 3
            if (tiles.at(0).isMouseOver(t3sprite.getGlobalBounds(),
                                        sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    scoreboardValue = 0;
                    boardSprites.clear();
                    openup.clear();
                    tiles.clear();
                    gameover = false;
                    victory = false;
                    board = testboard3;
                    numFlagged = 0;
                    numMines = 0;
                    for(int i = 0; i < 400; i++){
                        sf::Sprite cur;
                        cur.setTexture(tile);
                        boardSprites.push_back(cur);

                        Tile curTile;
                        if(board.getMineBoard()[i])
                            curTile.setContainsMine(true);
                        tiles.push_back(curTile);
                    }
                }
            }

            ///makes vector of adjacent tile indices for each tile
            for(int i = 0; i < tiles.size(); i++){
                vector<int> adjacent = tiles.at(i).adjacent;
                ///makes vector of adjacent tile indices

                if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                    if ((i + 1 < 400)) {
                        adjacent.push_back(i+1);
                    }
                }
                if(i-1 >= 0 &&  (i % 25 != 0 || i-1==0)){
                    adjacent.push_back(i-1);
                }
                if(i+25 < 400){
                    adjacent.push_back(i+25);
                }
                if(i+24 < 400 && (i!= 0) && (i%25!=0)){
                    adjacent.push_back(i+24);
                }
                if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                    if(i+26 < 400 && (i+1 % 25 != 0)) {
                        adjacent.push_back(i+26);
                    }
                }
                if(i-25 >= 0){
                    adjacent.push_back(i-25);
                }
                if(i-26 >= 0 && (i%25 != 0)) {
                    adjacent.push_back(i-26);
                }
                if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                    if (i - 24 >= 0 && (i + 1 % 25 != 0)) {
                        adjacent.push_back(i-24);
                    }
                }
                tiles.at(i).adjacent = adjacent;
            }

            numMines = 0;
            for(int i = 0; i < 400; i++){
                if(board.getMineBoard()[i])
                    numMines++;
            }

            /// user clicks a tile
            if (!gameover && !victory) {
                for (int i = 0; i < boardSprites.size(); i++) {

                    switch (board.getValueBoard()[i]) {
                        case 0:
                            if(!board.getMineBoard()[i])
                                tiles.at(i).drawzero = true;
                            break;
                        case 1:
                            tiles.at(i).drawone = true;
                            break;
                        case 2:
                            tiles.at(i).drawtwo = true;
                            break;
                        case 3:
                            tiles.at(i).drawthree = true;
                            break;
                        case 4:
                            tiles.at(i).drawfour = true;
                            break;
                        case 5:
                            tiles.at(i).drawfive = true;
                            break;
                        case 6:
                            tiles.at(i).drawsix = true;
                            break;
                        case 7:
                            tiles.at(i).drawseven = true;
                            break;
                        case 8:
                            tiles.at(i).draweight = true;
                            break;
                        default:
                            break;
                    }

                    if (tiles.at(i).isMouseOver(boardSprites.at(i).getGlobalBounds(),
                                                sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {

                        /// Left click
                        if (event.type == sf::Event::MouseButtonReleased &&
                            event.mouseButton.button == sf::Mouse::Left) {

                            ///user clicks zero tile, recursive call
                            if(!tiles.at(i).isFlagged()) {
                                if(tiles.at(i).drawzero) {

                                       openup = tiles.at(i).zeroroll(openup, i, tiles);

                                }
                            }

                            for(int i = 0; i < openup.size(); i++){
                                boardSprites.at(openup.at(i)).setTexture(opentile);
                                tiles.at(openup.at(i)).setHidden(false);
                            }

                            ///open tile if not flagged
                            if (!tiles.at(i).isFlagged()) {
                                    boardSprites.at(i).setTexture(opentile);
                                    tiles.at(i).setHidden(false);
                            }

                            ///gameover if they click on a mine
                            if (tiles.at(i).hasMine() && !(tiles.at(i).isFlagged())) {
                                gameover = true;
                                break;
                            }

                            numHidden = 0;
                            for(int i = 0; i < tiles.size(); i++) {
                                if (tiles.at(i).isHidden())
                                    numHidden++;
                            }

                            ///checks if they won
                            if(numHidden == numMines) {
                                victory = true;
                                break;
                            }

                        }

                        ///Right click -> set flag
                        if (event.type == sf::Event::MouseButtonReleased &&
                            event.mouseButton.button == sf::Mouse::Right) {
                            if (tiles.at(i).isHidden()) {
                                tiles.at(i).flag();
                            }
                        }

                    }
                }
            }
        }

        window.clear();

        ///-------------------BEGIN DRAWING UI -- STARTING WITH SCOREBOARD ----------------------------

        if(victory){
            for(int i = 0; i < tiles.size(); i++){
                if(tiles.at(i).hasMine())
                    if(!tiles.at(i).isFlagged())
                        tiles.at(i).flag();
            }
        }
        numFlagged = 0;
        for(int i = 0; i < tiles.size(); i++){
            if(tiles.at(i).isFlagged())
                numFlagged++;
        }

            scoreboardValue = numMines - numFlagged;
            int first;
            int second;
            int third = -401;
            if (scoreboardValue / 100 != 0) {
                first = abs(scoreboardValue / 100);
                second = abs(scoreboardValue % 10)/10;
                third = abs(scoreboardValue % 10);
            }
            else if (scoreboardValue < 10 && scoreboardValue > -10){
                first = 0;
                second = 0;
                third = abs(scoreboardValue % 10);
            }
            else if (scoreboardValue < 100 && scoreboardValue > -100) {
                first = 0;
                second = abs(scoreboardValue / 10);
                third = abs(scoreboardValue % 10);
            } else {
                third = abs(scoreboardValue % 10);
            }

            if (scoreboardValue >= 0) {
                digitSprite.setPosition(sf::Vector2f(0, 16 * sprite.getGlobalBounds().height));

                digitSprite.setTextureRect(sf::IntRect(first * 21, 0, 21, 32));
                window.draw(digitSprite);

                digitSprite.setPosition(sf::Vector2f(21, 16 * sprite.getGlobalBounds().height));

                digitSprite.setTextureRect(sf::IntRect(second * 21, 0, 21, 32));
                window.draw(digitSprite);

                if (third != -401) {
                    digitSprite.setPosition(sf::Vector2f(42, 16 * sprite.getGlobalBounds().height));

                    digitSprite.setTextureRect(sf::IntRect(third * 21, 0, 21, 32));
                    window.draw(digitSprite);
                }
            } else {
                digitSprite.setPosition(sf::Vector2f(0, 16 * sprite.getGlobalBounds().height));
                digitSprite.setTextureRect(sf::IntRect(10 * 21, 0, 21, 32));
                window.draw(digitSprite);

                digitSprite.setPosition(sf::Vector2f(21, 16 * sprite.getGlobalBounds().height));
                digitSprite.setTextureRect(sf::IntRect(first * 21, 0, 21, 32));
                window.draw(digitSprite);

                digitSprite.setPosition(sf::Vector2f(42, 16 * sprite.getGlobalBounds().height));
                digitSprite.setTextureRect(sf::IntRect(second * 21, 0, 21, 32));
                window.draw(digitSprite);

                if (third != -401) {
                    digitSprite.setPosition(sf::Vector2f(64, 16 * sprite.getGlobalBounds().height));

                    digitSprite.setTextureRect(sf::IntRect(third * 21, 0, 21, 32));
                    window.draw(digitSprite);
                }

            }
            ///-------------------------END DRAWING SCOREBOARD------------------------------------------------------------------

        ///-------------------------BEGIN DRAWING TILES AND VALUES------------------------------------------------------------------

        int count = 0;

        for(int c = 0; c < 16; c++) {
            for (int r = 0; r < 25; r++) {
                Tile curTile = tiles.at(count);


                boardSprites.at(count).setPosition(sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                window.draw(boardSprites.at(count));

                if(!curTile.isHidden()) {

                    if (curTile.drawone) {
                        sprite1.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite1);
                    }
                    if (curTile.drawtwo) {
                        sprite2.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite2);
                    }
                    if (curTile.drawthree) {
                        sprite3.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite3);
                    }
                    if (curTile.drawfour) {
                        sprite4.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite4);
                    }
                    if (curTile.drawfive) {
                        sprite5.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite5);
                    }
                    if (curTile.drawsix) {
                        sprite6.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite6);
                    }
                    if (curTile.drawseven) {
                        sprite7.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite7);
                    }
                    if (curTile.draweight) {
                        sprite8.setPosition(
                                sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(sprite8);
                    }
                }

                if(curTile.isFlagged()){
                    flagsprite.setPosition(sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                    window.draw(flagsprite);
                }

                ///draws mines on top if game over
                if(gameover) {
                    int c = 0;
                    for(int col = 0; col < 16; col++) {
                        for (int row = 0; row < 25; row++) {
                            if(tiles.at(c).hasMine()) {
                                minesprite.setPosition(sf::Vector2f(row * sprite.getGlobalBounds().width,
                                                                    col * sprite.getGlobalBounds().height));
                                window.draw(minesprite);
                            }
                            c++;
                        }
                    }
                }
                ///draws mines on top if in debug mode
                if(debugMode){
                    if(curTile.hasMine()){
                        minesprite.setPosition(sf::Vector2f(r * sprite.getGlobalBounds().width, c * sprite.getGlobalBounds().height));
                        window.draw(minesprite);

                    }
                }

                count++;
            }
        }

        ///-------------------------END DRAWING TILES AND TILE VALUES------------------------------------------------------------------

        ///draw sad guy ig they lost, or happy guy if they win
        if(gameover){
            lostsprite.setPosition(sf::Vector2f(400 - (smilySprite.getGlobalBounds().width)/2, 16 * sprite.getGlobalBounds().height));
            window.draw(lostsprite);

        }
        else if(victory){
            victorySprite.setPosition(sf::Vector2f(400 - (smilySprite.getGlobalBounds().width)/2, 16 * sprite.getGlobalBounds().height));
            window.draw(victorySprite);
        }else{
            smilySprite.setPosition(sf::Vector2f(400 - (smilySprite.getGlobalBounds().width)/2, 16 * sprite.getGlobalBounds().height));
            window.draw(smilySprite);
        }

        ///draw degub button
        dbsprite.setPosition(sf::Vector2f(smilySprite.getPosition().x + ((2) * smilySprite.getGlobalBounds().width), 16 * sprite.getGlobalBounds().height));
        window.draw(dbsprite);

        ///draw test1 button
        t1sprite.setPosition(sf::Vector2f(dbsprite.getPosition().x + dbsprite.getGlobalBounds().width, 16 * sprite.getGlobalBounds().height));
        window.draw(t1sprite);

        ///draw test2 button
        t2sprite.setPosition(sf::Vector2f(t1sprite.getPosition().x + smilySprite.getGlobalBounds().width, 16 * sprite.getGlobalBounds().height));
        window.draw(t2sprite);

        ///draw test 3 button
        t3sprite.setPosition(sf::Vector2f(t2sprite.getPosition().x + smilySprite.getGlobalBounds().width, 16 * sprite.getGlobalBounds().height));
        window.draw(t3sprite);

        ///-----------------------------END DRAWING UI-------------------------------------------

        window.display();
        }


    return 0;
}