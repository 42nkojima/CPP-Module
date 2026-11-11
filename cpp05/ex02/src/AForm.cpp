#include "AForm.hpp"

#include <ostream>

#include "Bureaucrat.hpp"

AForm::AForm()
    : name("default"),
      isSigned(false),
      gradeToSign(kLowestGrade),
      gradeToExecute(kLowestGrade) {}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
    : name(name),
      isSigned(false),
      gradeToSign(gradeToSign),
      gradeToExecute(gradeToExecute) {
  validateGrade(gradeToSign);
  validateGrade(gradeToExecute);
}

AForm::AForm(const AForm& copy)
    : name(copy.name),
      isSigned(copy.isSigned),
      gradeToSign(copy.gradeToSign),
      gradeToExecute(copy.gradeToExecute) {}

AForm::~AForm() {}

AForm& AForm::operator=(const AForm& copy) {
  if (this != &copy) {
    isSigned = copy.isSigned;
  }
  return *this;
}

const char* AForm::GradeTooHighException::what() const throw() {
  return "AForm: grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
  return "AForm: grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw() {
  return "AForm: form is not signed";
}

const std::string& AForm::getName() const { return name; }

bool AForm::getIsSigned() const { return isSigned; }

int AForm::getGradeToSign() const { return gradeToSign; }

int AForm::getGradeToExecute() const { return gradeToExecute; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > gradeToSign) {
    throw GradeTooLowException();
  }
  isSigned = true;
}

void AForm::execute(const Bureaucrat& executor) const {
  if (!isSigned) {
    throw FormNotSignedException();
  }
  if (executor.getGrade() > gradeToExecute) {
    throw GradeTooLowException();
  }
  executeAction();
}

void AForm::validateGrade(int grade) {
  if (grade < kHighestGrade) {
    throw GradeTooHighException();
  }
  if (grade > kLowestGrade) {
    throw GradeTooLowException();
  }
}

std::ostream& operator<<(std::ostream& out, const AForm& right) {
  out << right.getName() << ", form signed "
      << (right.getIsSigned() ? "yes" : "no") << ", grade to sign "
      << right.getGradeToSign() << ", grade to execute "
      << right.getGradeToExecute() << ".";
  return out;
}
