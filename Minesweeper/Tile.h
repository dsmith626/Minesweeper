//
// Created by David Smith on 4/9/20.
//

#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "Board.h"
using namespace std;

class Tile{
public:
    bool flagged;
    bool hidden;
    bool containsMine;
    bool drawzero;
    bool drawone;
    bool drawtwo;
    bool drawthree;
    bool drawfour;
    bool drawfive;
    bool drawsix;
    bool drawseven;
    bool draweight;
    vector<int> adjacent;
    Tile(){
        flagged = false;
        hidden = true;
        containsMine = false;
        drawzero = false;
        drawone = false;
        drawtwo = false;
        drawthree = false;
        drawfour = false;
        drawfive = false;
        drawsix = false;
        drawseven = false;
        draweight = false;
    }
    Tile(bool flag, bool hid, bool hasMine){
        flagged = flag;
        hidden = hid;
        containsMine = hasMine;
    }
    void flag(){
        flagged = !flagged;
    }
    void setFlagged(bool f){
        flagged = f;
    }
    void setHidden(bool b){
        hidden = b;
    }
    void setContainsMine(bool b){
        containsMine = b;
    }
    bool isMouseOver(sf::FloatRect sprite, sf::Vector2f mp){
        if(sprite.contains(mp)){
            return true;
        }
        return false;
    }
    bool hasMine(){
        return containsMine;
    }
    bool isFlagged(){
        return flagged;
    }
    bool isHidden(){
        return hidden;
    }
    vector<int> zeroroll(vector<int> open, int index, vector<Tile> tiles) {

        open.push_back(index);
        tiles.at(index).setHidden(false);

        vector<int> adjacent = tiles.at(index).adjacent;

        for (int i = 0; i < adjacent.size(); i++) {
            open.push_back(adjacent.at(i));
            if(!tiles.at(adjacent.at(i)).drawzero)
                tiles.at(adjacent.at(i)).setHidden(false);
            }
        for(int i = 0; i < adjacent.size(); i++) {
            if (tiles.at(adjacent.at(i)).isHidden() && !tiles.at(adjacent.at(i)).hasMine() &&
                !tiles.at(adjacent.at(i)).isFlagged() && tiles.at(adjacent.at(i)).drawzero)
                return tiles.at(adjacent.at(i)).zeroroll(open, adjacent.at(i), tiles);
        }

        return open;
    }

};