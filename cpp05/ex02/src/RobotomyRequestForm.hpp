#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <string>

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
 public:
  RobotomyRequestForm();
  explicit RobotomyRequestForm(const std::string& target);
  RobotomyRequestForm(const RobotomyRequestForm& copy);

  RobotomyRequestForm& operator=(const RobotomyRequestForm& copy);

  ~RobotomyRequestForm();

 private:
  static const int kGradeToSign = 72;
  static const int kGradeToExecute = 45;

  void executeAction() const;

  const std::string target_;
};

#endif
