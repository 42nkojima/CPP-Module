#include "Contact.hpp"

#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

void Contact::set_first_name(const std::string& value) { first_name_ = value; }
void Contact::set_last_name(const std::string& value) { last_name_ = value; }
void Contact::set_nickname(const std::string& value) { nickname_ = value; }
void Contact::set_phone_number(const std::string& value) {
  phone_number_ = value;
}
void Contact::set_darkest_secret(const std::string& value) {
  darkest_secret_ = value;
}

bool Contact::IsValid() const {
  return !first_name_.empty() && !last_name_.empty() && !nickname_.empty() &&
         !phone_number_.empty() && !darkest_secret_.empty();
}

std::string Contact::DetailText() const {
  std::ostringstream oss;
  oss << "First name: " << first_name_ << "\n"
      << "Last name: " << last_name_ << "\n"
      << "Nickname: " << nickname_ << "\n"
      << "Phone number: " << phone_number_ << "\n"
      << "Darkest secret: " << darkest_secret_ << "\n";
  return oss.str();
}

std::string Contact::FirstNameColumn() const {
  return FormatColumn(first_name_);
}
std::string Contact::LastNameColumn() const { return FormatColumn(last_name_); }
std::string Contact::NicknameColumn() const { return FormatColumn(nickname_); }

std::string Contact::FormatColumn(const std::string& value) {
  std::ostringstream oss;
  if (value.length() > 10) {
    oss << value.substr(0, 9) << ".";
  } else {
    oss << std::setw(10) << std::right << value;
  }
  return oss.str();
}
