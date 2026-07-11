#include <iostream>
#include <sstream>
#include <string>

#include "Contact.hpp"
#include "PhoneBook.hpp"

static bool promptNonEmpty(const std::string &label, std::string &out) {
  while (true) {
    std::cout << label << ": ";
    if (!std::getline(std::cin, out)) {
      return false;
    }
    if (!out.empty()) {
      return true;
    }
    std::cout << "This field can't be empty." << std::endl;
  }
}

static bool doAdd(PhoneBook &phoneBook) {
  Contact contact;
  std::string value;

  if (!promptNonEmpty("First name", value))
    return false;
  contact.setFirstName(value);
  if (!promptNonEmpty("Last name", value))
    return false;
  contact.setLastName(value);
  if (!promptNonEmpty("Nickname", value))
    return false;
  contact.setNickname(value);
  if (!promptNonEmpty("Phone number", value))
    return false;
  contact.setPhoneNumber(value);
  if (!promptNonEmpty("Darkest secret", value))
    return false;
  contact.setDarkestSecret(value);

  phoneBook.addContact(contact);
  std::cout << "Contact saved." << std::endl;
  return true;
}

static bool parseIndex(const std::string &input, int &out) {
  std::istringstream iss(input);
  return (iss >> out) && iss.eof();
}

static bool doSearch(const PhoneBook &phoneBook) {
  std::cout << phoneBook.searchListText();
  std::cout << "Index: ";

  std::string input;
  if (!std::getline(std::cin, input)) {
    return false;
  }

  int index;
  if (!parseIndex(input, index) || !phoneBook.hasContact(index)) {
    std::cout << "Invalid index." << std::endl;
    return true;
  }
  std::cout << phoneBook.contactDetailText(index);
  return true;
}

int main() {
  PhoneBook phoneBook;
  std::string command;

  while (true) {
    std::cout << "Enter command (ADD, SEARCH, EXIT): ";
    if (!std::getline(std::cin, command))
      break;

    if (command == "EXIT")
      break;
    if (command == "ADD" && !doAdd(phoneBook))
      break;
    if (command == "SEARCH" && !doSearch(phoneBook))
      break;
  }
  return 0;
}
