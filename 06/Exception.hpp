#pragma once

#include <iostream>
#include <string>

class Exception {
 public:
  Exception(const std::string& msg) : message(msg) {}
  const std::string& what() const { return message; }

 private:
  const std::string message;
};

class InvalidArgs : public Exception {
 public:
  InvalidArgs(const std::string& msg) : Exception(msg) {}
};

class InvalidIndex : public Exception {
 public:
  InvalidIndex(const std::string& msg) : Exception(msg) {}
};

class InvalidScopeSeq : public Exception {
 public:
  InvalidScopeSeq(const std::string& msg) : Exception(msg) {}
};