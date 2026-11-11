#ifndef INTERN_HPP
#define INTERN_HPP

#include <exception>
#include <string>

class AForm;

class Intern {
 public:
  class UnknownFormException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  Intern();
  Intern(const Intern& copy);

  Intern& operator=(const Intern& copy);

  ~Intern();

  AForm* makeForm(const std::string& form_name,
                  const std::string& target) const;

 private:
  static const int kNumForms = 3;

  static AForm* newFormByName(const std::string& form_name,
                              const std::string& target);
};

#endif
