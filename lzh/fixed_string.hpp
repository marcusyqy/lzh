#include <cstdint>
#include <string_view>

namespace lzh {
/*
 * this class is mainly for being able to write
 * hello<"hello"> in template arguments
 * */
template<size_t N>
struct fixed_string {
    char buf[N + 1]{};

    constexpr fixed_string(char const* s) {
        for (size_t i {}; i != N; ++i)
            buf[i] = s[i];
    }

    constexpr operator char const *() const { return buf; }

    auto operator<=>(const fixed_string&) const = default;
};

template<size_t N>
fixed_string(char const (&)[N]) -> fixed_string<N - 1>;

} // namespace lzh
