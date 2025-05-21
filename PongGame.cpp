#include<iostream>
#include<windows.h>
#include <conio.h>
#include <string>
using namespace std;

#define RED 4
#define AQUA 3
#define LPURPULE 13

void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void DrawBoard() {
	char a = 219;
	gotoRowCol(7, 3);
	for (int i = 0; i <= 100; i++)
	{
		cout << a;
	}
	cout << endl;
	for (int i = 7; i <= 29; i++)
	{
		gotoRowCol(i, 3);
		cout << a;
		gotoRowCol(i, 103);
		cout << a << endl;
	}
	gotoRowCol(30, 3);
	for (int i = 0; i <= 100; i++)
	{
		cout << a;
	}
}

void DrawBall(int x, int y, char a) {
	gotoRowCol(x, y);
	cout << a << a;
}

void MoveBall(int& x, int& y, int& d, int& px1, int& py1, int& px2, int& py2) {
	switch (d)
	{
	case 0:
	{
		y++;
		break;
	}
	case 1:
	{
		y--;
		break;
	}
	case 2:
	{
		x--;
		y++;
		break;
	}
	case 3:
	{
		x++;
		y--;
		break;
	}
	case 4:
	{
		x--;
		y--;
		break;
	}
	case 5:
	{
		x++;
		y++;
		break;
	}
	default:
		break;
	}

}

void BounceBall(int& x, int& y, int& d, int& px1, int& py1, int& px2, int& py2) {

	if (x == 8 && y == 4)
	{
		d = 5;
	}
	else if (x == 8 && y == 101)
	{
		d = 3;
	}
	else if (x == 29 && y == 4)
	{
		d = 2;
	}
	else if (x == 29 && y == 101)
	{
		d = 4;
	}
	if (x >= 29 || x <= 8)
	{

		switch (d)
		{
		case 2:
		{
			d = 5;
			break;
		}
		case 3:
		{
			d = 4;
			break;
		}
		case 4:
		{
			d = 3;
			break;
		}
		case 5:
		{
			d = 2;
			break;
		}
		default:
			break;
		}
	}
	else if (y >= 101 || y <= 4)
	{

		switch (d)
		{
		case 0:
		{
			d = 1;
			break;
		}
		case 1:
		{
			d = 0;
			break;
		}
		case 2:
		{
			d = 4;
			break;
		}
		case 3:
		{
			d = 5;
			break;
		}
		case 4:
		{
			d = 2;
			break;
		}
		case 5:
		{
			d = 3;
			break;
		}
		default:
			break;
		}

	}
}

void PrintPaddle(int x, int y, char b) {

	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(x, y);
		cout << b;
		x++;
	}
}

bool CheckPaddle(int xBall, int xPaddleUpper, int yBall) {
	int xPaddlelower = xPaddleUpper + 6;
	if (xBall <= xPaddlelower && xBall >= xPaddleUpper && (yBall == 7 || yBall == 98))
	{
		return true;
	}
	else
		return false;
}

void BouncePaddle(int& d, int px1, int px2, int x, int y) {

	if (y == 98 && CheckPaddle(x, px2, y))
	{
		if (x < px2 + 2)
		{
			d = 4;
		}
		else if (x < px2 + 4)
		{
			d = 1;
		}
		else
		{
			d = 3;
		}
	}
	else if (y == 7 && CheckPaddle(x, px1, y))
	{
		if (x < px1 + 2)
		{
			d = 2;
		}
		else if (x < px1 + 4)
		{
			d = 0;
		}
		else
		{
			d = 5;
		}
	}
}

void MovePaddleUp(int& x, int& y, int speed) {
	char a = 219;
	if (x > 9)
	{
		PrintPaddle(x, y, ' ');
		x -= speed;
		PrintPaddle(x, y, a);
	}
}

void MovePaddleDown(int& x, int& y, int speed) {
	char a = 219;
	int px = x + 6;

	if (px < 30)
	{
		PrintPaddle(x, y, ' ');
		x += speed;
		PrintPaddle(x, y, a);
	}
}

