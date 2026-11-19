#ifndef SCALARVALUES_HPP
#define SCALARVALUES_HPP

class ScalarValues {
 public:
  ScalarValues();
  ScalarValues(const ScalarValues& copy);

  ScalarValues& operator=(const ScalarValues& copy);

  ~ScalarValues();

  bool hasChar() const;
  char getChar() const;
  void setChar(char value);

  bool hasInt() const;
  int getInt() const;
  void setInt(int value);

  bool hasFloat() const;
  float getFloat() const;
  void setFloat(float value);

  bool hasDouble() const;
  double getDouble() const;
  void setDouble(double value);

 private:
  bool has_char_;
  char char_value_;

  bool has_int_;
  int int_value_;

  bool has_float_;
  float float_value_;

  bool has_double_;
  double double_value_;
};

#endif
