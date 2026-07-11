#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>

#include "Contact.hpp"

class PhoneBook {
private:
  static const int MAX_CONTACTS = 8;

  Contact contacts[MAX_CONTACTS];
  int count;

  int displayCount() const;

public:
  PhoneBook();
  void addContact(const Contact &contact);
  std::string searchListText() const;
  bool hasContact(int index) const;
  std::string contactDetailText(int index) const;
};

#endif
