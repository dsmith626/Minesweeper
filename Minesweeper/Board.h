//
// Created by David Smith on 4/9/20.
//
#include <iostream>
#include <cstdlib>
using namespace std;

class Board{
private:
    bool mines[400];
    int values[400];
public:
    Board(){
        for(int i = 0; i < 400; i++){
            mines[i] = false;
            values[i] = 0;
        }
        for(int i = 0; i < 50; i++){
            int index;
            index = (rand() % 400);
            if(mines[index])
                i--;
            else
                mines[index] = true;
        }


        for(int i = 0; i < 400; i++){
            if(mines[i])
                continue;
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if ((i + 1 < 400)) {
                    if (mines[i + 1]) {
                        values[i]++;
                    }
                }
            }
            if(i-1 >= 0 &&  (i % 25 != 0 || i-1==0)){
                if (mines[i - 1]) {
                    values[i]++;
                }
            }
            if(i+25 < 400){
                if(mines[i+25])
                    values[i]++;
            }
            if(i+24 < 400 && (i!= 0) && (i%25!=0)){
                if(mines[i+24])
                    values[i]++;
            }
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if(i+26 < 400 && (i+1 % 25 != 0)) {
                    if (mines[i + 26])
                        values[i]++;
                }
            }
            if(i-25 >= 0){
                if(mines[i-25])
                    values[i]++;
            }
            if(i-26 >= 0 && (i%25 != 0)) {
                if(mines[i-26])
                    values[i]++;
            }
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if (i - 24 >= 0 && (i + 1 % 25 != 0)) {
                    if (mines[i - 24])
                        values[i]++;
                }
            }
        }

    }
    Board(bool* mineboard){
        for(int i = 0; i < 400; i++){
            mines[i] = mineboard[i];
            values[i] = 0;
        }

        for(int i = 0; i < 400; i++){
            if(mineboard[i])
                continue;
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if ((i + 1 < 400)) {
                    if (mineboard[i + 1]) {
                        values[i]++;
                    }
                }
            }
            if(i-1 >= 0 &&  (i % 25 != 0 || i-1==0)){
                if (mineboard[i - 1]) {
                    values[i]++;
                }
            }
            if(i+25 < 400){
                if(mineboard[i+25])
                    values[i]++;
            }
            if(i+24 < 400 && (i!= 0) && (i%25!=0)){
                if(mineboard[i+24])
                    values[i]++;
            }
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if(i+26 < 400 && (i+1 % 25 != 0)) {
                    if (mineboard[i + 26])
                        values[i]++;
                }
            }
            if(i-25 >= 0){
                if(mineboard[i-25])
                    values[i]++;
            }
            if(i-26 >= 0 && (i%25 != 0)) {
                if(mineboard[i-26])
                    values[i]++;
            }
            if(i != 24 && i != 49 && i != 74 && i != 99 && i != 124 && i!= 149 && i != 174 && i != 199 && i != 224 && i != 249 && i != 274 && i != 299 && i != 324 && i != 349 && i != 374 && i != 399) {
                if (i - 24 >= 0 && (i + 1 % 25 != 0)) {
                    if (mineboard[i - 24])
                        values[i]++;
                }
            }
        }
    }
    bool* getMineBoard(){
        return mines;
    }
    int* getValueBoard(){
        return values;
    }
};