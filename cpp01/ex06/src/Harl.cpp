#include "Harl.hpp"

#include <iostream>

const int kCountOfLevels = 4;

Harl::Level Harl::getLevel(const std::string& level) {
  std::string names[kCountOfLevels] = {"DEBUG", "INFO", "WARNING", "ERROR"};
  for (int i = 0; i < kCountOfLevels; i++) {
    if (names[i] == level) {
      return static_cast<Level>(i);
    }
  }

  return UNKNOWN;
}

void Harl::complainFilter(const std::string& level) {
  switch (getLevel(level)) {
    case DEBUG:
      debug();
      // fall through
    case INFO:
      info();
      // fall through
    case WARNING:
      warning();
      // fall through
    case ERROR:
      error();
      break;
    case UNKNOWN:
      std::cout << "[ Probably complaining about insignificant problems ]\n";
  }
}

void Harl::debug(void) {
  std::cout << "[ DEBUG ]\n"
               "I love having extra bacon for my "
               "7XL-double-cheese-triple-pickle-special-ketchup burger. I "
               "really do!\n\n";
}

void Harl::info(void) {
  std::cout << "[ INFO ]\n"
               "I cannot believe adding extra bacon costs more money. You "
               "didn't put enough bacon in my burger! If you did, I wouldn't "
               "be asking for more!\n\n";
}

void Harl::warning(void) {
  std::cout << "[ WARNING ]\n"
               "I think I deserve to have some extra bacon for free. I've been "
               "coming for years, whereas you started working here just last "
               "month.\n\n";
}

void Harl::error(void) {
  std::cout << "[ ERROR ]\n"
               "This is unacceptable! I want to speak to the manager now.\n\n";
}
