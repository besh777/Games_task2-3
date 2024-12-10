#ifndef OOP_2_WORD_GAME_H
#define OOP_2_WORD_GAME_H
#include "BoardGame_Classes.h"
template <typename T>
class Word_Game : public Board<T>{
    vector<int> failed_words {0,0,0,0,0,0,0,0};
    vector<int> failed_reverse{0,0,0,0,0,0,0,0};
    vector<string> words;
    bool Word_compare(string word,string rword);
public:
    Word_Game();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win();
    bool is_draw();
    bool game_is_over();
};
template<typename T>
class Word_Player : public Player<T>{
public:
    Word_Player(string name, T symbol);
    void getmove(int &x,int &y);

};
template<typename T>
class Word_RandomPlayer : public RandomPlayer<T>{
    int random_word = 26;
    vector<char> alphabet{'a','b','c','d','e','f','j','h','i','g','k','l','m'
            ,'n','o','p','q','r','s','t','u','v','w','x','y','z'};
public:
    Word_RandomPlayer(T symbol);
    void getmove(int &x,int &y);
};

#include <iomanip>
#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;

template<typename T>
Word_Game<T> :: Word_Game() {
    this->rows = this->columns =3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; ++j) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    string line;
    ifstream infile("dic.txt");
    while (infile >> line){
        words.push_back(line);
    }
    infile.close();
}

template<typename T>
bool Word_Game<T>::update_board(int x, int y, T symbol) {
    if (!(x < 0||x > 2 || y < 0||y > 2) && (this->board[x][y] == 0 || symbol == 0)){
        if (symbol == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }else{
            this->n_moves++;
            this->board[x][y] = toupper(symbol);
        }
        return true;
    }
    return false;
}

template<typename T>
void Word_Game<T>::display_board() {
    for (int i = 0; i < this->rows; ++i) {
        cout<< "|";
        for (int j = 0; j < this->columns; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << "|";
            if (j == this->columns-1){
                cout << endl;
            }
        }
    }
    cout << "-------------------------" << endl;
}

template<typename T>
bool Word_Game<T>::is_win() {
    string Word;
    string Rword;
    for (int i = 0; i < this->rows; ++i) {
        if (this->board[i][0] != 0 &&
        this->board[i][1] != 0 && this->board[i][2] != 0){
            if (failed_words[i] == 0){
                for (int j = 0; j < 3; ++j) {
                    Word += this->board[i][j];
                }
                for (int j = 2; j >= 0 ; --j) {
                    Rword += this->board[i][j];
                }
                if (Word_compare(Word,Rword)){
                    return true;
                } else{
                    Word.clear();
                    Rword.clear();
                }
                failed_words[i] = 1;
                failed_reverse[i] = 1;
            }
        }
    }
    for (int i = 0; i < this->columns; ++i) {
        if (this->board[0][i] != 0 &&
            this->board[1][i] != 0 && this->board[2][i] != 0){
            if (failed_words[3+i] == 0){
                for (int j = 0; j < 3; ++j) {
                    Word += this->board[j][i];
                }
                for (int j = 2; j >= 0 ; --j) {
                    Rword += this->board[j][i];
                }
                if (Word_compare(Word,Rword)){
                    return true;
                }else{
                    Word.clear();
                    Rword.clear();
                }
                failed_words[3+i] = 1;
                failed_reverse[3+i] = 1;
            }
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (this->board[0][2*i] != 0 &&
            this->board[1][1] != 0 && this->board[2][2-(2*i)] != 0){
            if (failed_words[6+i] == 0){
                Word += this->board[0][2*i];
                Word += this->board[1][1];
                Word += this->board[2][2-(2*i)];

                Rword += this->board[2][2-(2*i)];
                Rword += this->board[1][1];
                Rword += this->board[0][2*i];
                if (Word_compare(Word,Rword)){
                    return true;
                }
                failed_words[6+i] = 1;
                failed_reverse[6+i] =1;
            }
        }
    }

    return false;
}

template<typename T>
bool Word_Game<T>::Word_compare(string word,string rword) {
    for (int i = 0; i < words.size(); ++i) {
        if (word == words[i] || rword == words[i]){
            return true;
        }
    }
    return false;
}

template<typename T>
bool Word_Game<T>::is_draw() {
    return (this->n_moves == 9 && !(is_win()));
}

template<typename T>
bool Word_Game<T>::game_is_over() {
    return (is_win() || is_draw());
}

template<typename T>
Word_Player<T> ::Word_Player(string name, T symbol) : Player<T>(name,symbol) {}

static bool first = true;

template<typename T>
void Word_Player<T>::getmove(int &x, int &y) {
    while (true){
        string position1;
        string position2;
        if (!first){
            cout << "choose x and y from 0 to 2 and separated it by enter:" << endl;
            cout << "x:" << endl;
        }
        getline(cin,position1);
        if (first){
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
    while (true){
        char letter;
        string cha;
        cout << "enter a letter to create a word:";
        getline(cin,cha);
        if (cha.size() == 1 && isalpha(cha[0])){
            letter = cha[0];
            this->symbol = letter;
            break;
        }
        cout << "wrong input" << endl;

    }

}

template<typename T>
Word_RandomPlayer<T> ::Word_RandomPlayer(T symbol) : RandomPlayer<T>(symbol){
    this->dimension = 3;
    srand(static_cast<unsigned int>(time(nullptr)));
}

template<typename T>
void Word_RandomPlayer<T>::getmove(int &x, int &y) {
    x = rand() % this->dimension;
    y = rand() % this->dimension;
    int i;
    i = rand() % random_word;
    this->symbol = alphabet[i];
}


#endif //OOP_2_WORD_GAME_H
