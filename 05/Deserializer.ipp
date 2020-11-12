#pragma once

#include <stdexcept>
#include <string>

#include "Serializers.hpp"

template <typename T>
Error Deserializer::load(T& object) {
  return object.deserialize(*this);
}

template <typename... ArgsT>
Error Deserializer::operator()(ArgsT&... args) {
  return process(args...);
}

template <typename T, typename... ArgsT>
Error Deserializer::process(T& object, ArgsT&... args) {
  if (load(object) == Error::CorruptedArchive) {
    return Error::CorruptedArchive;
  }

  return process(args...);
}

Error Deserializer::process() {
  return is.fail() ? Error::CorruptedArchive : Error::NoError;
}

template <>
Error Deserializer::load<bool>(bool& object) {
  std::string value;
  is >> value;

  if (value == TRUE) {
    object = true;
  } else if (value == FALSE) {
    object = false;
  } else {
    return Error::CorruptedArchive;
  }

  return is.fail() ? Error::CorruptedArchive : Error::NoError;
}

template <>
Error Deserializer::load<uint64_t>(uint64_t& object) {
  if (is.peek() == '-') {
    return Error::CorruptedArchive;
  }

  std::string value;
  is >> value;
  size_t pos;

  try {
    object = stoull(value, &pos);
  } catch(std::logic_error&) {
    return Error::CorruptedArchive;
  }

  if (pos != value.size()) {
    return Error::CorruptedArchive;
  }

  return is.fail() ? Error::CorruptedArchive : Error::NoError;
}
