#include "PhoneBook.hpp"

#include <sstream>
#include <string>

PhoneBook::PhoneBook() : count(0) {}

int PhoneBook::displayCount() const {
  return count < MAX_CONTACTS ? count : MAX_CONTACTS;
}

void PhoneBook::addContact(const Contact &contact) {
  if (!contact.isValid()) {
    return;
  }

  contacts[count % MAX_CONTACTS] = contact;
  count++;
}

std::string PhoneBook::searchListText() const {
  std::ostringstream oss;
  for (int i = 0; i < displayCount(); i++) {
    std::ostringstream indexText;
    indexText << i;
    oss << Contact::formatColumn(indexText.str()) << "|"
        << contacts[i].firstNameColumn() << "|" << contacts[i].lastNameColumn()
        << "|" << contacts[i].nicknameColumn() << "\n";
  }
  return oss.str();
}

bool PhoneBook::hasContact(int index) const {
  return 0 <= index && index < displayCount();
}

std::string PhoneBook::contactDetailText(int index) const {
  return contacts[index].detailText();
}
