#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("robotomy request", kGardenToSign, kGardenToExecute),
      target("default") {}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
    : AForm("robotomy request", kGardenToSign, kGardenToExecute),
      target(target) {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& copy)
    : AForm(copy), target(copy.target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm& RobotomyRequestForm::operator=(
    const RobotomyRequestForm& copy) {
  if (this != &copy) {
    AForm::operator=(copy);
  }
  return *this;
}

// The random seed is set once in main, not here: reseeding on every call
// would repeat the same result within the same second.
void RobotomyRequestForm::executeAction() const {
  std::cout << "* drilling noises *\n";
  if (std::rand() % 2 == 0) {
    std::cout << target << " has been robotomized successfully.\n";
  } else {
    std::cout << "The robotomy on " << target << " failed.\n";
  }
}