void MovePaddleComputer(int& xPaddle, int& yPaddle, int xBall) {
	if (xBall < xPaddle)
	{
		MovePaddleUp(xPaddle, yPaddle, 1);
	}
	if (xBall > (xPaddle + 6))
	{
		MovePaddleDown(xPaddle, yPaddle, 1);
	}
}

int PressKeysAndPerform(int& px1, int& py1, int& px2, int& py2, bool& restart, bool VsComputer) {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		{
			if (!VsComputer)
				MovePaddleUp(px1, py1, 2);
			break;
		}
		case 's':
		case 'S':
		{
			if (!VsComputer)
				MovePaddleDown(px1, py1, 2);
			break;
		}
		case 'r':
		case 'R':
		{
			restart = true;
			break;
		}
		case 72:
		{
			// arrow up
			MovePaddleUp(px2, py2, 2);
			break;
		}
		case 80:
		{
			// arrow down
			MovePaddleDown(px2, py2, 2);
			break;
		}
		case 27:
		{
			// esc key to exit game 
			return 1;
			break;
		}
		case 32:
		{
			// space bar to pause game
			gotoRowCol(33, 0);
			SetClr(4, 0);
			system("pause");
			SetClr(3, 0);
			break;
		}
		default:
			break;
		}
	}
	return 0;
}

bool InvalidMaxScoreInput(string a) {
	int l = a.length();
	for (int i = 0; i < l; i++)
	{
		if (!isdigit(a[i]))
		{
			return true;
		}
	}
	return false;
}

void MaxScoreToWin(int& GoalToWin) {
	string MaxGoal;

	do {
		gotoRowCol(17, 50);
		cout << "                ";
		gotoRowCol(17, 50);
		cin >> MaxGoal;
		if (InvalidMaxScoreInput(MaxGoal))
		{
			gotoRowCol(19, 2);
			cout << "PLEASE ENTER A VALID NUMBER OF GOALS ";
		}
	} while (InvalidMaxScoreInput(MaxGoal));
	GoalToWin = stoi(MaxGoal);
}

void MaxScoreInputDisplay() {
	gotoRowCol(14, 36);
	cout << "--------------------------------";
	gotoRowCol(15, 36);
	cout << "|   ENTER WINNING GOAL COUNT   |";
	gotoRowCol(16, 36);
	cout << "--------------------------------";
	gotoRowCol(17, 36);
	cout << "|                              |";
	gotoRowCol(18, 36);
	cout << "--------------------------------";
}

void PlayerNameInputDisplay(bool VsComputer) {
	if (VsComputer)
	{
		gotoRowCol(14, 41);
		cout << "-----------------------";
		gotoRowCol(15, 41);
		cout << "|   ENTER YOUR NAME   |";
		gotoRowCol(16, 41);
		cout << "-----------------------";
		gotoRowCol(17, 41);
		cout << "|                     |";
		gotoRowCol(18, 41);
		cout << "-----------------------";
	}
	else if (!VsComputer)
	{
		gotoRowCol(14, 24);
		cout << "----------------";
		gotoRowCol(15, 24);
		cout << "|   PLAYER 1   |";
		gotoRowCol(16, 24);
		cout << "----------------";
		gotoRowCol(17, 24);
		cout << "|              |";
		gotoRowCol(18, 24);
		cout << "----------------";

		gotoRowCol(14, 67);
		cout << "----------------";
		gotoRowCol(15, 67);
		cout << "|   PLAYER 2   |";
		gotoRowCol(16, 67);
		cout << "----------------";
		gotoRowCol(17, 67);
		cout << "|              |";
		gotoRowCol(18, 67);
		cout << "----------------";
	}
}

