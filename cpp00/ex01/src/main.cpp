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
    std::cout << "This field can't be empty.\n";
  }
}

static bool DoAdd(PhoneBook& phone_book) {
  Contact contact;
  std::string value;

  if (!PromptNonEmpty("First name", value)) {
    return false;
  }
  contact.set_first_name(value);
  if (!PromptNonEmpty("Last name", value)) {
    return false;
  }
  contact.set_last_name(value);
  if (!PromptNonEmpty("Nickname", value)) {
    return false;
  }
  contact.set_nickname(value);
  if (!PromptNonEmpty("Phone number", value)) {
    return false;
  }
  contact.set_phone_number(value);
  if (!PromptNonEmpty("Darkest secret", value)) {
    return false;
  }
  contact.set_darkest_secret(value);

  phone_book.AddContact(contact);
  std::cout << "Contact saved.\n";
  return true;
}

static bool ParseIndex(const std::string& input, int& out) {
  std::istringstream iss(input);
  return (iss >> out) && iss.eof();
}

static bool DoSearch(const PhoneBook& phone_book) {
  std::cout << phone_book.SearchListText();
  std::cout << "Index: ";

  std::string input;
  if (!std::getline(std::cin, input)) {
    return false;
  }

  int index;
  if (!ParseIndex(input, index) || !phone_book.HasContact(index)) {
    std::cout << "Invalid index.\n";
    return true;
  }
  std::cout << phone_book.ContactDetailText(index);
  return true;
}

int main() {
  PhoneBook phone_book;
  std::string command;

  while (true) {
    std::cout << "Enter command (ADD, SEARCH, EXIT): ";
    if (!std::getline(std::cin, command)) {
      break;
    }

    if (command == "EXIT") {
      break;
    }
    if (command == "ADD" && !DoAdd(phone_book)) {
      break;
    }
    if (command == "SEARCH" && !DoSearch(phone_book)) {
      break;
    }
  }
  return 0;
}
