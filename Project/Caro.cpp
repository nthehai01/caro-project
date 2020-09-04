#include<iostream>
#include<windows.h>
#include<conio.h>
#include<string>
#include<fstream>
#include<time.h>
#include"Game.h"
using namespace std;
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	RECT r;
	GetWindowRect(consoleWindow, &r);
	MoveWindow(consoleWindow, r.left, r.top, 1300, 750, TRUE);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void Color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void GoToXY(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Caro()
{
	GoToXY(0, 3);
	cout << "                 ********************                               **                                *****        *****************               ******************" << endl;
	cout << "               *******************                                ******                              *****      *********************           **********************" << endl;
	cout << "             *****                                              **********                            *****    *****               *****       *****                *****" << endl;
	cout << "           *****                                              *****    *****                          *****  *****                           *****                    *****" << endl;
	cout << "         *****                                              *****        *****                        **********                             *****                    *****" << endl;
	cout << "       *****                                              *****            *****                      ********                               *****                    *****" << endl;
	cout << "     *****                                              *****                *****                    *****                                  *****                    *****" << endl;
	cout << "    *****                                             ******************************                  *****                                  *****                    *****" << endl;
	cout << "     *****                                          **********************************                *****                                  *****                    *****" << endl;
	cout << "       *****                                      *****                            *****              *****                                  *****                    *****" << endl;
	cout << "         *****                                  *****                                *****            *****                                  *****                    *****" << endl;
	cout << "           *****                              *****                                    *****          *****                                  *****                    *****" << endl;
	cout << "             *****                          *****                                        *****        *****                                    *****                *****" << endl;
	cout << "               ******************         *****                                            *****      *****                                      **********************" << endl;
	cout << "                 *******************    *****                                                *****    *****                                        ******************" << endl;
}
void ResetData(int a[][100], int n)
{
	int i, j;
	for (i = 0; i < 2 * n;)
	{
		for (j = 0; j < 4 * n;)
		{
			a[i][j] = 0;
			j = j + 4;
		}
		i = i + 2;
	}
}
void DrawBoard(int a[][100], int n, string s1, string s2, int d1, int d2, int i)
{
	int x, y;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			GoToXY(y, x);
			Color(240);
			if (a[x][y] == 0) cout << ".";
			else if (a[x][y] == 1)
			{
				Color(252);
				cout << "X";
			}
			else if (a[x][y] == 2)
			{
				Color(249);
				cout << "O";
			}
			y = y + 4;
		}
		x = x + 2;
	}
	GoToXY(115, 3);
	Color(240);
	cout << "SCORE BOARD";
	GoToXY(122, 5);
	cout << d2;
	GoToXY(120, 5);
	cout << '-';
	if ((d1 / 10) == 0) GoToXY(114 - s1.length(), 5);
	else GoToXY(113 - s1.length(), 5);
	Color(252);
	cout << char(219);
	Color(240);
	cout << ' ' << s1 << "  ";
	cout << d1;
	if ((d2 / 10) == 0) GoToXY(125, 5);
	else GoToXY(126, 5);
	cout << s2 << ' ';
	Color(249);
	cout << char(219);
	Color(240);
	GoToXY(114, 15);
	cout << "NOTIFICATION:  ";
	GoToXY(117, 10);
	cout << "TURN: ";
	if (i % 2 != 0)
	{
		Color(252);
		cout << s1;
	}
	else
	{
		Color(249);
		cout << s2;
	}
	Color(240);
}
void StartGame(int a[][100], int n, string s1, string s2, int d1, int d2, int i)
{
	system("cls");
	ResetData(a, n);
	DrawBoard(a, n, s1, s2, d1, d2, i);
}
void Move(int n, int& x, int& y, char c)
{
	switch (c)
	{
	case 'w': case 'W': case 72:
	{
		if (y > 0) y = y - 2;
		break;
	}
	case 's': case 'S': case 80:
	{
		if (y < 2 * (n - 1)) y = y + 2;
		break;
	}
	case 'd': case 'D': case 77:
	{
		if (x < 4 * (n - 1)) x = x + 4;
		break;
	}
	case 'a': case'A': case 75:
	{
		if (x > 0) x = x - 4;
		break;
	}
	}
	GoToXY(x, y);
}
int Law(int a[][100], int n, int k)
{
	int i, j, l, s;
	s = 0;
	if (k == 1) l = 2;
	else if (k == 2) l = 1;
	for (i = 0; i < 2 * (n - 1);)
	{
		for (j = 0; j <= 4 * (n - 1);)
		{
			if (j == 0)
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k && a[i][j + 16] == k)
				{
					if (a[i][j + 20] != l) return 1;
				}
			}
			else if (j == 4 * (n - 5))
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k)
				{
					if (a[i][j - 4] == 0 && a[i][j + 16] == 0) return 1;
					if (a[i][j - 4] != l && a[i][j + 16] == k) return 1;
				}
			}
			else
			{
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k)
				{
					if (a[i][j - 4] == 0 && a[i][j + 16] == 0) return 1;
				}
				if (a[i][j] == k && a[i][j + 4] == k && a[i][j + 8] == k && a[i][j + 12] == k && a[i][j + 16] == k)
				{
					if (a[i][j - 4] != l) return 1;
					if (a[i][j - 4] != l || a[i][j + 20] != l) return 1;
				}
			}
			j = j + 4;
		}
		i = i + 2;
	}
	for (j = 0; j <= 4 * (n - 1);)
	{
		for (i = 0; i < 2 * (n - 4);)
		{
			if (i == 0)
			{
				if (a[0][j] == k && a[2][j] == k && a[4][j] == k && a[6][j] == k && a[8][j] == k)
				{
					if (a[10][j] != l) return 1;
				}
			}
			else if (i == 2 * (n - 5))
			{
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k)
				{
					if (a[i - 2][j] == 0 && a[i + 8][j] == 0) return 1;
					if (a[i - 2][j] != l && a[i + 8][j] == k) return 1;
				}
			}
			else
			{
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k)
				{
					if (a[i - 2][j] == 0 && a[i + 8][j] == 0) return 1;
				}
				if (a[i][j] == k && a[i + 2][j] == k && a[i + 4][j] == k && a[i + 6][j] == k && a[i + 8][j] == k)
				{
					if (a[i - 2][j] != l || a[i + 10][j] != l) return 1;
				}
			}
			i = i + 2;
		}
		j = j + 4;
	}
	for (i = 0; i <= 2 * (n - 3);)
	{
		for (j = 0; j <= 4 * (n - 1);)
		{
			if (i == 0 || j == 0)
			{
				if (a[i][j] == k && a[i + 2][j + 4] == k && a[i + 4][j + 8] == k && a[i + 6][j + 12] == k)
				{
					if (a[i + 8][j + 16] == k)
					{
						if (a[i + 10][j + 20] == k || a[i + 10][j + 20] == 0) return 1;
					}
				}
			}
			else if (a[i][j] == k && a[i + 2][j + 4] == k && a[i + 4][j + 8] == k && a[i + 6][j + 12] == k)
			{
				if (a[i - 2][j - 4] == 0 && a[i + 8][j + 16] == 0) return 1;
				if (a[i - 2][j - 4] == k && a[i + 8][j + 16] == 0) return 1;
				if (a[i - 2][j - 4] == 0 && a[i + 8][j + 16] == k) return 1;
			}
			if (i == 0 || j == 0)
			{
				if (a[i][j] == k && a[i + 2][j - 4] == k && a[i + 4][j - 8] == k && a[i + 6][j - 12] == k)
				{
					if (a[i + 8][j - 16] == k)
					{
						if (a[i + 10][j - 20] == k || a[i + 10][j - 20] == 0) return 1;
					}
				}
			}
			else if (a[i][j] == k && a[i + 2][j - 4] == k && a[i + 4][j - 8] == k && a[i + 6][j - 12] == k)
			{
				if (a[i - 2][j + 4] == 0 && a[i + 8][j - 16] == 0) return 1;
				if (a[i - 2][j + 4] == k && a[i + 8][j - 16] == 0) return 1;
				if (a[i - 2][j + 4] == 0 && a[i + 8][j - 16] == k) return 1;
			}
			j = j + 4;
		}
		i = i + 2;
	}
	for (i = 0; i < 2 * n;)
	{
		for (j = 0; j < 4 * (n - 1);)
		{
			if (a[i][j] == 0)
			{
				s = 1;
				break;
			}
			j = j + 4;
		}
		if (s == 1) break;
		i = i + 2;
	}
	if (s == 0) return 0;
}
void SaveGame(int a[][100], int n, string s1, string s2, int d1, int d2, int t, int i, ofstream& fout)
{
	int x, y, k;
	fout << n << endl;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			fout << a[x][y] << ' ';
			y = y + 4;
		}
		x = x + 2;
		fout << endl;
	}
	k = 1;
	for (x = 0; x < s1.length(); x++)
	{
		if (s1[x] == ' ') k = k + 1;
	}
	fout << endl << k << endl << s1 << endl;
	k = 1;
	for (x = 0; x < s2.length(); x++)
	{
		if (s2[x] == ' ') k = k + 1;
	}
	fout << endl << k << endl << s2 << endl;
	fout << endl << d1 << ' ' << d2 << endl;
	fout << endl << t << endl;
	fout << endl << i;
}
void AskSave(int x, int y, int a[][100], int n, string s1, string s2, int d1, int d2, int t, int i)
{
	int x1, u,j;
	char c;
	string s;
	x1 = 105;
	u = 0;
	GoToXY(x1, 25);
	Color(240);
	cout << "\aDO YOU WANT TO SAVE BEFORE EXITING ?";
	Cout2(105);
	while (1)
	{
		GoToXY(x1, 27);
		c = _getch();
		Move2(x1, c);
		Cout2(x1);
		if (c == 13 || c == 32 || c == 8 || c == 27) break;
	}
	GoToXY(x1, 25);
	Color(240);
	cout << "                                        ";
	GoToXY(105, 27);
	cout << "                                        ";
	if (c == 8 || c == 27) GoToXY(x, y);
	else
	{
		if (x1 == 105)
		{
			GoToXY(114, 25);
			rewind(stdin);
			cout << "ENTER A NAME: ";
			getline(cin, s);
			ifstream FileIn;
			FileIn.open(s, ios_base::in);

			while (FileIn.fail() != true)
			{
				GoToXY(110, 24);
				cout << "\aTHIS FILE ALREADY EXISTS";
				GoToXY(105, 25);
				cout << "____DO YOU WANT TO REPLACE IT ?____";
				x1 = 125;
				Cout2(x1);
				while (1)
				{
					GoToXY(x1, 27);
					c = _getch();
					Move2(x1, c);
					Cout2(x1);
					if (c == 13) break;
				}
				if (x1 == 105)
				{
					u = 1;
					break;
				}
				else
				{
					Color(240);
					GoToXY(110, 24);
					cout << "                                                 ";
					GoToXY(105, 25);
					cout << "                                                 ";
					GoToXY(105, 27);
					cout << "                                                 ";
					GoToXY(114, 25);
					rewind(stdin);
					cout << "REENTER A NAME: ";
					getline(cin, s);
				}
				
			}
			FileIn.close();
			ofstream fout;
			fout.open(s, ios_base::out);
			SaveGame(a, n, s1, s2, d1, d2, t, i, fout);
			fout.close();
			Out(s, u);
		}
		Color(240);
		system("cls");
		Caro();
		GameMenu();
	}
}
void Out(string s, int u)
{
	string str[50];
	int h, m,j,l;
	char a[50], b[50];
	ifstream fin;
	fin.open("List.txt", ios_base::in);
	fin >> m;
	for (h = 0; h < m; h++)
	{
		rewind(stdin);
		getline(fin, str[h]);
	}
	if (u == 0)
	{
		str[m] = s;
		m = m + 1;
	}
	for (h = 0; h < m-1; h++)
	{
		for (j = h + 1; j < m; j++)
		{
			for (l = 0; l < str[h].length(); l++) a[l] = str[h][l];
			for (l = 0; l < str[j].length(); l++) b[l] = str[j][l];
			a[str[h].length()] = '\0';
			b[str[j].length()] = '\0';
			if (SoSanh(a, b) > 0)
			{
				str[h] = b;
				str[j] = a;
			}
		}
	}
	fin.close();
	ofstream fout;
	fout.open("List.txt", ios_base::in);
	fout << m << str[0] << endl;
	for (h = 1; h < m; h++)
	{
		fout << str[h] << endl;
	}
	fout.close();
}
void AskContinue(int x, int y, int a[][100], int n, string s1, string s2, int d1, int d2, int t, int& i)
{
	int x1;
	char c;
	x1 = 105;
	GoToXY(105, 25);
	cout << "_DO YOU WANT TO CONTINUE PLAYING ?_";
	Cout2(x1);
	while (1)
	{
		GoToXY(x1, 27);
		c = _getch();
		Move2(x1, c);
		Cout2(x1);
		if (c == 13 || c == 8) break;
	}
	if (c == 8)
	{
		GoToXY(105, 25);
		Color(240);
		cout << "                                        ";
		GoToXY(105, 27);
		cout << "                                        ";
		GoToXY(x, y);
	}
	else
	{
		Color(240);
		system("cls");
		if (x1 == 105)
		{
			StartGame(a, n, s1, s2, d1, d2, i);
			CheckBoard(a, n, s1, s2, d1, d2, t, i);
		}
		if (x1 == 125)
		{
			Caro();
			GameMenu();
		}
	}
}
void Process1(int x, int y, int a[][100], int n, string s1, string s2, int& d1, int& d2, int t, int& i)
{
	int k, l;
	if (a[y][x - 4] == 0)
	{
		Color(252);
		cout << 'X';
		GoToXY(123, 10);
		Color(240);
		cout << "                                           ";
		GoToXY(128, 15);
		cout << "                                           ";
		GoToXY(123, 10);
		Color(249);
		cout << s2;
		a[y][x - 4] = 1;
		i = i + 1;
		k = 1;
		l = Law(a, n, k);
		if (l == 1)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    " << s1 << " WIN    ";
			GoToXY(117, 10);
			Color(240);
			cout << "                                           ";
			d1 = d1 + 1;
			if ((d1 / 10) == 0) GoToXY(118, 5);
			else
			{
				GoToXY(115, 5);
				cout << ' ';
				GoToXY(113 - s1.length(), 5);
				Color(252);
				cout << char(219);
				Color(240);
				cout << ' ' << s1;
				GoToXY(117, 5);
			}
			cout << d1;
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
		if (l == 0)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    DRAW    ";
			GoToXY(117, 10);
			Color(240);
			cout << "                                           ";
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
	}
	else
	{
		GoToXY(128, 15);
		Color(240);
		cout << "\aPlease mark on another position...";
	}
}
void Process2(int x, int y, int a[][100], int n, string s1, string s2, int& d1, int& d2, int t, int& i)
{
	int k, l;
	if (a[y][x - 4] == 0)
	{
		Color(249);
		cout << 'O';
		GoToXY(123, 10);
		Color(240);
		cout << "                                           ";
		GoToXY(128, 15);
		cout << "                                           ";
		GoToXY(123, 10);
		Color(252);
		cout << s1;
		a[y][x - 4] = 2;
		i = i + 1;
		k = 2;
		l = Law(a, n, k);
		if (l == 1)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    " << s2 << " WIN    ";
			GoToXY(123, 10);
			Color(240);
			cout << "                                           ";
			d2 = d2 + 1;
			if ((d2 / 10) != 0)
			{
				GoToXY(125, 5);
				cout << ' ' << s2 << ' ';
				Color(249);
				cout << char(219);
				Color(240);
			}
			GoToXY(122, 5);
			cout << d2;
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
		if (l == 0)
		{
			GoToXY(128, 15);
			Color(46);
			cout << "\a    DRAW    ";
			GoToXY(117, 10);
			Color(240);
			cout << "                                           ";
			AskContinue(x, y, a, n, s1, s2, d1, d2, t, i);
		}
	}
	else
	{
		GoToXY(128, 15);
		Color(240);
		cout << "\aPlease mark on another position...";
	}

}
void CheckBoard(int a[][100], int n, string s1, string s2, int d1, int d2, int t, int i)
{
	int x, y, l, k;
	char c;
	GoToXY(99, 1);
	t = t + 1;
	cout << "_______________THE " << t;
	if (t / 10 == 1) cout << "th ";
	else
	{
		if (t % 10 == 1) cout << "st ";
		else if (t % 10 == 2) cout << "nd ";
		else if (t % 10 == 3) cout << "rd ";
		else cout << "th ";
	}
	cout << "MATCH_______________";
	x = (n - 1) * 2;
	y = n - 1;
	if (n % 2 == 0)
	{
		x = x - 2;
		y = y - 1;
	}
	GoToXY(x, y);
	while (1)
	{
		while (1)
		{
			c = _getch();
			if (c == 13 || c == 32)
			{
				x = x + 4;
				break;
			}
			else if (c == 8 || c == 27) AskSave(x, y, a, n, s1, s2, d1, d2, t, i);
			else Move(n, x, y, c);
		}
		if (i % 2 != 0) Process1(x, y, a, n, s1, s2, d1, d2, t, i);
		else Process2(x, y, a, n, s1, s2, d1, d2, t, i);
		if (x > 4 * (n - 1))
		{
			x = 4 * (n - 1);
			if (y == 0) y = y + 2;
			else if (y < 2 * (n - 1))
			{
				if (a[y + 2][4 * (n - 1)] == 0) y = y + 2;
				else y = y - 2;
			}
			else
			{
				if (a[2 * (n - 1)][4 * (n - 2)] == 0) x = x - 4;
				else if (a[2 * (n - 2)][4 * (n - 2)] == 0)
				{
					x = x - 4;
					y = y - 2;
				}
				else y = y - 2;
			}
		}
		GoToXY(x, y);
	}
}
void ClearScreen()
{
	int i;
	for (i = 25; i < 35; i++)
	{
		GoToXY(40, i);
		cout << "                                                                                  ";
	}
}
void Move1(int& y, char c)
{
	if (c == 's' || c == 'S' || c == 80)
	{
		if (y < 33) y = y + 2;
		else y = 25;
	}
	if (c == 'w' || c == 'W' || c == 72)
	{
		if (y > 25) y = y - 2;
		else y = 33;
	}
	GoToXY(75, y);
}
void Cout1(int y)
{
	GoToXY(75, 25);
	cout << "         NEW GAME         ";
	GoToXY(75, 27);
	cout << "         LOAD GAME        ";
	GoToXY(75, 29);
	cout << "           HELP           ";
	GoToXY(75, 31);
	cout << "           ABOUT          ";
	GoToXY(75, 33);
	cout << "           EXIT           ";
	GoToXY(75, y);
	Color(15);
	if(y == 25) cout << "         NEW GAME         ";
	if(y == 27) cout << "         LOAD GAME        ";
	if(y == 29) cout << "           HELP           ";
	if(y == 31) cout << "           ABOUT          ";
	if(y == 33) cout << "           EXIT           ";
	Color(240);
}
void Move2(int& x, char c)
{
	switch (c)
	case 'd': case 'D': case 'a': case 'A': case 77: case 75:
	{
		if (x == 89) x = 69;
		else if (x == 69) x = 89;
		if (x == 105) x = 125;
		else if (x == 125) x = 105;
	}
	GoToXY(x, 27);
}
void Cout2(int x)
{
	if (x == 69 || x == 105)
	{
		GoToXY(x + 20, 27);
		Color(240);
		cout << "       NO       ";
		GoToXY(x, 27);
		Color(15);
		cout << "       YES       ";
	}
	if (x == 89 || x == 125)
	{
		GoToXY(x - 20, 27);
		Color(240);
		cout << "       YES       ";
		GoToXY(x, 27);
		Color(15);
		cout << "       NO       ";
	}
}
string Standardized(string& s)
{
	int i, j, n;
	char s0[50];
	n = s.length();
	for (i = 0; i < n; i++) s0[i] = s[i];
	while (s0[0] == ' ')
	{
		for (i = 0; i < n - 1; i++) s0[i] = s0[i + 1];
		n = n - 1;
	}
	while (s0[n - 1] == ' ')
	{
		s0[n - 1] = '\0';
		n = n - 1;
	}
	for (i = 1; i < n - 1; i++)
	{
		if (s0[i] == ' ' && s0[i + 1] == ' ')
		{
			for (j = i + 1; j < n - 1; j++) s0[j] = s0[j + 1];
			n = n - 1;
			i = i - 1;
		}
	}
	s0[n] = '\0';
	s = s0;
	return s;
}
void NewGame(int& n, string& s1, string& s2)
{
	GoToXY(79, 25);
	cout << "ENTER BOARDSIZE: ";
	cin >> n;
	while (n <= 5 || n >= 21)
	{
		GoToXY(65, 25);
		cout << "\aPLEASE REENTER BOARDSIZE (5 < BOARDSIZE < 21): ";
		cin >> n;
		cout << "    ";
	}
	GoToXY(65, 25);
	cout << "                                                            ";
	GoToXY(77, 25);
	rewind(stdin);
	cout << "ENTER PLAYER_1's NAME: ";
	Color(252);
	getline(cin, s1);
	if (s1.length() == 0) s1 = "PLAYER_1";
	else Standardized(s1);
	GoToXY(77, 27);
	Color(240);
	rewind(stdin);
	cout << "ENTER PLAYER_2's NAME: ";
	Color(249);
	getline(cin, s2);
	if (s2.length() == 0) s2 = "PLAYER_2";
	else Standardized(s2);
}
void LoadGame(int a[][100], int& n, string& s1, string& s2, int& d1, int& d2, int& t, int& i, ifstream& fin)
{
	int x, y, k;
	string s[10];
	fin >> n;
	for (x = 0; x < 2 * n;)
	{
		for (y = 0; y < 4 * n;)
		{
			fin >> a[x][y];
			y = y + 4;
		}
		x = x + 2;
	}
	fin >> k;
	for (i = 0; i < k; i++)
	{
		fin >> s[i];
		if (i == k - 1) s1 = s1 + s[i];
		else s1 = s1 + s[i] + ' ';
	}
	fin >> k;
	for (i = 0; i < k; i++)
	{
		fin >> s[i];
		if (i == k - 1) s2 = s2 + s[i];
		else s2 = s2 + s[i] + ' ';
	}
	fin >> d1;
	fin >> d2;
	fin >> t;
	t = t - 1;
	fin >> i;
}
void GameMenu()
{
	int x, y, n, a[100][100], i, d1, d2, t, m, y1;
	string str[50];
	char c;
	string s1, s2, s;
	y = 25;
	while (1)
	{
		Color(240);
		ClearScreen();
		Cout1(y);
		while (1)
		{
			GoToXY(75, y);
			c = _getch();
			Move1(y, c);
			Cout1(y);
			if (c == 13) break;
		}
		ClearScreen();
		switch (y)
		{
		case 25:
		{
			NewGame(n, s1, s2);
			t = d1 = d2 = 0;
			srand(time(NULL));
			do i = rand();
			while (i < 0 || i > 5);
			StartGame(a, n, s1, s2, d1, d2, i);
			CheckBoard(a, n, s1, s2, d1, d2, t, i);
			break;
		}
		case 27:
		{
			
			ifstream fin;
			fin.open("List.txt", ios_base::in);
			fin >> m;
			if (m == 0) 
			{
				GoToXY(71, 25);
				cout << "\a___THERE AREN'T ANY FILES SAVED___";
				GoToXY(72, 26);
				system("pause");
			}
			else
			{
				GoToXY(71, 23);
				cout << "CHOOSE THE FILE YOU WANT TO OPEN";
				GoToXY(71, 35);
				cout << "Press ESC to return the Main Menu";
				for (int i = 0; i < m; i++)
				{
					rewind(stdin);
					getline(fin, str[i]);
				}
				i = 0;
				y1 = 25;
				Cout3(str, y1, i);
				while (1)
				{

					GoToXY(75, y1);
					c = _getch();
					Move3(c, y1, i, m);
					Cout3(str, y1, i);
					if (c == 13 || c == 27) break;
				}
				GoToXY(71, 23);
				cout << "                                      ";
				GoToXY(71, 35);
				cout << "                                      ";
				if (c == 13)
				{
					fin.close();
					ifstream fin1;
					fin1.open(str[i + (y1 - 25) / 2], ios_base::in);
					LoadGame(a, n, s1, s2, d1, d2, t, i, fin1);
					fin1.close();
					system("cls");
					DrawBoard(a, n, s1, s2, d1, d2, i);
					CheckBoard(a, n, s1, s2, d1, d2, t, i);
				}
			}
			break;
		}
		case 29:
		{
			Help();
			GoToXY(40, 34);
			system("pause");
			break;
		}
		case 31:
		{
			About();
			GoToXY(53, 34);
			system("pause");
			break;
		}
		case 33:
		{
			x = 89;
			GoToXY(67, 25);
			cout << "\aARE YOU SURE THAT YOU WANT TO EXIT GAME ?";
			Cout2(x);
			while (1)
			{
				GoToXY(x, 27);
				c = _getch();
				Move2(x, c);
				Cout2(x);
				if (c == 13) break;
			}
			if (x == 69) exit(0);
			else x = 75;
			break;
		}
		}
	}
}
void Help()
{
	ClearScreen();
	GoToXY(40, 25);
	cout << "_ Moving:             ";
	GoToXY(45, 26);
	cout << "Use 'W', 'A', 'S', 'D' or 'Navigation Keys' to move.";
	GoToXY(40, 27);
	cout << "_ Playing:            ";
	GoToXY(45, 28);
	cout << "After choosing position, press 'Enter' or 'Space' to mark ";
	Color(252);
	cout << "'X'";
	Color(240);
	cout << " or ";
	Color(249);
	cout << "'O'";
	Color(240);
	cout << '.';
	GoToXY(40, 29);
	cout << "_ While you are playing, if you want to exit the game,";
	GoToXY(43, 30);
	cout << "press 'Esc' or 'BackSapce' and save game if you want,";
	GoToXY(43, 31);
	cout << "press 'Esc' or 'BackSapce' again to continue playing.";

}
void About()
{
	GoToXY(53, 25);
	cout << "HO CHI MINH UNIVERSITY OF SCIENCE - FACULTY OF INFORMATION TECHNOLOGY";
	GoToXY(60, 27);
	cout << "19CTT1 - Group 8:";
	GoToXY(66, 28);
	cout << "1. Nguyen The Hai ............. 19120069";
	GoToXY(66, 29);
	cout << "2. Tran Duc Thuy .............. 19120138";
	GoToXY(66, 30);
	cout << "3. Nguyen Tien Toan ........... 19120399";
	GoToXY(66, 31);
	cout << "4. Phan Minh Triet ............ 19120039";
	GoToXY(66, 32);
	cout << "5. Huynh Ngoc Van ............. 19120155";
}
void Cout3(string str[], int y, int i)
{
	GoToXY(75, 25);
	cout << "                         ";
	GoToXY(87 - (str[i].length()-0.5)/ 2, 25);
	cout << str[i];
	GoToXY(75, 27);
	cout << "                         ";
	GoToXY(87 - (str[i+1].length()-0.5) / 2, 27);
	cout << str[i + 1];
	GoToXY(75, 29);
	cout << "                         ";
	GoToXY(87 - (str[i+2].length()-0.5) / 2, 29);
	cout << str[i + 2];
	GoToXY(75, 31);
	cout << "                         ";
	GoToXY(87 - (str[i+3].length()-0.5) / 2, 31);
	cout << str[i + 3];
	GoToXY(75, 33);
	cout << "                         ";
	GoToXY(87 - (str[i+4].length()-0.5) / 2, 33);
	cout << str[i + 4];
	GoToXY(75, y);
	Color(15);  
	cout << "                         ";
	if (y == 25)
	{
		GoToXY(87-(str[i].length()-0.5)/2, y);
		cout << str[i];
	}
	if (y == 27)
	{
		GoToXY(87 - (str[i+1].length() - 0.5) / 2, y);
		cout << str[i+1];
	}
	if (y == 29)
	{
		GoToXY(87 - (str[i+2].length() - 0.5) / 2, y);
		cout << str[i+2];
	}
	if (y == 31)
	{
		GoToXY(87 - (str[i+3].length() - 0.5) / 2, y);
		cout << str[i+3];
	}
	if (y == 33)
	{
		GoToXY(87 - (str[i+4].length() - 0.5) / 2, y);
		cout << str[i+4];
	}
	Color(240);
}
void Move3(char c, int &y, int &i, int m)
{
	if (m >= 5)
	{
		if (c == 72)
		{
			if (y > 25) y = y - 2;
			else if (y == 25)
			{
				if (i > 0) i = i - 1;
			}
		}
		if (c == 80)
		{
			if (y < 33) y = y + 2;
			else if (y == 33)
			{
				if (i < m - 5) i = i + 1;
			}
		}
	}
	else if (m == 2)
	{
		if (c == 72 && y == 27) y = 25;
		if (c == 80 && y == 25) y = 27;
	}
	else if (m == 3)
	{
		if (c == 72)
		{
			if (y > 25) y = y - 2;
		}
		if (c == 80)
		{
			if (y < 29) y = y + 2;
		}
	}
	else if (m == 4)
	{
		if (c == 72)
		{
			if (y > 25) y = y - 2;
		}
		if (c == 80)
		{
			if (y < 31) y = y + 2;
		}
	}
	GoToXY(75, y);
}
int SoSanh(char s1[], char s2[])
{
	int i, m, n, min, ds1 = 0, ds2 = 0;
	for (i = 0; i < strlen(s1); i++)
	{
		if (s1[i] != ' ') ds1 = ds1 + 1;
		else break;
	}
	for (i = 0; i < strlen(s2); i++)
	{
		if (s2[i] != ' ') ds2 = ds2 + 1;
		else break;
	}
	min = (ds1 < ds2) ? ds1 : ds2;
	for (int i = 0; i < min; i++)
	{
		m = n = 0;
		if (s1[i] > 64 && s1[i] < 96)
		{
			n = 1;
			s1[i] = s1[i] + 32;
		}
		if (s2[i] > 64 && s2[i] < 96)
		{
			m = 1;
			s2[i] = s2[i] + 32;
		}
		if ((s1[i] > s2[i]))
		{
			if (n == 1) s1[i] = s1[i] - 32;
			if (m == 1) s2[i] = s2[i] - 32;
			return 1; 
		}
		else if ((s1[i] < s2[i]))
		{
			if (n == 1) s1[i] = s1[i] - 32;
			if (m == 1) s2[i] = s2[i] - 32;
			return -1; 
		}
		if (n == 1) s1[i] = s1[i] - 32;
		if (m == 1) s2[i] = s2[i] - 32;
	}
	if (ds1 > ds2) return 1;
	else if (ds1 < ds2) return -1;
	if (strlen(s1)>strlen(s2)) return 1;
	else if (strlen(s1) < strlen(s2)) return -1;
	return 0; 
}