#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("robotomy request", kGradeToSign, kGradeToExecute),
      target_("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("robotomy request", kGradeToSign, kGradeToExecute),
      target_(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
    : AForm(copy), target_(copy.target_) {}

RobotomyRequestForm& RobotomyRequestForm::operator=(
    const RobotomyRequestForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {}

// The random seed is set once in main, not here: reseeding on every call
// would repeat the same result within the same second.
void RobotomyRequestForm::executeAction() const {
  std::cout << "* drilling noises *\n";
  if (std::rand() % 2 == 0) {
    std::cout << target_ << " has been robotomized successfully.\n";
  } else {
    std::cout << "The robotomy on " << target_ << " failed.\n";
  }
}
