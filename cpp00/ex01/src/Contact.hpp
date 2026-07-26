#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
 private:
  std::string firstName_;
  std::string lastName_;
  std::string nickname_;
  std::string phoneNumber_;
  std::string darkestSecret_;

 public:
  void SetFirstName(const std::string& value);
  void SetLastName(const std::string& value);
  void SetNickname(const std::string& value);
  void SetPhoneNumber(const std::string& value);
  void SetDarkestSecret(const std::string& value);

  bool IsValid() const;
  std::string DetailText() const;
  std::string FirstNameColumn() const;
  std::string LastNameColumn() const;
  std::string NicknameColumn() const;

  static std::string FormatColumn(const std::string& value);
};

#endif
