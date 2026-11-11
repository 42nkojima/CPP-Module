#include <exception>
#include <iostream>

#include "Bureaucrat.hpp"
#include "Form.hpp"

static void testValidGrades() {
  std::cout << std::endl << "--- valid grades ---" << std::endl;

  try {
    const Bureaucrat highest("Highest", 1);
    const Bureaucrat lowest("Lowest", 150);
    const Bureaucrat by_default;

    std::cout << highest << std::endl;
    std::cout << lowest << std::endl;
    std::cout << by_default << std::endl;
  } catch (std::exception& e) {
    std::cout << "unexpected: " << e.what() << std::endl;
  }
}

static void tryConstruct(int grade) {
  std::cout << "grade " << grade << ": ";
  try {
    const Bureaucrat bureaucrat("Invalid", grade);
    std::cout << "unexpected: " << bureaucrat << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

static void testInvalidGrades() {
  std::cout << std::endl << "--- invalid grades ---" << std::endl;

  tryConstruct(0);
  tryConstruct(-42);
  tryConstruct(151);
}

static void testIncrementDecrement() {
  std::cout << std::endl << "--- increment / decrement ---" << std::endl;

  Bureaucrat bureaucrat("Taro", 42);
  std::cout << bureaucrat << std::endl;
  bureaucrat.incrementGrade();  // 42 -> 41: a higher rank is a smaller number
  std::cout << bureaucrat << std::endl;
  bureaucrat.decrementGrade();  // 41 -> 42
  std::cout << bureaucrat << std::endl;
}

static void testIncrementAtHighest() {
  std::cout << std::endl << "--- increment at grade 1 ---" << std::endl;

  Bureaucrat bureaucrat("Top", 2);
  try {
    bureaucrat.incrementGrade();
    std::cout << bureaucrat << std::endl;
    bureaucrat.incrementGrade();
    std::cout << "unexpected: no exception" << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << bureaucrat << std::endl;  // a failed call keeps the grade
}

static void testDecrementAtLowest() {
  std::cout << std::endl << "--- decrement at grade 150 ---" << std::endl;

  Bureaucrat bureaucrat("Bottom", 149);
  try {
    bureaucrat.decrementGrade();
    std::cout << bureaucrat << std::endl;
    bureaucrat.decrementGrade();
    std::cout << "unexpected: no exception" << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << bureaucrat << std::endl;  // a failed call keeps the grade
}

static void testCatchByExactType() {
  std::cout << std::endl << "--- catch by exact type ---" << std::endl;

  try {
    const Bureaucrat bureaucrat("TooHigh", 0);
    std::cout << "unexpected: " << bureaucrat << std::endl;
  } catch (Bureaucrat::GradeTooHighException& e) {
    std::cout << "GradeTooHighException: " << e.what() << std::endl;
  }

  try {
    const Bureaucrat bureaucrat("TooLow", 151);
    std::cout << "unexpected: " << bureaucrat << std::endl;
  } catch (Bureaucrat::GradeTooLowException& e) {
    std::cout << "GradeTooLowException: " << e.what() << std::endl;
  }
}

static void testCopy() {
  std::cout << std::endl << "--- copy ---" << std::endl;

  const Bureaucrat original("Alice", 42);
  const Bureaucrat copied(original);
  std::cout << copied << std::endl;

  Bureaucrat assigned("Carol", 100);
  assigned = original;  // the name is const: only the grade changes
  std::cout << assigned << std::endl;
}

static void testFormValid() {
  std::cout << std::endl << "--- form: valid grades ---" << std::endl;

  try {
    const Form form("Contract", 50, 25);
    const Form by_default;

    std::cout << form << std::endl;  // a new form is not signed
    std::cout << by_default << std::endl;
  } catch (std::exception& e) {
    std::cout << "unexpected: " << e.what() << std::endl;
  }
}

static void tryConstructForm(int grade_to_sign, int grade_to_execute) {
  std::cout << "sign " << grade_to_sign << ", execute " << grade_to_execute
            << ": ";
  try {
    const Form form("Invalid", grade_to_sign, grade_to_execute);
    std::cout << "unexpected: " << form << std::endl;
  } catch (std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}

static void testFormInvalidGrades() {
  std::cout << std::endl << "--- form: invalid grades ---" << std::endl;

  tryConstructForm(0, 10);
  tryConstructForm(151, 10);
  tryConstructForm(10, 0);
  tryConstructForm(10, 151);
}

static void testSignForm() {
  std::cout << std::endl << "--- sign form ---" << std::endl;

  Form form("Contract", 50, 25);
  const Bureaucrat low("Low", 51);
  const Bureaucrat edge("Edge", 50);

  low.signForm(form);  // 51 is lower than the required 50
  std::cout << form << std::endl;
  edge.signForm(form);  // exactly the required grade is enough
  std::cout << form << std::endl;
}

static void testBeSignedThrows() {
  std::cout << std::endl << "--- beSigned throws ---" << std::endl;

  Form form("Secret", 1, 1);
  const Bureaucrat bureaucrat("Taro", 2);
  try {
    form.beSigned(bureaucrat);
    std::cout << "unexpected: no exception" << std::endl;
  } catch (Form::GradeTooLowException& e) {
    std::cout << "Form::GradeTooLowException: " << e.what() << std::endl;
  }
  std::cout << form << std::endl;  // a failed call keeps the form unsigned
}

static void testFormCopy() {
  std::cout << std::endl << "--- form: copy ---" << std::endl;

  Form original("Contract", 50, 25);
  const Bureaucrat boss("Boss", 1);
  boss.signForm(original);

  const Form copied(original);
  std::cout << copied << std::endl;

  Form assigned("Other", 1, 1);
  assigned = original;  // name and grades are const: only is_signed_ changes
  std::cout << assigned << std::endl;
}

int main() {
  testValidGrades();
  testInvalidGrades();
  testIncrementDecrement();
  testIncrementAtHighest();
  testDecrementAtLowest();
  testCatchByExactType();
  testCopy();
  testFormValid();
  testFormInvalidGrades();
  testSignForm();
  testBeSignedThrows();
  testFormCopy();
  return 0;
}
