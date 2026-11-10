#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <ostream>
#include <string>

#include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
 public:
  Form();
  Form(const std::string& name, int gradeToSign, int gradeToExecute);
  Form(const Form& copy);

  ~Form();

  Form& operator=(const Form& copy);

  class GradeTooHighException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  const std::string& getName() const;
  bool getIsSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  void beSigned(const Bureaucrat& bureaucrat);

 private:
  static const int kHighestGrade = 1;
  static const int kLowestGrade = 150;

  static void validateGrade(int grade);

  const std::string name;
  bool isSigned;
  const int gradeToSign;
  const int gradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const Form& right);

#endif
