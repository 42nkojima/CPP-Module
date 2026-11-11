#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <exception>
#include <string>

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
 public:
  class FileOpenException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  ShrubberyCreationForm();
  explicit ShrubberyCreationForm(const std::string& target);
  ShrubberyCreationForm(const ShrubberyCreationForm& copy);

  ShrubberyCreationForm& operator=(const ShrubberyCreationForm& copy);

  ~ShrubberyCreationForm();

 private:
  static const int kGardenToSign = 145;
  static const int kGardenToExecute = 137;

  void executeAction() const;

  const std::string target_;
};

#endif
