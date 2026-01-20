#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <cstring>
using namespace std;

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// ---------------- GAME VARIABLES ----------------
int enemyY[2], enemyX[2], enemyFlag[2];
int carPos;
int score;

// ---------------- CAR DESIGN ----------------
char car[4][4] = {
    {' ','±','±',' '},
    {'±','±','±','±'},
    {' ','±','±',' '},
    {'±','±','±','±'}
};

// ---------------- LEADERBOARD ----------------
#define MAX_PLAYERS 10
struct Player {
    char name[20];
    int score;
};
Player leaderboard[MAX_PLAYERS];
int playerCount = 0;

// ---------------- MATCHMAKING QUEUE ----------------
#define MAX_QUEUE 6
struct MatchPlayer {
    char name[20];
};
MatchPlayer queuePlayers[MAX_QUEUE];
int front = 0, rear = -1;

// ---------------- BASIC FUNCTIONS ----------------
void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible) {
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}

// ---------------- INSTRUCTIONS ----------------
void instructions() {
    system("cls");
    cout << "\n========= GAME INSTRUCTIONS =========\n";
    cout << "A : Move Left\n";
    cout << "D : Move Right\n";
    cout << "ESC : Exit Game\n\n";
    cout << "DSA USED:\n";
    cout << "- Arrays (Enemies)\n";
    cout << "- Queue (Matchmaking)\n";
    cout << "- Sorting (Leaderboard)\n";
    cout << "- Comparison (Winner Decision)\n";
    cout << "\nPress any key...";
    getch();
}

// ---------------- LEADERBOARD ----------------
void sortLeaderboard() {
    for (int i = 0; i < playerCount - 1; i++)
        for (int j = 0; j < playerCount - i - 1; j++)
            if (leaderboard[j].score < leaderboard[j + 1].score)
                swap(leaderboard[j], leaderboard[j + 1]);
}

void showLeaderboard() {
    system("cls");
    sortLeaderboard();
    cout << "\n LEADERBOARD \n\n";
    for (int i = 0; i < playerCount; i++)
        cout << i + 1 << ". " << leaderboard[i].name
             << "  Score: " << leaderboard[i].score << endl;
    getch();
}

// ---------------- GAME FUNCTIONS ----------------
void drawBorder() {
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "±";
        gotoxy(WIN_WIDTH, i); cout << "±";
    }
}

void genEnemy(int i) {
    enemyX[i] = 18 + rand() % 30;
}

void drawEnemy(int i) {
    gotoxy(enemyX[i], enemyY[i]); cout << "****";
    gotoxy(enemyX[i], enemyY[i] + 1); cout << " ** ";
    gotoxy(enemyX[i], enemyY[i] + 2); cout << "****";
    gotoxy(enemyX[i], enemyY[i] + 3); cout << " ** ";
}

void eraseEnemy(int i) {
    for (int k = 0; k < 4; k++) {
        gotoxy(enemyX[i], enemyY[i] + k);
        cout << "    ";
    }
}

void drawCar() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            gotoxy(carPos + j, 22 + i);
            cout << car[i][j];
        }
}

void eraseCar() {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            gotoxy(carPos + j, 22 + i);
            cout << " ";
        }
}

int collision() {
    if (enemyY[0] + 4 >= 23)
        if (enemyX[0] + 4 >= carPos && enemyX[0] <= carPos + 4)
            return 1;
    return 0;
}

// ---------------- PLAY GAME (RETURNS SCORE) ----------------
int play() {
    carPos = WIN_WIDTH / 2;
    score = 0;

    enemyY[0] = enemyY[1] = 1;
    genEnemy(0);
    genEnemy(1);

    system("cls");
    drawBorder();

    while (1) {
        if (kbhit()) {
            char ch = getch();
            if ((ch == 'a' || ch == 'A') && carPos > 18) carPos -= 4;
            if ((ch == 'd' || ch == 'D') && carPos < 50) carPos += 4;
            if (ch == 27) break;
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);

        if (collision()) {
            system("cls");
            cout << "\nGAME OVER\nScore: " << score;
            Sleep(1000);
            return score;
        }

        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        enemyY[0]++;
        enemyY[1]++;

        if (enemyY[0] > SCREEN_HEIGHT - 4) {
            enemyY[0] = 1;
            genEnemy(0);
            score++;
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4) {
            enemyY[1] = 1;
            genEnemy(1);
            score++;
        }
    }
    return score;
}

// ---------------- MATCHMAKING ----------------
void resetQueue() {
    front = 0;
    rear = -1;
}

void joinMatchmaking() {
    if (rear == MAX_QUEUE - 1) {
        cout << "\nQueue Full!";
        getch();
        return;
    }

    rear++;
    cout << "\nEnter Player Name: ";
    cin >> queuePlayers[rear].name;

    if (rear - front + 1 >= 2) {
        char p1[20], p2[20];
        strcpy(p1, queuePlayers[front].name);
        strcpy(p2, queuePlayers[front + 1].name);

        front += 2;
        if (front > rear) resetQueue();

        int s1, s2;

        cout << "\n" << p1 << " TURN";
        Sleep(1000);
        s1 = play();

        cout << "\n" << p2 << " TURN";
        Sleep(1000);
        s2 = play();

        system("cls");
        cout << "\n MATCH RESULT \n";
        cout << p1 << " : " << s1 << endl;
        cout << p2 << " : " << s2 << endl;

        if (s1 > s2) cout << "\nWINNER: " << p1;
        else if (s2 > s1) cout << "\nWINNER: " << p2;
        else cout << "\nMATCH DRAW";

        strcpy(leaderboard[playerCount].name, p1);
        leaderboard[playerCount++].score = s1;

        strcpy(leaderboard[playerCount].name, p2);
        leaderboard[playerCount++].score = s2;

        getch();
    }
}

// ---------------- MAIN ----------------
int main() {
    setcursor(0);
    srand(time(0));

    while (1) {
        system("cls");
        cout << "\n===== CAR GAME (DSA BASED) =====\n";
        cout << "1. Start Game (Practice)\n";
        cout << "2. Instructions\n";
        cout << "3. View Leaderboard\n";
        cout << "4. Join Matchmaking\n";
        cout << "5. Exit\n";

        char ch = getch();
        if (ch == '1') play();
        else if (ch == '2') instructions();
        else if (ch == '3') showLeaderboard();
        else if (ch == '4') joinMatchmaking();
        else if (ch == '5') exit(0);
    }
}