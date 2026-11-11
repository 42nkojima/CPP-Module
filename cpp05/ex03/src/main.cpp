#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

static void testSubjectExample() {
  std::cout << std::endl << "--- subject example ---" << std::endl;

  Intern someRandomIntern;
  AForm* rrf;

  rrf = someRandomIntern.makeForm("robotomy request", "Bender");
  if (rrf != NULL) {
    std::cout << *rrf << std::endl;
    delete rrf;
  }
}

static void signAndExecute(const Intern& intern, const Bureaucrat& boss,
                           const std::string& name, const std::string& target) {
  AForm* form = intern.makeForm(name, target);
  if (form == NULL) {
    return;
  }

  boss.signForm(*form);
  boss.executeForm(*form);
  delete form;
}

static void testAllForms() {
  std::cout << std::endl << "--- all forms ---" << std::endl;

  const Intern intern;
  const Bureaucrat boss("Boss", 1);

  signAndExecute(intern, boss, "shrubbery creation", "home");
  signAndExecute(intern, boss, "robotomy request", "Bender");
  signAndExecute(intern, boss, "presidential pardon", "Arthur");
}

static void testUnknownForm() {
  std::cout << std::endl << "--- unknown form ---" << std::endl;

  const Intern intern;
  AForm* form = intern.makeForm("coffee request", "Boss");

  if (form == NULL) {
    std::cout << "makeForm returned NULL" << std::endl;
  }
  delete form;
}

static void testCopy() {
  const Intern original;
  const Intern copied(original);
  Intern assigned;
  assigned = original;

  AForm* form = copied.makeForm("presidential pardon", "Ford");
  delete form;
  form = assigned.makeForm("shrubbery creation", "garden");
  delete form;
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  testSubjectExample();
  testAllForms();
  testUnknownForm();
  testCopy();
  return 0;
}
