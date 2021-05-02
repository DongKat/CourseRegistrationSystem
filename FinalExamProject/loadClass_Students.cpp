#include "loadClass_Students.h"

float convertToFloat(string score) {
	int j = 0;
	float ans = 0;
	while (j < score.length() && score[j] != '.') {
		ans *= 10;
		ans += float(score[j] - '0');
		++j;
	}
	j++;
	float tmp = 0;
	while (j < score.length()) {
		ans += float(score[j] - '0') * tmp;
		tmp /= 10;
		++j;
	}
	return ans;
}

//CourseScore* loadScore(string path,string StudentID) {
//
//}

BasicCourses* loadCourse(string path, string StudentID) {
	BasicCourses* course = nullptr, * tmp = nullptr;
	ifstream f;
	f.open(path);
	while (f.peek() != EOF)
	{
		string stmp;
		getline(f, stmp, ',');
		if (stmp == "") continue;
		if (course) {
			tmp->next = new BasicCourses;
			tmp = tmp->next;
		}
		else {
			course = new BasicCourses;
			tmp = course;
		}
		tmp->courseID = stmp;
		getline(f, tmp->courseName, ',');
		getline(f, tmp->schedule[0].day, ',');
		getline(f, tmp->schedule[0].time, ',');
		getline(f, tmp->schedule[1].day, ',');
		getline(f, tmp->schedule[1].time);
	}
	f.close();
	return course;
}

Students* loadStudentInfo(string path) //path: schoolyear/classes/classname/id/
{
	Students* stu = new Students;
	stu->courseStudent = nullptr;
	// get student's basic info
	ifstream f;
	f.open(path + "\\Profile.txt");
	f >> stu->no;
	f.ignore(10000, '\n');
	getline(f, stu->ID);
	getline(f, stu->firstName);
	getline(f, stu->lastName);
	getline(f, stu->gender);
	string dateofBirth;
	getline(f, dateofBirth);
	stu->dateOfBirth = convertToDay(dateofBirth);
	getline(f, stu->idSocial);
	getline(f, stu->className);
	f.close();

	//get course
	stu->courseStudent = loadCourse(path + "\\Course " + Sem, stu->ID);

	return stu;
}

Students* loadStudent(string path, string ClassName) // path: schoolyear/Classes/ClassName/
{
	Students* stu = nullptr;
	ifstream f;
	f.open(path + "allStudents.txt");
	if (!f.is_open())
		throw std::runtime_error("Student file not found. Code: 404");
	Students* tmp = nullptr;
	while (!f.eof()) {
		string ID;
		getline(f, ID);
		string StudentPath = path + ID;
		if (stu) {
			tmp->next = loadStudentInfo(StudentPath);
			tmp = tmp->next;
		}
		else {
			stu = loadStudentInfo(StudentPath);
			tmp = stu;
		}
		tmp->className = ClassName;
		tmp->next = nullptr;
	}
	f.close();
	return stu;
}

Classes* loadClassFromFile(Classes*& pClass)
{
	Classes* Class = nullptr;
	string path = Schoolyear + "\\Classes\\";
	string listClass = path + "allClasses.csv";
	ifstream f;
	f.open(listClass);
	if (!f.is_open())
		throw std::runtime_error("Class file not found. Code: 404");
	Classes* tmp = nullptr;
	while (!f.eof()) {
		string ClassName;
		getline(f, ClassName);
		if (ClassName == "") continue;
		if (Class) {
			tmp->next = new Classes;
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		else {
			Class = new Classes;
			tmp = Class;
			tmp->prev = nullptr;
		}
		tmp->className = ClassName;
		tmp->next = nullptr;
		tmp->student = loadStudent(path + ClassName + "\\", ClassName);
	}
	return Class;
}