void PlayerNameInput(string& playerName1, string& playerName2, bool VsComputer) {
	char a;

	gotoRowCol(12, 2);
	cout << "ENTER '1' TO WRITE PLAYER NAME ";
	gotoRowCol(13, 2);
	cout << "ANYTHING ELSE TO PROCEED : ";
	cin >> a;
	switch (a)
	{
	case '1':
	{
		PlayerNameInputDisplay(VsComputer);
		if (VsComputer)
		{
			gotoRowCol(17, 45);
			cin >> playerName2;
		}
		else
		{
			gotoRowCol(17, 28);
			cin >> playerName1;
			gotoRowCol(17, 71);
			cin >> playerName2;
		}
		break;
	}
	default:
		break;
	}

}

void DisplayLevels() {
	gotoRowCol(4, 33);
	cout << "SELECT THE DIFFICULTY LEVEL OF THE GAME \n";
	SetClr(3, 0);
	gotoRowCol(6, 13);
	cout << "-------------";
	gotoRowCol(7, 13);
	cout << "| LEVEL 'A' |";
	gotoRowCol(8, 13);
	cout << "-------------";
	gotoRowCol(9, 13);
	cout << "|   EASY    |";
	gotoRowCol(10, 13);
	cout << "-------------";

	gotoRowCol(6, 35);
	cout << "-------------";
	gotoRowCol(7, 35);
	cout << "| LEVEL 'B' |";
	gotoRowCol(8, 35);
	cout << "-------------";
	gotoRowCol(9, 35);
	cout << "|  MEDIUM   |";
	gotoRowCol(10, 35);
	cout << "-------------";

	gotoRowCol(6, 56);
	cout << "-------------";
	gotoRowCol(7, 56);
	cout << "| LEVEL 'C' |";
	gotoRowCol(8, 56);
	cout << "-------------";
	gotoRowCol(9, 56);
	cout << "|   HARD    |";
	gotoRowCol(10, 56);
	cout << "-------------";

	gotoRowCol(6, 78);
	cout << "----------------";
	gotoRowCol(7, 78);
	cout << "| CHOOSE LEVEL |";
	gotoRowCol(8, 78);
	cout << "----------------";
	gotoRowCol(9, 78);
	cout << "|              |";
	gotoRowCol(10, 78);
	cout << "----------------";
}

void ChooseDifficultyLevels(int& speed) {

	char a;
	do {
		gotoRowCol(9, 85);
		cin >> a;
		switch (a)
		{
		case 'a':
		case 'A':
			speed = 65;
			break;
		case 'b':
		case 'B':
			speed = 40;
			break;
		case 'c':
		case 'C':
			speed = 20;
			break;
		default:
			gotoRowCol(11, 2);
			cout << "CHOOSE A VALID OPTION \n";
			gotoRowCol(9, 85);
			cout << "         ";
			speed = -1;
			break;
		}
	} while (speed == -1);
}

void DrawBorders(int x) {
	char a = 219;
	gotoRowCol(0, 0);
	for (int i = 0; i <= 106; i++)
	{
		cout << '-';
	}
	cout << endl;
	for (int i = 1; i <= x; i++)
	{
		cout << '|';
		gotoRowCol(i, 106);
		cout << '|' << endl;
	}
	for (int i = 0; i <= 106; i++)
	{
		cout << '-';
	}
}

void PrintPlayer1Score(int score) {
	gotoRowCol(5, 22);
	cout << score;
}

void PrintPlayer2Score(int score) {
	gotoRowCol(5, 82);
	cout << score;
}

