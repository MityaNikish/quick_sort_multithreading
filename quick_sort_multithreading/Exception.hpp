#pragma once

#include <string>
#include <exception>

class User_exception : public std::exception {};

class Invalid_value_exception : public User_exception {
    const char* what() const noexcept override;
};

class opening_file_exception : public User_exception {
    const char* what() const noexcept override;
};