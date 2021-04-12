#include "UI.h"

void Nocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void UnNocursortype() {
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = TRUE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void gotoxy(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void txtColor(int color) {
	HANDLE hConsoleColor;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setWindowFullSize() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void logo_moodle() {
	txtColor(11);
	gotoxy(58, 4);	cout << " __   __  _______  _______  ______   ___      _______ " << endl;
	gotoxy(58, 5);	cout << "|  |_|  ||       ||       ||      | |   |    |       |" << endl;
	gotoxy(58, 6);	cout << "|       ||   _   ||   _   ||  _    ||   |    |    ___|" << endl;
	gotoxy(58, 7);	cout << "|       ||  | |  ||  | |  || | |   ||   |    |   |___ " << endl;
	gotoxy(58, 8);	cout << "|       ||  |_|  ||  |_|  || |_|   ||   |___ |    ___|" << endl;
	gotoxy(58, 9);	cout << "| ||_|| ||       ||       ||       ||       ||   |___ " << endl;
	gotoxy(58, 10);	cout << "|_|   |_||_______||_______||______| |_______||_______|" << endl;

	gotoxy(50, 2);
	for (int i = 0; i < 70; ++i)
		cout << char(220);
	gotoxy(53, 3);
	for (int i = 0; i < 65; ++i)
		cout << char(205);
	gotoxy(53, 12);
	for (int i = 0; i < 65; ++i)
		cout << char(205);
	gotoxy(50, 13);
	for (int i = 0; i < 70; ++i)
		cout << char(223);

	gotoxy(52, 3);
	cout << char(201);
	gotoxy(52, 12);
	cout << char(200);

	gotoxy(117, 3);
	cout << char(187);
	gotoxy(117, 12);
	cout << char(188);

	for (int i = 4; i < 12; ++i)
	{
		gotoxy(52, i);
		cout << char(186);
	}
	for (int i = 4; i < 12; ++i)
	{
		gotoxy(117, i);
		cout << char(186);
	}
	for (int i = 3; i < 13; ++i)
	{
		gotoxy(50, i);
		cout << char(219);
	}
	for (int i = 3; i < 13; ++i)
	{
		gotoxy(119, i);
		cout << char(219);
	}

	cout << endl;
	cout << endl;


}

void loginUI() {
	txtColor(9);
	gotoxy(58, 14); cout << "  __ _ _               _                              " << endl;
	gotoxy(58, 15); cout << " / _(_) |      ____   | |                             " << endl;
	gotoxy(58, 16); cout << "| |_ _| |_    / __ \\  | |__   ___ _ __ ___  _   _ ___ " << endl;
	gotoxy(58, 17); cout << "|  _| | __|  / / _` | | '_ \\ / __| '_ ` _ \\| | | / __|" << endl;
	gotoxy(58, 18); cout << "| | | | |_  | | (_| | | | | | (__| | | | | | |_| \\__ \\" << endl;
	gotoxy(58, 19); cout << "|_| |_|\\__|  \\ \\__,_| |_| |_|\\___|_| |_| |_|\\__,_|___/" << endl;
	gotoxy(58, 20); cout << "              \\____/                                  " << endl;

	txtColor(14);
	// bigger bolder
	gotoxy(63, 21);
	for (int i = 0; i < 45; ++i)
		cout << char(220);

	for (int i = 22; i < 40; ++i) {
		gotoxy(63, i);
		cout << char(219);
	}

	for (int i = 22; i < 40; ++i) {
		gotoxy(107, i);
		cout << char(219);
	}

	gotoxy(63, 40);
	for (int i = 0; i < 45; ++i)
		cout << char(223);

	gotoxy(73, 22);	cout << " _    ___   ___ ___ _  _ ";
	gotoxy(73, 23);	cout << "| |  / _ \\ / __|_ _| \\| |";
	gotoxy(73, 24);	cout << "| |_| (_) | (_ || || .` |";
	gotoxy(73, 25);	cout << "|____\\___/ \\___|___|_|\\_|";

	txtColor(15);
	//smaller bolder 1 ( Username )
	gotoxy(68, 28);	cout << "USERNAME:";

	gotoxy(73, 29);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 29); cout << char(201);
	gotoxy(99, 29); cout << char(187);
	gotoxy(73, 30); cout << char(186);
	gotoxy(99, 30); cout << char(186);

	gotoxy(73, 31);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 31); cout << char(200);
	gotoxy(99, 31); cout << char(188);

	//smaller bolder 2 ( Password )
	gotoxy(68, 33);	cout << "PASSWORD:";

	gotoxy(73, 34);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 34); cout << char(201);
	gotoxy(99, 34); cout << char(187);
	gotoxy(73, 35); cout << char(186);
	gotoxy(99, 35); cout << char(186);

	gotoxy(73, 36);
	for (int i = 0; i < 27; ++i)
		cout << char(205);

	gotoxy(73, 36); cout << char(200);
	gotoxy(99, 36); cout << char(188);


	// input here
	gotoxy(75, 30);
	string a;
	cin >> a;

	gotoxy(75, 35);
	string b;
	cin >> b;

	bool check = false;

	if (check == true) {
		system("cls");
		logo_moodle();
	}
	else {
		txtColor(12);
		gotoxy(78, 38); cout << "*** INVALID ***";
		gotoxy(78, 41);
		txtColor(15);
	}
}

void fillBlackLogin() {
	gotoxy(66, 38);
	for (int i = 0; i < 40; ++i)
		cout << char(32);
	gotoxy(75, 30);
	for (int i = 0; i < 24; ++i)
		cout << char(32);
	gotoxy(75, 35);
	for (int i = 0; i < 24; ++i)
		cout << char(32);
}