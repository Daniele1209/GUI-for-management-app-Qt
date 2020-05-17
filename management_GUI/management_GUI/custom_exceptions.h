#pragma once
#include <exception>
#include <string>
using namespace std;

class service_exception : public exception
{
private:
	string warning;

public:
	service_exception(const string& str) : warning{ str } {}
	const char* what() const throw() override {
		return this->warning.c_str();
	}
};

class repo_exception : public exception
{
private:
	string warning;

public:
	repo_exception(const string& str) : warning{ str } {}
	const char* what() const throw() override {
		return this->warning.c_str();
	}
};