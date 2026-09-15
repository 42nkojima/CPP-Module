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
  std::string first_name_;
  std::string last_name_;
  std::string nickname_;
  std::string phone_number_;
  std::string darkest_secret_;
};

#endif
