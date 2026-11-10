#include <exception>
#include <iostream>

#include "Bureaucrat.hpp"

static void testValidGrades() {
  std::cout << std::endl << "--- valid grades ---" << std::endl;

  try {
    const Bureaucrat highest("Highest", 1);
    const Bureaucrat lowest("Lowest", 150);
    const Bureaucrat byDefault;

    std::cout << highest << std::endl;
    std::cout << lowest << std::endl;
    std::cout << byDefault << std::endl;
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

int main() {
  testValidGrades();
  testInvalidGrades();
  testIncrementDecrement();
  testIncrementAtHighest();
  testDecrementAtLowest();
  testCatchByExactType();
  testCopy();
  return 0;
}
