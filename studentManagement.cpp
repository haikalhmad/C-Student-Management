#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <iomanip>
#include <algorithm>

using namespace std;
// Define a class to represent a student
class Student {
public:
    int studentID;
    string studentName;
    double test1;
    double test2;
    double finalAssessment;

    // Constructor to initialize student object
    Student(int id, const string& name, double t1, double t2, double final)
        : studentID(id), studentName(name), test1(t1), test2(t2), finalAssessment(final) {}

    // Function to calculate total marks
    double calculateTotalMarks() const {
        return test1 + test2 + finalAssessment;
    }
};

// Function prototypes
void addStudent(vector<Student>& students);
void modifyStudent(vector<Student>& students);
void retrieveAllStudents(vector<Student>& students);
void viewAllStudents(vector<Student>& students);
void saveToFileSummary(const vector<Student>& students);
void saveToFileRecord(const vector<Student>& students);
void saveVectorData(const vector<Student>& students);

int main() {
    vector<Student> students; // Vector to store student records
    retrieveAllStudents(students); // Automatically get the vector data
    int choice;

    do {
        cout << "\nStudent Information Management System\n";
        cout << "1. Add a new student record\n";
        cout << "2. Modify a student's record\n";
        cout << "3. View all student records\n";
        cout << "4. Save data to file (Backup your files to avoid overwrite!)\n";
	cout << "5. Exit\n";
        cout << "Enter your choice: ";
        while(true) {
	    cin >> choice;
	    if(cin.fail()) {
		cout << "Invalid input! Please Re-enter: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	    } else
		break;
	}

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                modifyStudent(students);
                break;
            case 3:
                viewAllStudents(students);
                break;
            case 4:
                saveToFileSummary(students);
		saveToFileRecord(students);
		saveVectorData(students);
                break;
	    case 5:
		cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice! Please enter a valid option." << endl;
        }
    } while (choice != 5);

    return 0;
}

// Function to add a new student record
void addStudent(vector<Student>& students) {
    int id;
    string name;
    double t1, t2, final;
    cout << endl << "Add New Student Record" << endl;

    // Enter student ID
    cout << "Enter Student ID: ";
    while(true) {
	cin >> id;
	if(cin.fail()) {
	    //Check to see if input is an integer
	    cout << "Invalid input! Please enter a valid input: ";
	    cin.clear(); //clear error state
	    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
	} else {
	    bool idExist = false;
	    //If the input is an integer, check if the ID already exist
	    for(auto& student : students) {
		if(id == student.studentID) {
		    idExist = true;
		    cout << "Student ID already exist! Please Re-enter: ";
		    break; //Break out of for loop
		}
	    }
	    //If ID does not exist, break out of while loop
	    if(!idExist)
		break;
	}
    }

    //Enter student name
    cout << "Enter Student Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //to avoid getline() from reading '\n' as input
    getline(cin, name);
    
    //Enter Test 1 Marks
    cout << "Enter Marks for Test 1: ";
    while(true) {
	cin >> t1;
	if(cin.fail()) {
	    //Check to see if input is a double
	    cout << "Invalid input! Please enter a valid input: ";
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //clear input buffer
	} else
	    break; //break out of while loop
    }

    //Enter Test 2 Marks
    cout << "Enter Marks for Test 2: ";
    while(true) {
	cin >> t2;
	if(cin.fail()) {
	    cout << "Invalid input! Please enter a valid input: ";
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} else
	    break; //break out of while loop
    }
    
    //Enter Final Assessment Marks
    cout << "Enter Marks for Final Assessment: ";
    while(true) {
	cin >> final;
	if(cin.fail()) {
	    cout << "Invalid input! Please enter a valid input: ";
	    cin.clear(); //clear error state
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} else
	    break; //break out of while loop
    }
    cout << "Student has been added to Record successfully." << endl;
    students.push_back(Student(id, name, t1, t2, final));
}

// Function to modify a student's record
void modifyStudent(vector<Student>& students) {
    int id;
    cout << endl << "Modify Student Record" << endl;

    //Enter student id
    cout << "Enter Student ID: ";
    while(true) {
	cin >> id;
	if(cin.fail()) {
	    cout << "Invalid input! Please Re-enter: ";
	    cin.clear();
	    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} else {
	    for(auto& student : students) {
		if(id == student.studentID) {
		    //Enter Test 1 Marks
		    cout << "Enter Marks for Test 1: ";
		    while(true) {
			cin >> student.test1;
			if(cin.fail()) {
			    cout << "Invalid input! Please Re-enter: ";
			    cin.clear();
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else
			    break; //Break inner while loop
		    }
		    //Enter Test 2 Marks
		    cout << "Enter Marks for Test 2: ";
		    while(true) {
			cin >> student.test2;
			if(cin.fail()) {
			    cout << "Invalid input! Please Re-enter: ";
			    cin.clear();
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else
			    break; //Break inner while loop
		    }
		    //Enter Final Assessment Marks
		    cout << "Enter Marks for Final Assessment: ";
		    while(true) {
			cin >> student.finalAssessment;
			if(cin.fail()) {
			    cout << "Invalid input! Please Re-enter: ";
			    cin.clear();
			    cin.ignore(numeric_limits<streamsize>::max(), '\n');
			} else
			    break; //Break inner while loop
		    }
		    cout << "Student Record has been modified successsfully." << endl;
		    return;
		}
	    }
	    break; //break out of while loop
	}
    }
    cout << "Student ID does not exist." << endl;
}

void viewAllStudents(vector<Student>& students) {
    // Sort students based on student IDs
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.studentID < b.studentID;
    });

    cout << endl;
    cout << setw(4) << "|| Number ||" << setw(14) << "Student ID ||" << setw(16) << "Student Name ||" << setw(10) << "Test 1 ||" << setw(10) << "Test 2 ||" << setw(20) << "Final Assessment ||" << setw(15) << "Total Marks ||" << endl;
    cout << setw(10) << "--------" << setw(14) << "------------" << setw(16) << "--------------" << setw(10) << "--------" << setw(10) << "--------" << setw(20) << "------------------" << setw(15) << "-------------" << endl;

    for(size_t i = 0; i < students.size(); ++i) {
        auto& student = students[i];
        cout << setw(7) << i + 1 << "\t";
        cout << setw(12) << student.studentID << "\t";
        cout << setw(11) << student.studentName << "\t";
        cout << setw(7) << student.test1 << "\t";
        cout << setw(9) << student.test2 << "\t";
        cout << setw(8) << student.finalAssessment << "\t";
        cout << setw(10) << student.calculateTotalMarks() << "\n";
    }
}

