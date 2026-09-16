#ifndef FIXED_HPP
#define FIXED_HPP

class Fixed {
 public:
  Fixed();                              // default constructor
  Fixed(const Fixed& copy);             // copy constructor
  Fixed& operator=(const Fixed& copy);  // copy assignment operator
  ~Fixed();                             // destructor

  int getRawBits() const;
  void setRawBits(const int raw);

 private:
  int value_;
  static const int kFractionalBits = 8;
};

#endif
