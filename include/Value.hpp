#pragma once
#include <variant>
#include <stdexcept>

namespace customType{
    struct Value{
        std::variant<double,std::monostate> data;

        Value() : data(std::monostate()) {}

        Value(double d) : data(d) {}

        bool isNumber(){
            return std::holds_alternative<double>(data);
        }

        double getNumber(){
            if(!isNumber()) throw std::runtime_error("Not a Number");
            return std::get<double>(data);
        }

        bool isNone(){
            return std::holds_alternative<std::monostate>(data);
        }
    };
}