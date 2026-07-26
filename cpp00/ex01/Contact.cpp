#include "Contact.hpp"

#include <iomanip>
#include <ios>
#include <sstream>

void Contact::SetFirstName(const std::string& value) { firstName_ = value; }
void Contact::SetLastName(const std::string& value) { lastName_ = value; }
void Contact::SetNickname(const std::string& value) { nickname_ = value; }
void Contact::SetPhoneNumber(const std::string& value) { phoneNumber_ = value; }
void Contact::SetDarkestSecret(const std::string& value) {
  darkestSecret_ = value;
}

bool Contact::IsValid() const {
  return !firstName_.empty() && !lastName_.empty() && !nickname_.empty() &&
         !phoneNumber_.empty() && !darkestSecret_.empty();
}

std::string Contact::DetailText() const {
  std::ostringstream oss;
  oss << "First name: " << firstName_ << "\n"
      << "Last name: " << lastName_ << "\n"
      << "Nickname: " << nickname_ << "\n"
      << "Phone number: " << phoneNumber_ << "\n"
      << "Darkest secret: " << darkestSecret_ << "\n";
  return oss.str();
}

std::string Contact::FormatColumn(const std::string& value) {
  std::ostringstream oss;
  if (value.length() > 10) {
    oss << value.substr(0, 9) << ".";
  } else {
    oss << std::setw(10) << std::right << value;
  }
  return oss.str();
}

std::string Contact::FirstNameColumn() const {
  return FormatColumn(firstName_);
}
std::string Contact::LastNameColumn() const { return FormatColumn(lastName_); }
std::string Contact::NicknameColumn() const { return FormatColumn(nickname_); }
