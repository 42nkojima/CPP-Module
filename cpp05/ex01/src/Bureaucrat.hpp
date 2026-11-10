#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <ostream>
#include <string>

class Form;

class Bureaucrat {
 public:
  Bureaucrat();
  Bureaucrat(const std::string& name, int grade);
  Bureaucrat(const Bureaucrat& copy);

  ~Bureaucrat();

  Bureaucrat& operator=(const Bureaucrat& copy);

  class GradeTooHighException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  class GradeTooLowException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  const std::string& getName() const;
  int getGrade() const;
  void incrementGrade();
  void decrementGrade();
  void signForm(Form& form) const;

 private:
  static const int kHighestGrade = 1;
  static const int kLowestGrade = 150;

  static void validateGrade(int grade);

  const std::string name;
  int grade;
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& right);

#endif
