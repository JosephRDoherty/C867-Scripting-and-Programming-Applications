
#include <iostream>
#include <string>
#include <map>
#include "student.h"
#include "degree.h"
#include "roster.h"


// Constructor
Roster::Roster(int rosterSize) {
	Roster::rosterSize = rosterSize;

	for (int i = 0; i < rosterSize; i++) {
		classRosterArray[i] = nullptr;
	}
};


Roster::~Roster() {
	for (int i = 0; i < rosterSize; i++) {
		delete classRosterArray[i];
		classRosterArray[i] = nullptr;
	}
};


void Roster::parse() {

	// Parse each student, create Student objects and place them into classRosterArray
	for (int student = 0; student < rosterSize; student++) {

		// Parse the data of an individual student
		classRosterArray[student] = Roster::parseLine(studentData[student]);

	};
};


Student* Roster::parseLine(std::string dataLine) {

	std::string delimiter = ","; // Set the delimiter you'd like to use to parse the data
	std::string studentArray[9];
	std::size_t lastDelimiter = 0; // Track the previous delimiter end point so we don't have to destroy the string
	int counter = 0;

	// Parse student info string
	while ((dataLine.find(delimiter, lastDelimiter + delimiter.length())) != std::string::npos) {

		// Add the student's data to the array
		studentArray[counter] = dataLine.substr(lastDelimiter, dataLine.find(delimiter, lastDelimiter) - lastDelimiter);

		// Locate and save the delimiter for next loop
		lastDelimiter = dataLine.find(delimiter, lastDelimiter) + delimiter.length();

		counter++;
	};
	// Catch the final line of information
	studentArray[8] = dataLine.substr(lastDelimiter);

	return new Student(
		studentArray[0], // studentID
		studentArray[1], // firstName
		studentArray[2], // lastName
		studentArray[3], // email
		std::stoi(studentArray[4]), // age, cast to int
		std::stoi(studentArray[5]), // courseTime1, cast to int
		std::stoi(studentArray[6]), // courseTime2, cast to int
		std::stoi(studentArray[7]), // courseTime3, cast to int
		castToDegreeProgram(studentArray[8]) // degreeProgram, cast to enum DegreeProgram
	);
};


void Roster::add(
	std::string studentID,
	std::string firstName,
	std::string lastName,
	std::string emailAddress,
	int age,
	int daysInCourse1,
	int daysInCourse2,
	int daysInCourse3,
	DegreeProgram degreeProgram) {

	classRosterArray[rosterSize] = new Student(studentID, firstName, lastName, emailAddress, age, daysInCourse1, daysInCourse2, daysInCourse3, degreeProgram);

	std::cout << "Student ID #" << studentID << " successfully added to roster" << std::endl;
	std::cout << std::endl;
};


void Roster::remove(std::string studentID) {

	std::cout << "Attempting to remove Student ID:  " << studentID << std::endl;

	bool studentRemoved = false;
		
	for (int i = 0; i < rosterSize; i++) {

		if (classRosterArray[i] == nullptr) {
			continue;
		}
		else if (classRosterArray[i]->getStudentID() == studentID) {

			classRosterArray[i] = nullptr;
			studentRemoved = true;
		}
	};

	if (studentRemoved) {

		std::cout << "Success: Student ID " << studentID << " was removed." << std::endl;
		std::cout << std::endl;
	}
	else {

		std::cout << "Error: Student ID " << studentID << " was not found." << std::endl;
		std::cout << std::endl;
	};
};


void Roster::printAll() {

	std::cout << "All students in roster: " << std::endl;

	for (int student = 0; student < rosterSize; student++) {

		if (classRosterArray[student] != nullptr) {
			classRosterArray[student]->print();
		}
	};

	std::cout << std::endl;
};


void Roster::printAverageDaysInCourse(std::string studentID) {
	
	for (int i = 0; i < rosterSize; i++) {

		if (classRosterArray[i] == nullptr) {
			continue;
		}
		else if(classRosterArray[i]->getStudentID() == studentID) {

			int* courseArray = classRosterArray[i]->getDaysPerCourseArray();

			int totalDays = 0;
			int arrayLength = 3;

			for (int i = 0; i < arrayLength; i++) {
				totalDays = totalDays + courseArray[i];
			}
			
			std::cout << "Average days per course: Student #" << studentID << ": " << totalDays / arrayLength << std::endl;
		}
	}
};


void Roster::printInvalidEmails() {

	for (int i = 0; i < rosterSize; i++) {

		if (classRosterArray[i] != nullptr) {

			std::string email = classRosterArray[i]->getEmailAddress();

			if ((email.find(" ") != std::string::npos) || 
				(email.find(".") == std::string::npos) || 
				(email.find("@") == std::string::npos)) {

				std::cout << "INVALID EMAIL: " << email << std::endl;
			}

		}
	}

	std::cout << std::endl;
};


void Roster::printByDegreeProgram(DegreeProgram degreeProgram) {
	
	std::cout << "Students enrolled in " << castDegreeProgramToString(degreeProgram) << ": " << std::endl;

	for (int i = 0; i < rosterSize; i++) {

		if (classRosterArray[i] != nullptr) {

			if (classRosterArray[i]->getDegreeProgram() == degreeProgram) {

				classRosterArray[i]->print();
			}
		}
	}

	std::cout << std::endl;

};



// Cast string into degreeProgram
DegreeProgram Roster::castToDegreeProgram(std::string degreeString) {

	if (degreeString == "SECURITY") {
		return SECURITY;
	}
	else if (degreeString == "NETWORK") {
		return NETWORK;
	}
	else if (degreeString == "SOFTWARE") {
		return SOFTWARE;
	}
	else {
		return UNDECLARED;
	}

};


// Cast Degree Program to a string
std::string Roster::castDegreeProgramToString(DegreeProgram degreeEnum) {
	if (degreeEnum == SECURITY) {
		return "SECURITY";
	}
	else if (degreeEnum == NETWORK) {
		return "NETWORK";
	}
	else if (degreeEnum == SOFTWARE) {
		return "SOFTWARE";
	}
	else {
		return "UNDECLARED";
	};
};