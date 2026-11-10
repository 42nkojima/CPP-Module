#include "Form.hpp"

#include <ostream>

#include "Bureaucrat.hpp"

Form::Form()
    : name("default"),
      isSigned(false),
      gradeToSign(kLowestGrade),
      gradeToExecute(kLowestGrade) {}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name),
      isSigned(false),
      gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  validateGrade(gradeToSign);
  validateGrade(gradeToExecute);
}

Form::Form(const Form& copy)
    : name(copy.name),
      isSigned(copy.isSigned),
      gradeToSign(copy.gradeToSign),
      gradeToExecute(copy.gradeToExecute) {}

Form::~Form() {}

Form& Form::operator=(const Form& copy) {
  if (this != &copy) {
    isSigned = copy.isSigned;
  }
  return *this;
}

const char* Form::GradeTooHighException::what() const throw() {
  return "Form: grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
  return "Form: grade is too low";
}

const std::string& Form::getName() const { return name; }

bool Form::getIsSigned() const { return isSigned; }

int Form::getGradeToSign() const { return gradeToSign; }

int Form::getGradeToExecute() const { return gradeToExecute; }

void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > gradeToSign) {
    throw GradeTooLowException();
  }
  isSigned = true;
}

void Form::validateGrade(int grade) {
  if (grade < kHighestGrade) {
    throw GradeTooHighException();
  }
  if (grade > kLowestGrade) {
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& out, const Form& right) {
  out << right.getName() << ", form signed "
      << (right.getIsSigned() ? "yes" : "no") << ", grade to sign "
      << right.getGradeToSign() << ", grade to execute "
      << right.getGradeToExecute() << ".";
  return out;
}
