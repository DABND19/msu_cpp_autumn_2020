#pragma once

#include <string>

#include "Serializers.hpp"

template <typename T>
Error Serializer::save(const T& object) {
  return object.serialize(*this);
}

template <typename... ArgsT>
Error Serializer::operator()(const ArgsT&... args) {
  return process(args...);
}

template <typename T, typename... ArgsT>
Error Serializer::process(const T& object, const ArgsT&... args) {
  if (save(object) == Error::CorruptedArchive) {
    return Error::CorruptedArchive;
  }

  return process(args...);
}

Error Serializer::process() {
  return os.fail() ? Error::CorruptedArchive : Error::NoError;
}

template <>
Error Serializer::save<bool>(const bool& object) {
  os << (object ? TRUE : FALSE) << Separator;

  return os.fail() ? Error::CorruptedArchive : Error::NoError;
}

template <>
Error Serializer::save<uint64_t>(const uint64_t& object) {
  os << object << Separator;

  return os.fail() ? Error::CorruptedArchive : Error::NoError;
}
