#ifndef LENGTHMISMATCH_H
#define LENGTHMISMATCH_H

#include <stdexcept>
#include <string>

class LengthMismatch : public std::exception 
{
public:
  LengthMismatch(int i,int j);
  
  virtual const char* what() const noexcept;

private:
  std::string msg;
};

#endif