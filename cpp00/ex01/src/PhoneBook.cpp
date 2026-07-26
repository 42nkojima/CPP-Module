#include "PhoneBook.hpp"

#include <sstream>
#include <string>

PhoneBook::PhoneBook() : count_(0) {}

void PhoneBook::AddContact(const Contact& contact) {
  if (!contact.IsValid()) {
    return;
  }

  contacts_[count_ % kMaxContacts] = contact;
  count_++;
}

std::string PhoneBook::SearchListText() const {
  std::ostringstream oss;
  for (int i = 0; i < DisplayCount(); i++) {
    std::ostringstream indexText;
    indexText << i;
    oss << Contact::FormatColumn(indexText.str()) << "|"
        << contacts_[i].FirstNameColumn() << "|"
        << contacts_[i].LastNameColumn() << "|" << contacts_[i].NicknameColumn()
        << "\n";
  }
  return oss.str();
}

bool PhoneBook::HasContact(int index) const {
  return 0 <= index && index < DisplayCount();
}

std::string PhoneBook::ContactDetailText(int index) const {
  return contacts_[index].DetailText();
}

int PhoneBook::DisplayCount() const {
  return count_ < kMaxContacts ? count_ : kMaxContacts;
}
