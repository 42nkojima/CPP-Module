#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
 public:
  void set_first_name(const std::string& value);
  void set_last_name(const std::string& value);
  void set_nickname(const std::string& value);
  void set_phone_number(const std::string& value);
  void set_darkest_secret(const std::string& value);

  bool IsValid() const;
  std::string DetailText() const;
  std::string FirstNameColumn() const;
  std::string LastNameColumn() const;
  std::string NicknameColumn() const;

  static std::string FormatColumn(const std::string& value);

 private:
  std::string firstName_;
  std::string lastName_;
  std::string nickname_;
  std::string phoneNumber_;
  std::string darkestSecret_;
};

#endif
