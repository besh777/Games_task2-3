#ifndef OOP_2_PYRAMID_GAME_H
#define OOP_2_PYRAMID_GAME_H
#include "BoardGame_Classes.h"
template<typename T>
class Pyramid_Game : public Board<T>{
public:
    Pyramid_Game();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};
template <typename T>
class Pyramid_Player : public Player<T>{
public:
    Pyramid_Player(string name,T symbol);
    void getmove(int &x,int &y);
};
template <typename T>
class Pyramid_RandomPlayer : public RandomPlayer<T>{
public:
    Pyramid_RandomPlayer(T symbol);
    void getmove(int &x,int &y);
};

#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;



template<typename T>
Pyramid_Game<T> :: Pyramid_Game(){
    this->rows = 3;
    this->board = new char*[this->rows] ;
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[(2*i)+1];
        for (int j = 0; j < (2*i)+1; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template<typename T>
bool Pyramid_Game<T>::update_board(int x, int y, T symbol) {
    for (int i = 0; i < 3; ++i) {
        if (!(x < 0||x > 2 || y < 0||y > (2*x+1)) && (this->board[x][y] == 0 || symbol == 0)){
            if (symbol == 0){
                this->n_moves--;
                this->board[x][y] = 0;
            }else{
                this->n_moves++;
                this->board[x][y] = toupper(symbol);
            }
            return true;
        }
    }
    return false;
}

template<typename T>
void Pyramid_Game<T>::display_board() {
    cout << setw(17) << right;
    for (int i = 0; i < this->rows; ++i) {
        if (i == 1){
            cout << setw(9) << right;
        }
        cout << "|";
        for (int j = 0; j < (2*i)+1; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << "|";
            if (j == 2*i){
                cout << endl;
            }
        }
    }
    cout << "-----------------------------------------" << endl;
}

template<typename T>
bool Pyramid_Game<T>::is_win() {

    for (int i = 0; i < 3; ++i) {
        if (this->board[2][i]==this->board[2][i+1] && this->board[2][i+1]==
        this->board[2][i+2] &&this->board[2][i] != 0){
            return true;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (this->board[2*i][0]==this->board[1][1] && this->board[1][1]==
        this->board[i+1][2] &&this->board[2*i][0] != 0){
            return true;
        }
    }

    for (int i = 0; i < 2; ++i) {
        if (this->board[0][0]==this->board[1][2*i] && this->board[1][2*i]==
        this->board[2][4*i] &&this->board[0][0] != 0){
            return true;
        }
    }
    return false;
}

template<typename T>
bool Pyramid_Game<T>::is_draw() {
    return (this->n_moves == 9 && !(is_win()));
}
template<typename T>
bool Pyramid_Game<T>::game_is_over() {
    return (is_win() || is_draw());
}

static bool first = true;

template<typename T>
Pyramid_Player<T> ::Pyramid_Player(std::string name, T symbol) : Player<T>(name,symbol) {}
template<typename T>
void Pyramid_Player<T>::getmove(int &x, int &y) {
    while (true){
        string position1;
        string position2;
        if (!first){
            cout << "choose x and y from 0 to 2 and separated it by enter:" << endl;
            cout << "x:" << endl;
        }
        getline(cin,position1);

        if (position1.empty()){
            first = false;
            continue;
        }

        cout << "y:" << endl;
        getline(cin,position2);
        if ((position1.size() == 1 && position2.size() == 1)
            && (isdigit(position1[0]) && isdigit(position2[0]))){
            x = stoi(position1);
            y = stoi(position2);
            break;
        }
        cout << "wrong inputs" << endl;
    }
}

template<typename T>
Pyramid_RandomPlayer<T> ::Pyramid_RandomPlayer(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(nullptr)));
}

template<typename T>
void Pyramid_RandomPlayer<T>::getmove(int &x, int &y) {

    x = rand() % this->dimension;
    y = rand() % ((2*x)-1);
}

#endif //OOP_2_PYRAMID_GAME_H