#include "Form.hpp"

#include <ostream>

#include "Bureaucrat.hpp"

Form::Form()
    : name_("default"),
      is_signed_(false),
      grade_to_sign_(kLowestGrade),
      grade_to_execute_(kLowestGrade) {}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
    : name_(name),
      is_signed_(false),
      grade_to_sign_(gradeToSign),
      grade_to_execute_(gradeToExecute) {
  validateGrade(gradeToSign);
  validateGrade(gradeToExecute);
}

Form::Form(const Form& copy)
    : name_(copy.name_),
      is_signed_(copy.is_signed_),
      grade_to_sign_(copy.grade_to_sign_),
      grade_to_execute_(copy.grade_to_execute_) {}

Form::~Form() {}

Form& Form::operator=(const Form& copy) {
  if (this != &copy) {
    is_signed_ = copy.is_signed_;
  }
  return *this;
}

const char* Form::GradeTooHighException::what() const throw() {
  return "Form: grade is too high";
}

const char* Form::GradeTooLowException::what() const throw() {
  return "Form: grade is too low";
}

const std::string& Form::getName() const { return name_; }

bool Form::getIsSigned() const { return is_signed_; }

int Form::getGradeToSign() const { return grade_to_sign_; }

int Form::getGradeToExecute() const { return grade_to_execute_; }

void Form::beSigned(const Bureaucrat& bureaucrat) {
  if (bureaucrat.getGrade() > grade_to_sign_) {
    throw GradeTooLowException();
  }
  is_signed_ = true;
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
