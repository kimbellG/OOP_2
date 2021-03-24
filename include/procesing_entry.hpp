#ifndef PROCESING_ENTRY_HPP
#define PROCESING_ENTRY_HPP


#include <string>
#include <utility>

namespace gym {
    namespace input_interface {
        std::string get_word_by_separator(const std::string &str, const int number_of_word, const char separator = ':');
        std::pair<std::size_t, std::size_t> get_start_end_word(const std::string &str, const int number_of_word, const char separator = ':');
        std::size_t get_count_word(std::size_t start, std::size_t end);
        std::size_t get_start_pos(const std::string &str, const int number_of_word, const char separator);
        std::size_t get_end_pos(const std::string &str, std::size_t start_pos, const char separator);
    }
}

#endif // PROCESING_ENTRY_HPP
