#include "Bureaucrat.hpp"

#include <iostream>
#include <ostream>

#include "AForm.hpp"

Bureaucrat::Bureaucrat() : name("default"), grade(kLowestGrade) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name(name), grade(grade) {
  validateGrade(grade);
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

const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Bureaucrat: grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Bureaucrat: grade is too low";
}

const std::string& Bureaucrat::getName() const { return name; }

int Bureaucrat::getGrade() const { return grade; }

void Bureaucrat::incrementGrade() {
  validateGrade(grade - 1);
  --grade;
}

void Bureaucrat::decrementGrade() {
  validateGrade(grade + 1);
  ++grade;
}

void Bureaucrat::signForm(AForm& form) const {
  try {
    form.beSigned(*this);
    std::cout << getName() << " signed " << form.getName() << "\n";
  } catch (std::exception& e) {
    std::cout << getName() << " couldn't sign " << form.getName() << " because "
              << e.what() << ".\n";
  }
}

void Bureaucrat::validateGrade(int grade) {
  if (grade < kHighestGrade) {
    throw GradeTooHighException();
  }
  if (grade > kLowestGrade) {
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& right) {
  out << right.getName() << ", bureaucrat grade " << right.getGrade() << ".";
  return out;
}
