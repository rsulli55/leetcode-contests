
auto char_to_pos = [&char_values](char c) {
    int pos = (static_cast<int>(c) - 'a') + 1;
    /* std::cout << "pos: " << pos << '\n'; */
    char_values.append(to_string(pos));
};

auto char_to_int = [](char c) {
    /* std::cout << "c - 0: " << c << '\n'; */
    return c - '0';
};


auto int_to_char = [](char c) {
    return static_cast<int>(c - '0');
};
auto char_to_int = [](int i) {
    return static_cast<char>(i + '0');
};
