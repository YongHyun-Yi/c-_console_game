#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

void game_over_screen();

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int nTail, tailX[100], tailY[100];
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % (width - 4) + 2;
	fruitY = rand() % (height - 4) + 2;
	score = 0;
	nTail = 0;
}

void Draw()
{
	// system("cls"); // system - cmd 명령어를 쓸수있게해줌

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Screen_Cursor;
	Screen_Cursor.X = 0;
	Screen_Cursor.Y = 0;
	SetConsoleCursorPosition(h, Screen_Cursor);

	for (int i = 0; i < width; i++)
		cout << '#';
	cout << '\n';

	for (int i = 1; i < height - 1; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				cout << '#';
			else if (i == y && j == x)
			{
				SetConsoleTextAttribute(h, 175);
				cout << 'O';
				SetConsoleTextAttribute(h, 7);
			}
			else if (i == fruitY && j == fruitX)
			{
				SetConsoleTextAttribute(h, 207);
				cout << 'F';
				SetConsoleTextAttribute(h, 7);
			}
			else
			{
				bool print = false;

				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						SetConsoleTextAttribute(h, 63);
						cout << 'o';
						SetConsoleTextAttribute(h, 7);
						print = true;
					}
				}
				if (!print) cout << ' ';
			}
		}
		cout << '\n';
	}

	for (int i = 0; i < width; i++)
		cout << '#';
	cout << '\n' << '\n' << "Score: " << score;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
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
			
			case 'x':
				gameOver = true;
				break;
		}
	}
}

void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
		// 꼬리좌표를 먼저 헤드좌표로 갱신시키고나서
		// 헤드좌표를 방향에 따른 좌표로 갱신시켜준다
	for (int i = 1; i < nTail; i++)
	{
		// if (gameOver) break;

		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dir)
	{
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
	}

	if (x < 0 || x >= width || y < 0 || y >= height) // 밖으로 나가면 게임오버
	{
		gameOver = true;
		game_over_screen();
		return;
	}

	for (int k = 0; k < nTail; k++) // 꼬리와 부딫히면 게임오버
	{
		if (tailX[k] == x && tailY[k] == y)
		{
			gameOver = true;
			game_over_screen();
			return;
		}
	}
	
	if (x == fruitX && y == fruitY)
	{
		score++;
		nTail++;
		fruitX = rand() % (width - 4) + 2;
		fruitY = rand() % (height - 4) + 2;
	}
}

void title_screen()
{
	system("cls");
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "  << Snake Game >>  \n";
	cout << "                    \n";
	cout << "        by YHY_Games\n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "     Start - <y>    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
}

void game_over_screen()
{
	system("cls");
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "      GAME OVER     \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "   score:" << score <<'\n';
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "    Restart - <y>   \n";
	cout << "      Exit - <n>    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
	cout << "                    \n";
}

int main()
{
	system("mode con cols=20 lines=23 | title Game");

	title_screen();

	while (!(_kbhit() && _getch() == 'y'))
		Setup();
	
	while (true)
	{
		if (!gameOver)
		{
			Draw();
			Input();
			Logic();
			_sleep(50);
		}
		else
		{
			if (_kbhit())
			{
				switch (_getch())
				{
					case 'y':
						Setup();
						break;
					
					case 'n':
						return 0;
				}
			}
		}
	}
}