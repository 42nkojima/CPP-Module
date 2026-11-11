#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <string>

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
 public:
  RobotomyRequestForm();
  explicit RobotomyRequestForm(const std::string& target);
  RobotomyRequestForm(const RobotomyRequestForm& copy);

  ~RobotomyRequestForm();

  RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);

 private:
  static const int kGardenToSign = 72;
  static const int kGardenToExecute = 45;

  void executeAction() const;

  const std::string target;
};

#endif
