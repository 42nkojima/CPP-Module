#include "Bureaucrat.hpp"

#include <iostream>
#include <ostream>

#include "Form.hpp"

Bureaucrat::Bureaucrat() : name_("default"), grade_(kLowestGrade) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
    : name_(name), grade_(grade) {
  validateGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy)
    : name_(copy.name_), grade_(copy.grade_) {}

Bureaucrat::~Bureaucrat() {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& copy) {
  if (this != &copy) {
    grade_ = copy.grade_;
  }
  return *this;
}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Bureaucrat: grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Bureaucrat: grade is too low";
}

const std::string& Bureaucrat::getName() const { return name_; }

int Bureaucrat::getGrade() const { return grade_; }

void Bureaucrat::incrementGrade() {
  validateGrade(grade_ - 1);
  --grade_;
}

void Bureaucrat::decrementGrade() {
  validateGrade(grade_ + 1);
  ++grade_;
}

void Bureaucrat::signForm(Form& form) const {
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
