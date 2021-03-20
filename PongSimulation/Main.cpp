#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>
#include<future>
#include"Player.h"
#include"Score.h"

using namespace std;

mutex m;

//fungsi mengembalikan player
Player getHit(Player player) {
    m.lock();
    int* temp = new int;
    srand((int)temp);
    delete temp; 
    float result = rand() % 100 + 1; //random hit
    m.unlock();
    player.hit = result; //set hit player
    return player;
}

int main() {
    // Instance Score
    Score score;
    score.scorePlayerX = 0;
    score.scorePlayerY = 0;
    // instance player
    Player playerX = Player();
    const char* playerXName = playerX.setPlayerName(playerX.PlayerX);
    // copy player 
    Player playerY = playerX;
    const char* playerYName = playerY.setPlayerName(playerY.PlayerY);

    int scorePlayerX = 0, scorePlayerY = 0;
    float playerXHit{}, playerYHit;
    
    while (1) {
        //random giliran
        float first = rand() % 1;
    back:
        if (first == 0) {
            //thread pada fungsi gethit dengan parameter player 
            auto future_playerX = async(getHit, playerX);
            playerXHit = future_playerX.get().hit;
            //get data hit
            auto future_playerY = async(getHit, playerY);
            playerYHit = future_playerY.get().hit;
        }

        else if (first == 1) {
            auto future_playerY = async(getHit, playerY);
            playerYHit = future_playerY.get().hit;

            auto future_playerX = async(getHit, playerX);
            playerXHit = future_playerX.get().hit;
        }
        //jika hit kedua player lebih dari 50 maka kembali ke state back
        if (playerXHit > 50 && playerYHit > 50) {
            cout << "\nUpdate" << endl;
            cout << "Player Hit X : " << playerXHit << endl;
            cout << "Player Hit Y : " << playerYHit << endl;
            goto back;
        }
        //jika kedua player kurang dari 50 maka kembali ke state back
        else if (playerXHit <= 50 && playerYHit <= 50) {
            cout << "\nUpdate" << endl;
            cout << "Player Hit X : " << playerXHit << endl;
            cout << "Player Hit Y : " << playerYHit << endl;
            goto back;
        }
        //penambahan score
        else {
            if (playerXHit <= 50) {
                scorePlayerY++;
            }
            else {
                scorePlayerX++;
            }
        }

        cout << "\nPlayer Hit X : " << playerXHit << endl;
        cout << "Player Hit Y : " << playerYHit << endl;
        cout << "Score X : " << scorePlayerX << endl;
        cout << "Score Y : " << scorePlayerY << endl;
        //kondisi jika score salah satu pemain sama dengan 10 
        if (scorePlayerX == 10 || scorePlayerY == 10) {
            break;
        }
        //delay 2 detik
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
    
    if (scorePlayerX == 10) {
        cout << "\nPlayer X Wins this round" << endl;
        cout << "Score X : " << scorePlayerX<<endl;
        cout << "Score Y : " << scorePlayerY<<endl;
    }
    else if (scorePlayerY == 10) {
        cout << "\nPlayer Y Wins this round" << endl;
        cout << "Score X : " << scorePlayerX<<endl;
        cout << "Score Y : " << scorePlayerY<<endl;
    }

    system("pause");
    return 0;
}