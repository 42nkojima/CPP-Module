#include "AForm.hpp"

#include <ostream>

#include "Bureaucrat.hpp"

const char* AForm::GradeTooHighException::what() const throw() {
  return "AForm: grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw() {
  return "AForm: grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw() {
  return "AForm: form is not signed";
}

AForm::AForm()
    : name_("default"),
      is_signed_(false),
      grade_to_sign_(kLowestGrade),
      grade_to_execute_(kLowestGrade) {}

AForm::AForm(const std::string& name, int grade_to_sign, int grade_to_execute)
    : name_(name),
      is_signed_(false),
      grade_to_sign_(grade_to_sign),
      grade_to_execute_(grade_to_execute) {
  validateGrade(grade_to_sign);
  validateGrade(grade_to_execute);
}

AForm::AForm(const AForm& copy)
    : name_(copy.name_),
      is_signed_(copy.is_signed_),
      grade_to_sign_(copy.grade_to_sign_),
      grade_to_execute_(copy.grade_to_execute_) {}

AForm::~AForm() {}

AForm& AForm::operator=(const AForm& copy) {
  if (this != &copy) {
    is_signed_ = copy.is_signed_;
  }
  return *this;
}

const std::string& AForm::getName() const { return name_; }

bool AForm::getIsSigned() const { return is_signed_; }

int AForm::getGradeToSign() const { return grade_to_sign_; }

int AForm::getGradeToExecute() const { return grade_to_execute_; }

void AForm::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > grade_to_sign_) {
    throw GradeTooLowException();
  }
  is_signed_ = true;
}

void AForm::execute(const Bureaucrat& executor) const {
  if (!is_signed_) {
    throw FormNotSignedException();
  }
  if (executor.getGrade() > grade_to_execute_) {
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
