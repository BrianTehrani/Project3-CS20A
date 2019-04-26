/*
 * Student.h
 *
 */

#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
using namespace std;

class Student {
	int id;
	string name;
	string school;

public:
	/*
	 * Default ctor
	 */
	Student();

	/*
	 * Overloaded ctor
	 */
	Student(int id, string name, string school);

	/*
	 * Returns a string representation of a student object
	 * like "Caroline Greene,10537229,SMC"
	 */
	string toString() const;

	/*
	 * Get the school name
	 */
	string getSchool() const;

	/*
	 * Compares two students by ID for equality
	 */
	bool operator == (const Student& other) const;

	/*
	 * Compares two students by ID for ordering
	 */
	bool operator < (const Student& other) const;

	virtual ~Student();
};

#endif /* STUDENT_H_ */
