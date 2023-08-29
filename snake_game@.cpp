#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#include <limits>
using namespace std;
const int width = 20;
const int height = 20;
bool gameover;
int x, y,fruitX=0, fruitY=0, score;
int tailX[100],tailY[100];
int ntail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void board() 
{
  system("cls");
  for(int i=0;i<width;i++)
  {
    cout<<"*";
  }cout<<endl;
  for (int i = 0; i < height; i++) {
  for (int j = 0; j < width; j++) {
    if (j == 0 || j== width- 1)
        cout << "*";
    else if (i == y && j == x)
        cout << "O";
    else if (i == fruitY && j == fruitX)
        cout << "F";
    else{
        bool print =false;
     for(int k=0;k<ntail;k++)
        { 
          if(tailX[k]==j && tailY[k]==i)
          {
            cout<<"o";
            print=true;
          }   
        }
        if(!print)
          cout<<" ";
      }
    }
    cout << "\n"; 
  }
  for(int i=0;i<width;i++)
  {
    cout<<"*";
  }cout<<endl;
  cout<<"Score:"<<score<<endl;
}

void start() {
  gameover = false;
  dir = STOP;  
  x = width / 2;
  y = height / 2;
  fruitX = rand() % (width-1);
  fruitY = rand() % (height-1);
  score = 0;
  board();
}

void input() {
  if (_kbhit()) {
    char key=_getch();
    switch (key) {  
      case 'a':
        dir = LEFT;
        break;
      case 'd':
        dir = RIGHT;
        break;
      case 'w':
        dir = UP;
        break;
      case 's':
        dir = DOWN;
        break;
      case 'X':
        gameover = true;
        break;
      default:
      break;
    }
  }
}

void logic() {
 int prevx=tailX[0];
 int prevy=tailY[0];
int prev2x,prev2y;
tailX[0]=x;
tailY[0]=y;
for(int i=1; i<ntail;i++)
{
prev2x=tailX[i];
prev2y=tailY[i];
tailX[i]=prevx;
tailY[i]=prevy;
prevx=prev2x;
prevy=prev2y;
}
  switch (dir) {
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

  if (x >width || x < 0) 
   gameover = true;  // Snake hits the wall
  if(y > height || y < 0)
    gameover = true;
  for(int i=0;i<ntail;i++)
  {
    if(tailX[i]==x && tailY[i]==y)
    {gameover =true;}
  }
   if (x == fruitX && y == fruitY) 
   {
    score+=10;
    fruitX = rand() % (width-1);
    fruitY = rand() % (height-1); // Update fruit coordinates
    ntail++;
  }

}
void game()
{
    srand(time(nullptr));
    char ch;
    do {
        start();
        while (!gameover) {
            input();
            logic();
            board();
            if (dir == LEFT || dir == RIGHT) {
                Sleep(20);
            }
            Sleep(250);
            if (dir == UP || dir == DOWN) {
                Sleep(20);
            }
        }
        cout << "Want to play again? (y/n): ";
        cin.clear(); // Clear any previous input errors
        cin.sync();  // Clear the input buffer
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    cout << "Thanks for playing" << endl;
}

int main()
 {
  system("Color 0A");
  game();
   system("pause");
   return 0;
}
