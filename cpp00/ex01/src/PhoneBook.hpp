#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include <string>

#include "Contact.hpp"

class PhoneBook {
 private:
  static const int kMaxContacts = 8;

  Contact contacts_[kMaxContacts];
  int count_;

  int DisplayCount() const;

 public:
  PhoneBook();
  void AddContact(const Contact& contact);
  std::string SearchListText() const;
  bool HasContact(int index) const;
  std::string ContactDetailText(int index) const;
};

#endif