void DisplayForScores(int maxScore, string playerName1, string playerName2)
{
	SetClr(3, 0);
	gotoRowCol(1, 47);
	cout << "|  PONG GAME  |";

	gotoRowCol(2, 3);
	for (int i = 0; i <= 100; i++)
	{
		cout << '-';
	}
	gotoRowCol(3, 49);
	cout << "|  SCORE  |";

	gotoRowCol(3, 3);
	cout << "|";
	gotoRowCol(3, 20);
	cout << playerName1;

	gotoRowCol(3, 103);
	cout << "|";
	gotoRowCol(3, 79);
	cout << playerName2;
	gotoRowCol(4, 3);
	for (int i = 0; i <= 100; i++)
	{
		cout << '-';
	}
	gotoRowCol(5, 3);
	cout << "|";
	gotoRowCol(5, 103);
	cout << "|";
	gotoRowCol(5, 51);
	cout << "|";
	gotoRowCol(5, 57);
	cout << "|";
	gotoRowCol(5, 54);
	cout << maxScore;
	gotoRowCol(6, 3);
	for (int i = 0; i <= 100; i++)
	{
		cout << '-';
	}
}

void InputToPlayAgain(bool& restart) {
	SetClr(4, 0);
	gotoRowCol(34, 0);
	cout << "Enter 1 to Play the Game Again\nAnything else to Exit the Game :  ";
	char a;
	cin >> a;
	switch (a)
	{
	case '1':
	{
		restart = true;
		break;
	}
	default:
		break;
	}
}

void InputTwoPlayerOrVsComputer(bool& VsComputer) {
	char a;
	bool Invalid;

	do {
		Invalid = false;
		gotoRowCol(7, 52);
		cin >> a;
		switch (a)
		{
		case 'a':
		case 'A':
			VsComputer = true;
			break;
		case 'b':
		case 'B':
			VsComputer = false;
			break;
		default:
			gotoRowCol(10, 2);
			cout << "CHOOSE A VALID OPTION \n";
			gotoRowCol(7, 52);
			cout << "     ";
			Invalid = true;
			break;
		}

	} while (Invalid);

}

void TwoPlayerOrVsComputerDisplay() {

	SetClr(3, 0);
	gotoRowCol(5, 20);
	cout << "------------------------";
	gotoRowCol(6, 20);
	cout << "|       ENTER 'A'      |";
	gotoRowCol(7, 20);
	cout << "------------------------";
	gotoRowCol(8, 20);
	cout << "|  PLAYER VS COMPUTER  |";
	gotoRowCol(9, 20);
	cout << "------------------------";

	gotoRowCol(6, 50);
	cout << "--------";
	gotoRowCol(7, 50);
	cout << "|      |";
	gotoRowCol(8, 50);
	cout << "--------";

	gotoRowCol(5, 63);
	cout << "-----------------------";
	gotoRowCol(6, 63);
	cout << "|       ENTER 'B'     |";
	gotoRowCol(7, 63);
	cout << "-----------------------";
	gotoRowCol(8, 63);
	cout << "|   TWO PLAYER GAME   |";
	gotoRowCol(9, 63);
	cout << "-----------------------";
}

