#include "Functions.h"

void readClassCSV(ifstream& classList, Students& student)
{
	//trash function
	// Temp function only read one row for a single student
	string temp;
	// Read the Data from the file as String Vector
	getline(classList, temp, ',');
	student.no = stoi(temp);
	getline(classList, temp, ',');
	student.ID = stoi(temp);
	getline(classList, temp, ',');
	student.firstName = temp;
	getline(classList, temp, ',');
	student.lastName = temp;
	getline(classList, temp, ',');
	student.gender = stoi(temp);
	getline(classList, temp, ',');
	//dateofbirth
	getline(classList, temp);
	student.idSocial = temp;
}

void createStudent(ifstream& classList, Students& student) // Read CSV file for student's info
{
	//trash function
	// Temp function only read one row for a single student
	string temp;
	// Read the Data from the file as String Vector
	// Ignore first line
	getline(classList, temp);

	getline(classList, temp, ',');
	student.no = stoi(temp);
	getline(classList, temp, ',');
	student.ID = stoi(temp);
	getline(classList, temp, ',');
	student.firstName = temp;
	getline(classList, temp, ',');
	student.lastName = temp;
	getline(classList, temp, ',');
	student.gender = stoi(temp);

	getline(classList, temp, '/');
	student.dateOfBirth.day = stoi(temp);
	getline(classList, temp, '/');
	student.dateOfBirth.month = stoi(temp);
	getline(classList, temp, ',');
	student.dateOfBirth.year = stoi(temp);

	getline(classList, temp);
	student.idSocial = temp;
}

void createStudentList(Students*& pHead, string csvFileName)
{
	//trash function
	ifstream file(csvFileName);
	Students* pCur = nullptr;
	while (!file.eof())
	{
		if (pHead == nullptr)
		{
			pHead = new Students;
			pCur = pHead;
			pCur->prev = nullptr;
		}
		else
		{
			pCur->next = new Students;
			pCur->next->prev = pCur;
			pCur = pCur->next;
		}
		readClassCSV(file, *pCur);
		pCur->next = nullptr;
	}
	file.close();
}


void exportCourseStudent(Courses Course)
{
	// copy course scoreboard to outside file
	string scoreboard_dir = Schoolyear + "./Semester/Sem " + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv";
	string temp;
	ifstream target(scoreboard_dir);
	ofstream file(Course.courseID + "_Scoreboard.csv");
	while (!target.eof())
	{
		getline(target, temp);
		file << temp;
	}
}

void viewScoreboard(Courses Course)
{
	// view Course scoreboard
	ifstream file("School year/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv");
	string temp;
	while (file.eof())
	{
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp << " | ";
		getline(file, temp, ',');	cout << temp;
		cout << endl;
	}
}

void importScoreboard(Courses Course, string file_name)
{
	// copy outside file to course scoreboard
	string target_dir = Schoolyear + "./Semester/Sem " + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv";
	string line;
	ifstream file(file_name);
	ofstream target(target_dir);
	while (!file.eof())
	{
		getline(file, line);
		target << line;
	}
}

void updateStudentResult(Courses Course, string studentID, Scores newScore)
{
	string oldDir, newDir, temp;
	bool recordFlag = false; // check if student record is update. if updated -> true
	oldDir = "./" + Schoolyear + "/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard.csv";
	newDir = "./" + Schoolyear + "/Semester/Sem" + to_string(Course.sem) + "/" + Course.courseID + "/Scoreboard_new.csv";
	ifstream oldFile(oldDir);
	ofstream newFile(newDir);
	while (!oldFile.eof())
	{
		if (!recordFlag)
		{
			for (int i = 0; i < 8; i++)
			{
				if (i == 7)
				{
					getline(oldFile, temp);
					newFile << temp << "\n";
				}
				getline(oldFile, temp, ',');
				newFile << temp << ",";
				if (temp == studentID)
				{
					getline(oldFile, temp, ',');
					newFile << temp << ",";
					getline(oldFile, temp, ',');
					newFile << temp << ",";
					newFile << newScore.Midterm << "," << newScore.Final << "," << newScore.Bonus << "," << newScore.GPA << "\n";
					getline(oldFile, temp);
					recordFlag = true;
					break;
				}
			}
		}
		else
		{
			getline(oldFile, temp);
			newFile << temp << "\n";
		}
	}
	oldFile.close();
	newFile.close();
	remove(oldDir.c_str());
	rename(newDir.c_str(), oldDir.c_str());
}

void viewClassScoreboard(Classes Class) // Require changing UI
{
	// Read class's students list Students.txt
	// Go to each studentID folder, read score from Course Sem 1/2/3
	// Problem many students with different courses

	string studentID;
	string line, temp;
	float overall_GPA;
	int count;
	ifstream student_list("./" + Schoolyear + "/Classes/" + Class.className + "/Students.txt");
	ifstream file;

	cout << "Student ID\t";
	cout << "Student Name\t";
	cout << "Course ID\t";
	cout << "Course final score";
	cout << "Course GPA\t";
	cout << "Overall GPA\n";


	while (!student_list.eof())
	{
		getline(student_list, studentID);

		cout << studentID << "\t";
		file.open("./" + Schoolyear + "/Classes/" + Class.className + "/" + studentID + "/Profile.txt"); // Get student name with ID
		getline(file, temp);
		cout << temp << "\t"; // Assume name is first row
		file.close();
		
		file.open("./" + Schoolyear + "/Classes/" + Class.className + "/" + studentID + "/Course Sem" + sem + ".csv");
		overall_GPA = 0;
		count = 0;
		while (!file.eof())
		{
			getline(file, line, ','); //get courseID
			cout << line << "\t";
			getline(file, line, ','); // skip course name
			getline(file, line, ','); // skip midterm score
			getline(file, line, ','); // get final score
			cout << line << "\t";
			getline(file, line, ','); // skip bonus
			getline(file, line); // get overall
			cout << line << "\n";
			overall_GPA += stof(line);
			count++;
		}
		file.close();
		overall_GPA /= count;
		cout << "Overall GPA: " << overall_GPA << endl;

	}
}

time_t timeToUnixTime(date end)
{
	int hour, min, sec;
	hour = min = sec = 0;
	//Assume session starts from 00:00:00
	time_t a = time(0);
	tm* timeinfo = localtime(&a);

	timeinfo->tm_year = end.year - 1900;
	timeinfo->tm_mon = end.month - 1;		//months since January - [0,11]
	timeinfo->tm_mday = end.day;			//day of the month - [1,31] 
	timeinfo->tm_hour = hour;			//hours since midnight - [0,23]
	timeinfo->tm_min = min;				//minutes after the hour - [0,59]
	timeinfo->tm_sec = sec;				//seconds after the minute - [0,59]

	a = mktime(timeinfo);


	return a;
}

bool isCourseRegistrationSessionActive(date registerStartDay, date registerEndDay)
{
	time_t now = time(0);
	if (timeToUnixTime(registerStartDay) <= now && now <= timeToUnixTime(registerEndDay))
		return true;
	return false;
}
