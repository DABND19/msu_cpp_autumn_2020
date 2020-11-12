#pragma once

#include <iostream>
#include <string>

static const std::string TRUE = "true";
static const std::string FALSE = "false";

enum class Error { NoError, CorruptedArchive };

std::ostream& operator<<(std::ostream& os, Error error);

class Serializer {
  std::ostream& os;
  static constexpr char Separator = ' ';

 public:
  Serializer(std::ostream& os) : os(os) {}

  template <typename T>
  Error save(const T& object);

  template <typename... ArgsT>
  Error operator()(const ArgsT&... args);

 private:
  template <typename T, typename... ArgsT>
  Error process(const T& object, const ArgsT&... args);

  Error process() { return Error::NoError; }
};

#include "Serializer.ipp"

class Deserializer {
  std::istream& is;

 public:
  Deserializer(std::istream& is) : is(is) {}

  template <typename T>
  Error load(T& object);

  template <typename... ArgsT>
  Error operator()(ArgsT&... args);

 private:
  template <typename T, typename... ArgsT>
  Error process(T& object, ArgsT&... args);

  Error process() { return Error::NoError; }
};

#include "Deserializer.ipp"

std::ostream& operator<<(std::ostream& os, Error error) {
  return os << (error == Error::NoError ? "NoError" : "CorruptedArchive");
}
