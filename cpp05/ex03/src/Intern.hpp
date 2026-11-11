#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>

class AForm;

class Intern {
 public:
  Intern();
  Intern(const Intern& copy);

  ~Intern();

  Intern& operator=(const Intern& copy);

  class UnknownFormException : public std::exception {
   public:
    virtual const char* what() const throw();
  };

  AForm* makeForm(const std::string& form_name,
                  const std::string& target) const;

 private:
  static AForm* newFormByName(const std::string& form_name,
                              const std::string& target);
  static const int kNumForms = 3;
};

#endif
