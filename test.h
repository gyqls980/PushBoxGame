#include <iostream>
#include <ncurses.h>
#include <locale.h>
#include <ncursesw/curses.h>
#include <fstream>

using namespace std;

#define MAX 100

int step = 0;
int push = 0;
class Count{
public:
    void StepCount();

    void PushCount();
};

class gameManager:public Count{
public:

  int a,b;
  int h_count=0, count =0;
  int what = 0;

    void DrawMap();
    void moveGame();
};
