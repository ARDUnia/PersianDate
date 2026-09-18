#pragma once

#include <cstdio>
#include <string>

using byte = unsigned char;

class String {
 public:
  String() = default;
  String(const char* value) : value_(value ? value : "") {}
  String(const std::string& value) : value_(value) {}

  const char* c_str() const {
    return value_.c_str();
  }

  bool operator==(const char* other) const {
    return value_ == (other ? other : "");
  }

 private:
  std::string value_;
};
