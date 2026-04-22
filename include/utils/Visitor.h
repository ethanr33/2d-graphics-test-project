
// Visitor pattern without inheritance!
// See https://en.cppreference.com/cpp/utility/variant/visit2

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;