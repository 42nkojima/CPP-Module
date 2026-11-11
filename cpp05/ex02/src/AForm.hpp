#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <ostream>
#include <string>

class Bureaucrat;

class AForm {
 public:
  AForm();
  AForm(const std::string& name, int gradeToSign, int gradeToExecute);
  AForm(const AForm& copy);

  virtual ~AForm();

  AForm& operator=(const AForm& copy);

  class GradeTooHighException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  class FormNotSignedException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  const std::string& getName() const;
  bool getIsSigned() const;
  int getGradeToSign() const;
  int getGradeToExecute() const;
  void beSigned(const Bureaucrat& bureaucrat);
  void execute(const Bureaucrat& executor) const;

 private:
  static const int kHighestGrade = 1;
  static const int kLowestGrade = 150;

  static void validateGrade(int grade);

  virtual void executeAction() const = 0;

  const std::string name;
  bool isSigned;
  const int gradeToSign;
  const int gradeToExecute;
};

std::ostream& operator<<(std::ostream& out, const AForm& right);

#endif
