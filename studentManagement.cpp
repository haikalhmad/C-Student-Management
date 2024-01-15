#include <iostream>
#include <fstream>
#include <vector>
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
void viewAllStudents(const vector<Student>& students);
void saveToFileSummary(const vector<Student>& students);
void saveToFileRecord(const vector<Student>& students);
void saveVectorData(const vector<Student>& students);

int main() {
    vector<Student> students; // Vector to store student records

    int choice;
    do {
        cout << "\nStudent Information Management System\n";
        cout << "1. Add a new student record\n";
        cout << "2. Modify a student's record\n";
        cout << "3. View all student records\n";
        cout << "4. Save data to file (Backup your files to avoid overwrite!)\n";
	cout << "5. Retrieve student data\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

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
                retrieveAllStudents(students);
                break;
	    case 6:
		cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }
    } while (choice != 6);

    return 0;
}

// Function to add a new student record
void addStudent(vector<Student>& students) {
    int id;
    string name;
    double t1, t2, final;

    cout << "Enter student ID: ";
    cin >> id;
    for(auto& student : students) {
	while(id == student.studentID) {
	    cout << "ID already exist! Please Re-enter: ";
	    cin >> id;
	}
    }

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter marks for Test 1: ";
    cin >> t1;
    cout << "Enter marks for Test 2: ";
    cin >> t2;
    cout << "Enter marks for Final Assessment: ";
    cin >> final;

    students.push_back(Student(id, name, t1, t2, final));
}

// Function to modify a student's record
void modifyStudent(std::vector<Student>& students) {
    int studentID;
    cout << "Enter student ID to modify: ";
    cin >> studentID;

    for (auto& student : students) {
        if (student.studentID == studentID) {
            cout << "Enter new marks for Test 1: ";
            cin >> student.test1;
            cout << "Enter new marks for Test 2: ";
            cin >> student.test2;
            cout << "Enter new marks for Final Assessment: ";
            cin >> student.finalAssessment;
            cout << "Student record modified successfully." << endl;
            return;
        }
    }

    cout << "Student not found with ID: " << studentID << endl;
}

void viewAllStudents(const vector<Student>& students) {
    cout << "Student Records:" << endl;
    for(const auto& student : students) {
	cout << "ID: " << student.studentID << endl;
        cout << "Name: " << student.studentName<< endl;
        cout << "Test 1: " <<student.test1<< endl;
        cout << "Test 2: " <<student.test2<< endl;
        cout << "Final Assessment: " <<student.finalAssessment<< endl;
        cout << "Total Marks : " <<student.calculateTotalMarks()<< endl;
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
	for(const auto& student : students) {
	    outFile << "ID: " << student.studentID << endl;
	    outFile << "Name: " << student.studentName << endl;
	    outFile << "Test 1: " << student.test1 << endl;
	    outFile << "Test 2: " << student.test2 << endl;
	    outFile << "FInal Assessment: " << student.finalAssessment << endl;
	    outFile << "Total Marks: " << student.calculateTotalMarks() << endl << endl;
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
