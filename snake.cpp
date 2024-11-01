#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver, gameWon;
const int breadth = 40;
const int length = 20;
int x, y, fruitX, fruitY, score;
int target1 = 30;
int target2 = 50;
int target3 = 80;
int tailX[100], tailY[100];
int tail;
int level;
int speed;

enum eDirection { 
    STOP = 0, LEFT, RIGHT, UP, DOWN
};
eDirection dir;

void goToXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void showTextWithDelay(string text, int delayMs) {
    for (char c : text) {
        cout << c;
        Sleep(delayMs);
    }
}
void instructionsScreen() {
    system("cls");  
    showTextWithDelay("############################################\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#         Welcome to the Snake Game!       #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#               Instructions:              #\n", 10);
    showTextWithDelay("#               -------------              #\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#  Move the snake using the following keys:#\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#       W - Move Up                        #\n", 10);
    showTextWithDelay("#       S - Move Down                      #\n", 10);
    showTextWithDelay("#       A - Move Left                      #\n", 10);
    showTextWithDelay("#       D - Move Right                     #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#         Press 'X' to quit the game.      #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("############################################\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#               Game Levels:               #\n", 10);
    showTextWithDelay("#               ------------               #\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#   Level 1:                               #\n", 10);
    showTextWithDelay("#     - Boundary collision enabled.        #\n", 10);
    showTextWithDelay("#     - No increase in snake length.       #\n", 10);
    showTextWithDelay("#     - Score 30 to upgrade to Level 2.    #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#   Level 2:                               #\n", 10);
    showTextWithDelay("#     - Speed increases gradually.         #\n", 10);
    showTextWithDelay("#     - Boundary collision enabled.        #\n", 10);
    showTextWithDelay("#     - No increase in snake length.       #\n", 10);
    showTextWithDelay("#     - Score 50 to upgrade to Level 3.    #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#   Level 3:                               #\n", 10);
    showTextWithDelay("#     - Snake length increase on eating.   #\n", 10);
    showTextWithDelay("#     - Opposite direction keys disabled.  #\n", 10);
    showTextWithDelay("#     - Self collision enabled.            #\n", 10);
    showTextWithDelay("#     - Speed increases gradually.         #\n", 10);
    showTextWithDelay("#     - Boundary collision enabled.        #\n", 10);
    showTextWithDelay("#     - Score 80 to win the game!          #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("############################################\n", 5);
    showTextWithDelay("     Press enter to start the game...     \n", 10);
    
    cin.get();
}

void gameOverScreen() {
    system("cls");
    cout <<           "\n                 Level: " << level << endl;
    cout <<           "                 Score: " << score << endl << "\n";
    showTextWithDelay("############################################\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#             G A M E   O V E R            #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#          Your journey ends here.         #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#         Want to try again? (Y/N):        #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("############################################\n", 5);
}

void congratulationsScreen() {
    system("cls");
    cout <<           "\n                 Level: " << level << endl;
    cout <<           "                 Score: " << score << endl << "\n";
    showTextWithDelay("############################################\n", 5);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#      C O N G R A T U L A T I O N S       #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#     You've conquered all the levels!     #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("#         Want to play again? (Y/N):       #\n", 10);
    showTextWithDelay("#                                          #\n", 5);
    showTextWithDelay("############################################\n", 5);
}

void setup(){
    gameOver = false;
    gameWon = false;
    dir = STOP;
    x = breadth / 2;
    y = length / 2;
    fruitX = (rand() % (breadth - 2)) + 1;
    fruitY = (rand() % (length - 2)) + 1;
    score = 0;
    speed = 200;
    tail = 0;
    level = 1;
}

void draw(){
    goToXY(0, 0);
    cout << "\n                  Level:" << level << endl <<"\n";
    for (int i = 0; i <= breadth-1; i++){//0 to 19 horizontally
        cout << "#";
    }
    cout << endl;
 
    for (int i = 1; i <= length-2; i++){//1 to 18 vertically
        cout << "#";//0 of each line
        for (int j = 1; j <= breadth-2; j++){//1 to 18 horizontally
            if (i == y && j == x){
                cout << "O";
            }
            else if (i == fruitY && j == fruitX){
                cout << "*";
            }
            else{
                bool print = false;
                for (int k = 0; k < tail; k++){
                    if (tailX[k] == j && tailY[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                if (!print){
                    cout << " ";
                }
            }
        }
        cout << "#";//19 of each line
        cout << endl;
    }
 
    for (int i = 0; i <= breadth-1; i++){//0 to 19 horizontally
        cout << "#";
    }
    cout << endl;
    cout << "\n                  Score:" << score << endl <<"\n";
    if(level==1){
    cout << "        Score " << target1 << " to reach Level-2!" << endl;
    }
    if(level==2){
    cout << "        Score " << target2 << " to reach Level-3!" << endl;
    }
    if(level==3){
    cout << "        Score " << target3 << " to win the game!" << endl;
    }
    cout << "         Press X to quit the game." << endl;
}

void input(){
    if (_kbhit()){
        switch (_getch()){
            case 'a':
                if (dir != RIGHT || level < 3){
                    dir = LEFT;
                }
                break;
            case 'd':
                if (dir != LEFT || level < 3){
                    dir = RIGHT;
                }
                break;
            case 'w':
                if (dir != DOWN || level < 3){
                    dir = UP;
                }
                break;
            case 's':
                if (dir != UP || level < 3){
                    dir = DOWN;
                }
                break;
            case 'x':
                system("cls");
                gameOver = true;
                break;
        }
    }
}

void run(){
    for (int i = tail; i > 0; i--){
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    tailX[0] = x;
    tailY[0] = y;
    switch (dir){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
    }
    if (x >= breadth || x <= 0 || y >= length || y <= 0){
        system("cls");
        gameOver = true;
    }
    if(level==3){
        for (int i = 0; i < tail; i++){
            if (tailX[i] == x && tailY[i] == y){
                system("cls");
                gameOver = true;
            }
        }	
    }
    if (x == fruitX && y == fruitY){
        score += 10;
        if(level==2 || level==3){
            speed-= 8;
        }
        fruitX = (rand() % (breadth - 2)) + 1;
        fruitY = (rand() % (length - 2)) + 1;
        if (level == 3){
            tail++;  
        }
        if (score >= target1 && level == 1) {
            level = 2;
            score = 0;
            speed = 140;  
        } 
        else if (score >= target2 && level == 2) {
            level = 3;
            score = 0;
            speed = 75;  
        } 
        else if (score >= target3 && level == 3) {
            system("cls");
            gameWon = true;
        }
    }
}

int main(){
    char decision;
    instructionsScreen();
    do {
        system("cls");
        setup();
        while (!gameOver) {
            draw();
            input();
            run();
            Sleep(speed);  

            if (gameOver || gameWon) {
                if (gameOver){
                    cout << "                    Score: \n" << score << endl;
                    gameOverScreen();
                }
                else if (gameWon) {
                    cout << "                    Score: \n" << score << endl;
                    congratulationsScreen();
                }
                cin >> decision;
                if (decision == 'Y' || decision == 'y') {
                    gameOver = false;
                    break;  
                } 
                else if (decision == 'N' || decision == 'n') {
                    cout<< "\n         It's sad to see you go :(" << endl;
                    break;  
                } 
                else {
                    cout << "\n         Invalid input! Exiting game..." << endl;
                    break;
                }
            }
        }
    } while (decision == 'Y' || decision == 'y');  
    return 0;
}