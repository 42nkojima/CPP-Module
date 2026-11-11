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

  AForm* makeForm(const std::string& form_name,
                  const std::string& target) const;

 private:
};

#endif
