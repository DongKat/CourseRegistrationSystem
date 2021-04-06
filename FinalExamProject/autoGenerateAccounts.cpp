#include "CourseRegistrationSystem.h"

void autoGenerateAccounts(string filePath)
{
	_mkdir("./accounts"); //create account folder

	ifstream in;
	in.open(filePath);

	ofstream out;
	
	string ID;
	string socialID;
	string ignore_line;

	// No, Student ID, First name, Last name, Gender, Date of Birth, Social ID.


	while(!in.eof()) // run to the end of file
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
		out.open("../accounts/" + ID + ".txt");
		out << ID << endl << socialID << endl;
		out.close();

	}

	in.close();
}

int main()
{
	autoGenerateAccounts("student.txt");
}
