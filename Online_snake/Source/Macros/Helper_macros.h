#pragma once

#include "boost/preprocessor.hpp"
#include <string_view>

#define ENUM_TO_STRING_CASE(i, name, enumator)                                                                         \
    case name::enumator:                                                                                               \
        return BOOST_PP_STRINGIZE(enumator);

#define DECLARE_ENUM(name, type, ...)                                                                                  \
    enum class name : type                                                                                             \
    {                                                                                                                  \
        BOOST_PP_SEQ_ENUM(BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                                                       \
    };                                                                                                                 \
    static std::string_view enum_to_string(name value) noexcept                                                        \
    {                                                                                                                  \
        switch (value)                                                                                                 \
        {                                                                                                              \
            BOOST_PP_SEQ_FOR_EACH(ENUM_TO_STRING_CASE, name, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))                    \
                                                                                                                       \
        default:                                                                                                       \
            return "unkown";                                                                                           \
        }                                                                                                              \
    }
