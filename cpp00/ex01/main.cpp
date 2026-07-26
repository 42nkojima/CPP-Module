#include <iostream>
#include <sstream>
#include <string>

#include "Contact.hpp"
#include "PhoneBook.hpp"

static bool PromptNonEmpty(const std::string& label, std::string& out) {
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

static bool DoAdd(PhoneBook& phoneBook) {
  Contact contact;
  std::string value;

  if (!PromptNonEmpty("First name", value)) return false;
  contact.SetFirstName(value);
  if (!PromptNonEmpty("Last name", value)) return false;
  contact.SetLastName(value);
  if (!PromptNonEmpty("Nickname", value)) return false;
  contact.SetNickname(value);
  if (!PromptNonEmpty("Phone number", value)) return false;
  contact.SetPhoneNumber(value);
  if (!PromptNonEmpty("Darkest secret", value)) return false;
  contact.SetDarkestSecret(value);

  phoneBook.AddContact(contact);
  std::cout << "Contact saved." << std::endl;
  return true;
}

static bool ParseIndex(const std::string& input, int& out) {
  std::istringstream iss(input);
  return (iss >> out) && iss.eof();
}

static bool DoSearch(const PhoneBook& phoneBook) {
  std::cout << phoneBook.SearchListText();
  std::cout << "Index: ";

  std::string input;
  if (!std::getline(std::cin, input)) {
    return false;
  }

  int index;
  if (!ParseIndex(input, index) || !phoneBook.HasContact(index)) {
    std::cout << "Invalid index." << std::endl;
    return true;
  }
  std::cout << phoneBook.ContactDetailText(index);
  return true;
}

int main() {
  PhoneBook phoneBook;
  std::string command;

  while (true) {
    std::cout << "Enter command (ADD, SEARCH, EXIT): ";
    if (!std::getline(std::cin, command)) break;

    if (command == "EXIT") break;
    if (command == "ADD" && !DoAdd(phoneBook)) break;
    if (command == "SEARCH" && !DoSearch(phoneBook)) break;
  }
  return 0;
}
