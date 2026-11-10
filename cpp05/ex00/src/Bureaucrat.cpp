#include "Bureaucrat.hpp"

#include <ostream>

const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Bureaucrat: grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Bureaucrat: grade is too low";
}

Bureaucrat::Bureaucrat() : name("default"), grade(kLowestGrade) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name(name), grade(grade) {
  if (grade < kHighestGrade) {
    throw GradeTooHighException();
  }
  if (grade > kLowestGrade) {
    throw GradeTooLowException();
  }
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
    : name(copy.name), grade(copy.grade) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& copy) {
  if (this != &copy) {
    grade = copy.grade;
  }
  return *this;
}

const std::string& Bureaucrat::getName() const { return name; }

int Bureaucrat::getGrade() const { return grade; }

void Bureaucrat::incrementGrade() {
  if (grade <= kHighestGrade) {
    throw GradeTooHighException();
  }
  --grade;
}

void Bureaucrat::decrementGrade() {
  if (grade >= kLowestGrade) {
    throw GradeTooLowException();
  }
  ++grade;
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& right) {
  out << right.getName() << ", bureaucrat grade " << right.getGrade() << ".";
  return out;
}
