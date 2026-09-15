#ifndef HARL_HPP
#define HARL_HPP

#include <string>

class Harl {
 public:
  void complainFilter(const std::string& level);

 private:
  enum Level { DEBUG, INFO, WARNING, ERROR, UNKNOWN };

  static Level getLevel(const std::string& level);

  void debug(void);
  void info(void);
  void warning(void);
  void error(void);
};

#endif
