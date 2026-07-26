#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
 private:
  std::string firstName;
  std::string lastName;
  std::string nickname;
  std::string phoneNumber;
  std::string darkestSecret;

 public:
  void setFirstName(const std::string& value);
  void setLastName(const std::string& value);
  void setNickname(const std::string& value);
  void setPhoneNumber(const std::string& value);
  void setDarkestSecret(const std::string& value);

  bool isValid() const;
  std::string detailText() const;
  std::string firstNameColumn() const;
  std::string lastNameColumn() const;
  std::string nicknameColumn() const;

  static std::string formatColumn(const std::string& value);
};

#endif
