#include "AutoGenerate.h"

void autoGenerateStudentAccounts(string filePath)
{
	_mkdir("Student Accounts"); //create account folder

	ifstream in;
	in.open(filePath);

	ofstream out;

	string ID;
	string socialID;
	string ignore_line;

	// No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.

	while (!in.eof()) // run to the end of file
	{
		// GET
		getline(in, ignore_line, ','); // Ignore No

		getline(in, ID, ','); // get student ID

		getline(in, ignore_line, ',');	// Ignore fisrt name
		getline(in, ignore_line, ',');	// Ignore last name
		getline(in, ignore_line, ',');	// Ignore gender
		getline(in, ignore_line, ',');	// Ignore data of birth

		getline(in, socialID);

		// OUT
		out.open("Student Accounts/" + ID);
		out << ID << endl << socialID << endl;
		out.close();
	}

	in.close();
}

void autoGenerateStaffProfiles(string filePath)
{
	_mkdir("Staff Profiles"); //create account folder

	ifstream in;
	in.open(filePath);

	ofstream out;

	string username;
	string name;
	string gender;
	string day;
	string month;
	string year;
	string socialID;
	string phoneNumber;
	string ignore_line;

	// No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.

	while (!in.eof()) // run to the end of file
	{
		// GET
		getline(in, username, ',');
		getline(in, name, ',');
		getline(in, gender, ',');
		getline(in, day, '/');
		getline(in, month, '/');
		getline(in, year, ',');
		getline(in, socialID, ',');
		getline(in, phoneNumber);

		// OUT
		out.open("Staff Profiles/" + username);
		out << name << endl << gender << endl;
		out << day << "/" << month << "/" << year << endl;
		out << socialID << endl << phoneNumber << endl;
		out.close();
	}

	in.close();
}

void autoGenerateStudentProfiles(string filePath)
{
	_mkdir("Student Profiles"); //create account folder

	ifstream in;
	in.open(filePath);

	ofstream out;

	string no;
	string ID;
	string firstName;
	string lastName;
	string gender;
	string day;
	string month;
	string year;
	string socialID;

	// No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.

	while (!in.eof()) // run to the end of file
	{
		// GET
		getline(in, no, ',');
		getline(in, ID, ',');
		getline(in, firstName, ',');
		getline(in, lastName, ',');
		getline(in, gender, ',');
		getline(in, day, '/');
		getline(in, month, '/');
		getline(in, year, ',');
		getline(in, socialID);

		// OUT
		out.open("Student Profiles/" + ID);
		out << no << endl << ID << endl << firstName << endl << lastName << endl << gender << endl;
		out << day << "/" << month << "/" << year << endl;
		out << socialID << endl;
		out.close();
	}

	in.close();
}