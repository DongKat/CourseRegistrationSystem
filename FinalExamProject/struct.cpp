#include <string>
using namespace std;

struct schoolYear{
    int yearStart;
    int yearEnd;
    int semester;
};

struct Course
{  
    schoolYear t;
    string courseName;
    string Id;
    string teacher_name;
    int numCredits;
    int maxStudents;
    string days;
    int *sessions = new int[2]; // remember to delete
};

struct Staff{
    string name;
    string password;
};

struct Student {
    int ID;
    string password;
    int no;
    string name;
    bool gender;
    string dateOfBirth;
    string idSocial;
};

int main()
{
    return 0;
}

