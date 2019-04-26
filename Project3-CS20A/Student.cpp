/*
 * Student.cpp
 *
 */

#include "Student.h"
#include <sstream>
#include <iostream>


Student::Student() {
	id = 0;
	name = "";
	school = "";
}

Student::Student(int id, string name, string school) {
	this->id = id;
	this->name = name;
	this->school = school;
}

string Student::toString() const {
	stringstream ss;
	ss << name << "," << id << "," << school;
	return ss.str();
}

string Student::getSchool() const {
	return school;
}

bool Student::operator ==(const Student& other) const {
	return this->id == other.id;
}

bool Student::operator < (const Student& other) const {
	return this->id < other.id;
}

Student::~Student() {
	// do nothing
}
