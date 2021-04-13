#pragma once
#include "Library.h"
#include "Struct.h"

void Nocursortype();
void UnNocursortype();
void gotoxy(int x, int y);
void txtColor(int color);
void setWindowFullSize();
void logo_moodle();
void loginUI();

void readClassCSV(ifstream& classList, Students& student);

