#pragma once

#include <stdexcept>
#include <string>

class InvalidArgs : public std::logic_error {
 public:
  InvalidArgs(const std::string& msg) : std::logic_error(msg) {}
};

class InvalidIndex : public std::logic_error {
 public:
  InvalidIndex(const std::string& msg) : std::logic_error(msg) {}
};

class InvalidScopeSeq : public std::logic_error {
 public:
  InvalidScopeSeq(const std::string& msg) : std::logic_error(msg) {}
};