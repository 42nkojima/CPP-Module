#ifndef LITERAL_HPP
#define LITERAL_HPP

class Literal {
 public:
  enum Type { kChar, kInt, kFloat, kDouble, kInvalid };

  Literal();
  Literal(const Literal& copy);
  explicit Literal(char value);
  explicit Literal(int value);
  explicit Literal(float value);
  explicit Literal(double value);

  Literal& operator=(const Literal& copy);

  ~Literal();

  Type getType() const;
  char getChar() const;
  int getInt() const;
  float getFloat() const;
  double getDouble() const;

 private:
  union Value {
    char c;
    int i;
    float f;
    double d;
  };

  Type type_;
  Value value_;
};

#endif