void GamePlay(bool& restart, bool& VsComputer, int GoalToWin, string Name1, string Name2, int speed) {
	DisplayForScores(4, Name1, Name2);
	SetClr(3, 0);
	DrawBorders(31);
	SetClr(13, 0);
	DrawBoard();
	char a = 219;
	// initialize paddle coordinates
	int p1x = 16;
	int p1y = 6;
	int p2x = 16;
	int p2y = 100;
	SetClr(3, 0);
	// initialize ball coordinates
	int x = 18;
	int y = 50;
	// initialize direction
	int d = 3;
	// initialize score 
	int score1 = 0, score2 = 0;
	PrintPlayer1Score(score1);
	PrintPlayer2Score(score2);

	gotoRowCol(34, 0);
	SetClr(4, 0);
	cout << "Press esc to exit the Game \n";
	gotoRowCol(35, 0);
	cout << "Enter 'R' to Restart the Game \n";
	SetClr(3, 0);

	bool GameEnd = false;
	do {
		PrintPaddle(p1x, p1y, a);
		PrintPaddle(p2x, p2y, a);
		GameEnd = false;
		bool ToSleepBall = false;
		gotoRowCol(33, 0);
		SetClr(4, 0);
		cout << "Press space bar to pause the Game \n";
		SetClr(3, 0);

		if ((y == 7 || y == 98))
		{
			BouncePaddle(d, p1x, p2x, x, y);
		}
		if (y == 4 && !CheckPaddle(x, p1x, y))
		{
			score2++;
			PrintPlayer2Score(score2);
			if (score2 == 4)
			{
				gotoRowCol(18, 43);
				cout << Name2 << " WINS THE GAME \n";
				GameEnd = true;
				InputToPlayAgain(restart);
				if (!restart)
				{
					DrawBall(x, y, ' ');
					gotoRowCol(18, 43);
					cout << "                             ";
					gotoRowCol(18, 47);
					SetClr(3, 0);
					cout << "GAME OVER ^O^ \n";
					break;
				}
			}
			x = 18;
			y = 50;
			ToSleepBall = true;
		}
		if (y == 101 && !CheckPaddle(y, p1y, y))
		{
			score1++;
			PrintPlayer1Score(score1);
			if (score1 == 4)
			{
				gotoRowCol(18, 43);
				cout << Name1 << " WINS THE GAME \n";
				GameEnd = true;
				InputToPlayAgain(restart);
				if (!restart)
				{
					DrawBall(x, y, ' ');
					gotoRowCol(18, 43);
					cout << "                             ";
					gotoRowCol(18, 47);
					SetClr(3, 0);
					cout << "GAME OVER ^O^ \n";
					break;
				}
			}
			x = 18;
			y = 50;
			ToSleepBall = true;
		}

		DrawBall(x, y, a);
		if (ToSleepBall)
		{
			Sleep(300);
		}
		Sleep(speed);
		int a = PressKeysAndPerform(p1x, p1y, p2x, p2y, restart, VsComputer);
		if (restart)
		{
			system("cls");
			break;
		}
		if (VsComputer)
		{
			MovePaddleComputer(p1x, p1y, x);
		}
		if (a == 1)
		{
			DrawBall(x, y, ' ');
			gotoRowCol(18, 47);
			cout << "GAME OVER ^O^ \n";
			break;
		}

		DrawBall(x, y, ' ');
		MoveBall(x, y, d, p1x, p1y, p2x, p2y);
		BounceBall(x, y, d, p1x, p1y, p2x, p2y);
	} while (!GameEnd);
}

void GameSetup(bool& VsComputer, string& Name1, string& Name2, int& GoalToWin, int& speed) {

	SetClr(13, 0);
	DrawBorders(20);
	SetClr(3, 0);
	gotoRowCol(1, 41);
	cout << "------------------------";
	gotoRowCol(2, 41);
	cout << "| WELCOME TO PONG GAME |";
	gotoRowCol(3, 41);
	cout << "------------------------";

	TwoPlayerOrVsComputerDisplay();
	InputTwoPlayerOrVsComputer(VsComputer);

	Name1 = "Player1";
	Name2 = "Player2";
	if (VsComputer)
	{
		Name1 = "Computer";
		Name2 = "Player";
	}

	PlayerNameInput(Name1, Name2, VsComputer);
	system("cls");

	SetClr(13, 0);
	DrawBorders(20);
	SetClr(3, 0);
	gotoRowCol(1, 41);
	cout << "------------------------";
	gotoRowCol(2, 41);
	cout << "| WELCOME TO PONG GAME |";
	gotoRowCol(3, 41);
	cout << "------------------------";
	DisplayLevels();
	ChooseDifficultyLevels(speed);
	MaxScoreInputDisplay();
	MaxScoreToWin(GoalToWin);
	system("cls");

}

int main() {
	string Name1;
	string Name2;
	int GoalToWin;
	int speed;
	bool VsComputer;
	bool restart;
	do {
		restart = false;
		GameSetup(VsComputer, Name1, Name2, GoalToWin, speed);
		GamePlay(restart, VsComputer, GoalToWin, Name1, Name2, speed);

	} while (restart);
	gotoRowCol(36, 0);
	return 0;
}