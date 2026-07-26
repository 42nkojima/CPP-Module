#include "Contact.hpp"

#include <iomanip>
#include <ios>
#include <sstream>

void Contact::setFirstName(const std::string& value) { firstName = value; }
void Contact::setLastName(const std::string& value) { lastName = value; }
void Contact::setNickname(const std::string& value) { nickname = value; }
void Contact::setPhoneNumber(const std::string& value) { phoneNumber = value; }
void Contact::setDarkestSecret(const std::string& value) {
  darkestSecret = value;
}

bool Contact::isValid() const {
  return !firstName.empty() && !lastName.empty() && !nickname.empty() &&
         !phoneNumber.empty() && !darkestSecret.empty();
}

std::string Contact::detailText() const {
  std::ostringstream oss;
  oss << "First name: " << firstName << "\n"
      << "Last name: " << lastName << "\n"
      << "Nickname: " << nickname << "\n"
      << "Phone number: " << phoneNumber << "\n"
      << "Darkest secret: " << darkestSecret << "\n";
  return oss.str();
}

std::string Contact::formatColumn(const std::string& value) {
  std::ostringstream oss;
  if (value.length() > 10) {
    oss << value.substr(0, 9) << ".";
  } else {
    oss << std::setw(10) << std::right << value;
  }
  return oss.str();
}

std::string Contact::firstNameColumn() const { return formatColumn(firstName); }
std::string Contact::lastNameColumn() const { return formatColumn(lastName); }
std::string Contact::nicknameColumn() const { return formatColumn(nickname); }
