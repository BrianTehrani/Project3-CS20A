//============================================================================
// Name        : CS20AProj3.cpp
// Author      : Brian Tehrani
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <time.h> //included for time_t functions to compile
#include "Student.h"
using namespace std;

/*
 * Read in a file containing student records and create an array of Student
 * objects
 *
 * @param file The filename
 * @param num The number of students in the file
 * @return An array of Student objects
 */
Student* readStudentsFromFile(string filename, int num) {
	ifstream studentsStream;
	studentsStream.open(filename.c_str());
	if (!studentsStream.is_open()) {
		cerr << "Couldn't open the file " << filename << endl;
		return NULL;
	}
	Student* students = new Student[num];
	string line, name, school, sid;
	int id;
	for (int i = 0; i < num; i++) {
		getline(studentsStream, line);
		istringstream iss(line);
		getline(iss, name, ',');
		getline(iss, sid, ',');
		getline(iss, school, ',');
		istringstream idConv(sid);
		idConv >> id;
		students[i] = Student(id, name, school);
	}
	studentsStream.close();
	return students;
}

/*
 * Write an array of Student objects to a file
 *
 * @param students The array of Student objects to write out
 * @param num The number of students in the array
 * @param filename The output filename
 */
void writeStudentsToFile(Student students[], int num, string filename) {
	ofstream output(filename.c_str());
	for (int i = 0; i < num; i++) {
		output << students[i].toString();
		if (i < num - 1) {
			output << endl;
		}
	}
	output.close();
}

/***************** Part 1 ***************************/

/*
 * Compare two students by school name
 * Return true if and only if s1 school comes before s2 school
 */
bool compareBySchoolName(Student s1, Student s2) {
	// your code here
	return s1.getSchool() < s2.getSchool();
}

/*
 * Sorts students by school. Uses Standard Template Library's stable sort
 * @param students array already sorted by ID
 * @param Student array length
 */
void sortByGroupById1(Student students[], int len) {
	// your code here
	//sort(students, students + len, compareBySchoolName);
	stable_sort(students, students + len, compareBySchoolName);
}

/***************** Part 2 ***************************/

// you may find this function useful for the counting sort
/*
 * Return the array index for a school (schools in alphabetical order)
 * "UCB", "UCD", "UCI", "UCLA", "UCM", "UCSD", "UCSF"
 *   0		1	   2	   3	  4      5        6
 * @param school
 * @return the index to use as a bucket
 */
int schoolToIndex(string school) {
	if (school == "UCB")  return 0;
	if (school == "UCD")  return 1;
	if (school == "UCI")  return 2;
	if (school == "UCLA") return 3;
	if (school == "UCM")  return 4;
	if (school == "UCSD") return 5;
	if (school == "UCSF") return 6;

	cerr << "Unknown school " << school << endl;
	return -1;
}

/*
 * Sorts students by school. An implementation of counting sort.
 * @param students array already sorted by ID
 * @param len Array length
 */
void sortByGroupById2(Student students[], int len) {
	// your code here
	// ~ 20 - 30 lines
	int* count = new int[7](); //initiallize count w/0
	Student* temp_array = new Student[len];

	for (int i = 0; i < len; i++) //# of students per school
		count[schoolToIndex(students[i].getSchool())]++;

	int students_UCB  = count[0];
	int students_UCD  = count[1] + students_UCB;
	int students_UCI  = count[2] + students_UCD;
	int students_UCLA = count[3] + students_UCI;
	int students_UCM  = count[4] + students_UCLA;
	int students_UCSD = count[5] + students_UCM;
	int students_UCSF = count[6] + students_UCSD;

	for (int i = 0; i < len; i++) {
		if (students[i].getSchool() == "UCB") {
			temp_array[--count[0]] = students[i];
		}
		else if (students[i].getSchool() == "UCD") {
			temp_array[--count[1] + students_UCB] = students[i];
		}
		else if (students[i].getSchool() == "UCI") {
			temp_array[--count[2] + students_UCD] = students[i];
		}
		else if (students[i].getSchool() == "UCLA") {
			temp_array[--count[3] + students_UCI] = students[i];
		}
		else if (students[i].getSchool() == "UCM") {
			temp_array[--count[4] + students_UCLA] = students[i];
		}
		else if (students[i].getSchool() == "UCSD") {
			temp_array[--count[5] + students_UCM] = students[i];
		}
		else if (students[i].getSchool() == "UCSF") {
			temp_array[--count[6] + students_UCSD] = students[i];
		}
	}
	
	int temp_len = len;
	for (int i = 0; i < len; i++) {
		students[i] = temp_array[--temp_len];
	}

	delete[] temp_array;
	delete[] count;
}

/***************** End of Part 2 ***************************/

/*************** DO NOT CHANGE THE CODE BELOW **************/

int main() {
	const int LEN = 350000;

	// Rough timing
	time_t start, end;

	Student* uc1 = readStudentsFromFile("uc_students_sorted_by_id.txt", LEN);
	time(&start);
	sortByGroupById1(uc1, LEN);
	time(&end);
		cout << "Using library sort it took " << difftime(end, start) << " seconds."
				<< endl;
		
	Student* uc2 = readStudentsFromFile("uc_students_sorted_by_id.txt", LEN);
	time(&start);
	sortByGroupById2(uc2, LEN);
	time(&end);
			cout << "Using counting sort it took " << difftime(end, start) << " seconds."
					<< endl;

	writeStudentsToFile(uc1, LEN, "uc_by_school_by_id1.txt");
	writeStudentsToFile(uc2, LEN, "uc_by_school_by_id2.txt");
	return 0;
}