// Function to retrieve all student records
void retrieveAllStudents(vector<Student>& students) {
    ifstream inFile("vector_data.txt");
    if(inFile.is_open()) {
	int id;
	string name;
	double t1, t2, final;

	while(inFile >> id >> name >> t1 >> t2 >> final) {
	    students.push_back(Student(id, name, t1, t2, final));
	}
	inFile.close();
	cout << "Vector data retrieved successfully." << endl;
    } else {
	cout << "Error retrieving vector data." << endl;
    }
}

// Function to save data into a file
void saveToFileSummary(const vector<Student>& students) {
    ofstream outFile("summary_student_data.txt");
    if (outFile.is_open()) {
        outFile << "Total number of students: " << students.size() << endl;

        // Calculate highest, lowest, and average marks for Test 1 and Test 2
        double highestTest1 = -1, lowestTest1 = 101, totalTest1 = 0;
        double highestTest2 = -1, lowestTest2 = 101, totalTest2 = 0;
        double totalMarks = 0;

        for (const auto& student : students) {
            totalTest1 += student.test1;
            totalTest2 += student.test2;

            if (student.test1 > highestTest1) highestTest1 = student.test1;
            if (student.test1 < lowestTest1) lowestTest1 = student.test1;

            if (student.test2 > highestTest2) highestTest2 = student.test2;
            if (student.test2 < lowestTest2) lowestTest2 = student.test2;

            totalMarks += student.calculateTotalMarks();
        }

        outFile << "Highest Test 1: " << highestTest1 << endl;
        outFile << "Lowest Test 1: " << lowestTest1 << endl;
        outFile << "Average Test 1: " << totalTest1 / students.size() << endl;

        outFile << "Highest Test 2: " << highestTest2 << endl;
        outFile << "Lowest Test 2: " << lowestTest2 << endl;
        outFile << "Average Test 2: " << totalTest2 / students.size() << endl;

        outFile << "Total Marks for all students: " << totalMarks << endl;

        cout << "Summary data saved to file successfully." << endl;
        outFile.close();
    } else {
        cout << "Error saving summary data." << endl;
    }
}

void saveToFileRecord(const vector<Student>& students) {
    ofstream outFile("student_record_data.txt");
    if(outFile.is_open()) {
	outFile << setw(4) << "|| Number ||" << setw(14) << "Student ID ||" << setw(16) << "Student Name ||" << setw(10) << "Test 1 ||" << setw(10) << "Test 2 ||" << setw(20) << "Final Assessment ||" << setw(15) << "Total Marks ||" << endl;
    outFile << setw(10) << "--------" << setw(14) << "------------" << setw(16) << "--------------" << setw(10) << "--------" << setw(10) << "--------" << setw(20) << "------------------" << setw(15) << "-------------" << endl;
        // Append new student data
        for (size_t i = 0; i < students.size(); ++i) {
            const Student& student = students[i];
            outFile << setw(6) << i + 1 << "\t";
            outFile << setw(12) << student.studentID << "\t";
            outFile << setw(11) << student.studentName << "\t";
            outFile << setw(7) << student.test1 << "\t";
            outFile << setw(9) << student.test2 << "\t";
            outFile << setw(9) << student.finalAssessment << "\t";
            outFile << setw(10) << student.calculateTotalMarks() << "\n";
        }
	cout << "Student record saved to file successfully." << endl;
	outFile.close();
    } else {
	cout << "Error saving student record." << endl;
    }
}

void saveVectorData(const vector<Student>& students) {
    ofstream outFile("vector_data.txt");
    if(outFile.is_open()) {
	for(const auto& student : students) {
	    outFile << student.studentID << " " << student.studentName << " " << student.test1 << " " << student.test2 << " " << student.finalAssessment << " ";
	}
	cout << "Vector data saved to file successfully." << endl;
	outFile.close();
    } else {
	cout << "Error saving vector data.";
    }
}
