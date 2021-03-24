#include <string>
#include <utility>
#include <exception>

#include "../include/procesing_entry.hpp"

namespace gym {
    namespace input_interface {
        std::string get_eq_name_from_file_entry(const std::string &file_entry)
        {
            return get_word_by_separator(file_entry, 0);
        }

        std::string get_word_by_separator(const std::string &str, const int number_of_word, const char separator)
        {
            auto start_end_word = get_start_end_word(str, number_of_word, separator);
            return str.substr(std::get<0>(start_end_word), get_count_word(std::get<0>(start_end_word), std::get<1>(start_end_word)));
        }

        std::pair<std::size_t, std::size_t> get_start_end_word(const std::string &str, const int number_of_word, const char separator)
        {
            std::size_t start = get_start_pos(str, number_of_word, separator);
            std::size_t end = get_end_pos(str, number_of_word, separator);
            return std::make_pair(start, end);
        }

        std::size_t get_count_word(std::size_t start, std::size_t end)
        {
            return (end == std::string::npos) ? end : end-start;
        }

        std::size_t get_start_pos(const std::string &str, const int number_of_word, const char separator)
        {
            std::size_t pos = 0;
            for (int i = 0; i < number_of_word; i++)
            {
                pos = str.find(separator, ++pos);
                if (pos == std::string::npos)
                {
                    throw std::invalid_argument("Invalid string with separator");
                }
            }
            return pos;
        }

        std::size_t get_end_pos(const std::string &str, std::size_t start_pos, const char separator)
        {
            return str.find(separator, start_pos);
        }


    }
}


