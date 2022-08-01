#pragma once

#include <variant>

namespace lzh {

namespace detail::error {

struct error_t {};
} // namespace detail::error

template<typename Error>
class unexpected {
public:
    using error_type = Error;

    // accessors
    constexpr const error_type& error() const& noexcept { return error_; }
    constexpr error_type& error() & noexcept { return error_; }
    constexpr const error_type&& error() const&& noexcept {
        return std::move(error_);
    }
    constexpr error_type&& error() && noexcept { return std::move(error_); }

private:
    error_type error_;
};

template<typename ValueType, typename Error = detail::error::error_t>
class expected {
public:
    using value_type = ValueType;
    using error_type = Error;
    using unexpected_type = unexpected<error_type>;

    // constructors
    constexpr expected() : value_{error_type()} {}
    constexpr expected(const ValueType& value) : value_{value} {}
    constexpr expected(ValueType&& value) : value_{std::move(value)} {}
    constexpr expected(unexpected_type&& ut) : value_{std::move(ut.error())} {}

    // observers
    bool has_value() const noexcept {
        return std::holds_alternative<value_type>(value_);
    }

    bool has_error() const noexcept {
        return std::holds_alternative<error_type>(value_);
    }

    operator bool() const noexcept { return has_value(); }

    // accessors
    value_type& value() & noexcept {
        return const_cast<value_type&>(std::as_const(*this).value());
    }
    value_type&& value() && noexcept {
        return const_cast<value_type&&>(std::as_const(*this).value());
    }
    const value_type& value() const & noexcept {
        return std::get<value_type>(value_);
    }
    const value_type&& value() const && noexcept {
        return std::move(std::get<value_type>(value_));
    }

    error_type& error() & noexcept {
        return const_cast<error_type&>(std::as_const(*this).error());
    }
    error_type&& error() && noexcept {
        return const_cast<error_type&&>(std::as_const(*this).error());
    }
    const error_type&& error() const&& noexcept {
        return std::move(std::get<error_type>(value_));
    }
    const error_type& error() const& noexcept {
        return std::get<error_type>(value_);
    }

    auto operator*() noexcept { return value(); }
    auto operator*() const noexcept { return value(); }

private:
    std::variant<value_type, error_type> value_;
};

} // namespace lzh
