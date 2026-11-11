#include <cstdlib>
#include <ctime>
#include <iostream>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

static void testFormInfo() {
  std::cout << std::endl << "--- form info ---" << std::endl;

  const ShrubberyCreationForm shrubbery("home");
  const RobotomyRequestForm robotomy("Bender");
  const PresidentialPardonForm pardon("Arthur");

  std::cout << shrubbery << std::endl;
  std::cout << robotomy << std::endl;
  std::cout << pardon << std::endl;
}

static void testExecuteUnsigned() {
  std::cout << std::endl << "--- execute unsigned ---" << std::endl;

  const Bureaucrat boss("Boss", 1);
  const PresidentialPardonForm pardon("Arthur");

  boss.executeForm(pardon);  // even the highest grade needs a signed form
}

static void testShrubbery() {
  std::cout << std::endl
            << "--- shrubbery (sign 145, exec 137) ---" << std::endl;

  ShrubberyCreationForm form("home");
  const Bureaucrat sign146("Sign146", 146);
  const Bureaucrat sign145("Sign145", 145);
  const Bureaucrat exec138("Exec138", 138);
  const Bureaucrat exec137("Exec137", 137);

  sign146.signForm(form);
  sign145.signForm(form);
  exec138.executeForm(form);
  exec137.executeForm(form);  // writes home_shrubbery
}

static void testRobotomy() {
  std::cout << std::endl << "--- robotomy (sign 72, exec 45) ---" << std::endl;

  RobotomyRequestForm form("Bender");
  const Bureaucrat sign73("Sign73", 73);
  const Bureaucrat sign72("Sign72", 72);
  const Bureaucrat exec46("Exec46", 46);
  const Bureaucrat exec45("Exec45", 45);

  sign73.signForm(form);
  sign72.signForm(form);
  exec46.executeForm(form);
  for (int i = 0; i < 4; ++i) {
    exec45.executeForm(form);  // succeeds about half of the time
  }
}

static void testPresidentialPardon() {
  std::cout << std::endl
            << "--- presidential pardon (sign 25, exec 5) ---" << std::endl;

  PresidentialPardonForm form("Arthur");
  const Bureaucrat sign26("Sign26", 26);
  const Bureaucrat sign25("Sign25", 25);
  const Bureaucrat exec6("Exec6", 6);
  const Bureaucrat exec5("Exec5", 5);

  sign26.signForm(form);
  sign25.signForm(form);
  exec6.executeForm(form);
  exec5.executeForm(form);
}

static void testFileOpenError() {
  std::cout << std::endl << "--- shrubbery file open error ---" << std::endl;

  ShrubberyCreationForm form("no/such/dir/home");
  const Bureaucrat boss("Boss", 1);

  boss.signForm(form);
  boss.executeForm(form);
}

static void testThroughBasePointer() {
  std::cout << std::endl << "--- through AForm* ---" << std::endl;

  const int kNumForms = 3;
  AForm* forms[kNumForms];
  forms[0] = new ShrubberyCreationForm("garden");
  forms[1] = new RobotomyRequestForm("Marvin");
  forms[2] = new PresidentialPardonForm("Ford");

  const Bureaucrat boss("Boss", 1);
  for (int i = 0; i < kNumForms; ++i) {
    boss.signForm(*forms[i]);
    boss.executeForm(*forms[i]);  // each form runs its own action
  }

  for (int i = 0; i < kNumForms; ++i) {
    delete forms[i];  // the virtual destructor frees the derived part
  }
}

static void testCopy() {
  std::cout << std::endl << "--- copy ---" << std::endl;

  const Bureaucrat boss("Boss", 1);
  PresidentialPardonForm original("Arthur");
  boss.signForm(original);

  const PresidentialPardonForm copied(original);
  std::cout << copied << std::endl;
  boss.executeForm(copied);  // the copy is signed and targets Arthur

  PresidentialPardonForm assigned("Trillian");
  assigned = original;  // target is const: only the signed status changes
  std::cout << assigned << std::endl;
  boss.executeForm(assigned);  // still targets Trillian
}

int main() {
  std::srand(static_cast<unsigned int>(std::time(NULL)));

  testFormInfo();
  testExecuteUnsigned();
  testShrubbery();
  testRobotomy();
  testPresidentialPardon();
  testFileOpenError();
  testThroughBasePointer();
  testCopy();
  return 0;
}
