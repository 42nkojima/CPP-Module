#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include <string>

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
 public:
  PresidentialPardonForm();
  explicit PresidentialPardonForm(const std::string& target);
  PresidentialPardonForm(const PresidentialPardonForm& copy);

  PresidentialPardonForm& operator=(const PresidentialPardonForm& copy);

  ~PresidentialPardonForm();

 private:
  static const int kGardenToSign = 25;
  static const int kGardenToExecute = 5;

  void executeAction() const;

  const std::string target_;
};

#endif
