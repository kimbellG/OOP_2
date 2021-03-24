#ifndef GYM_HPP
#define GYM_HPP

#include "data.hpp"
#include "../bprinter-master/include/bprinter/table_printer.h"
#include "consolemanipulator.h"
#include "eqinterface.h"

#include <map>
#include <ctime>
#include <string>

namespace gym
{
	class Gym
			: public std::map<::std::string, simulator::Equipment *>
	{
		bprinter::TablePrinter __tp;
		::std::vector<::std::size_t> __field_w;

        std::string __filename;
        static simulator::Equipment *create_eq_by_type_from_file(const std::string &name, const std::string &file_entry);

	public:
        Gym(const std::string &filename);

        void load_equipment_from_file();
        void save_equipment_to_file();

		enum sort_field
		{
			type = 0,
			muscule_group,
			name,
			cost,

		};

		void create_eq(const std::string &name);
		void delete_eq(const std::string &name);

		void find(const std::string &name);

		types::money total_cost();

		friend std::ostream &operator<<(std::ostream &out, Gym &source)
		{
			source.__tp.set_stream(&out);
			source.__tp.PrintHeader();
			
			for (auto& ptr : source)
			{
				std::cout << *ptr.second;
			}

			source.__tp.PrintFooter();
			
			return out;
		}

		void edit()
		{
			ConsoleManipulator manip(__field_w, 1);

			std::size_t index = 0;
			std::size_t field = 0;
			COORD start_pos = {30, 3};

			while (field == 0)
			{
				manip.mvtable(index, field, start_pos, size(), __field_w.size() - 1);
			}

			auto iter = begin();
			for (std::size_t i = 0; i < index; i++)
			{
				iter++;
			}

			std::string nw_val;
			std::cout << "Input new value: ";
			std::cin.ignore(20, '\n');
			std::getline(std::cin, nw_val);

			try
			{
				std::string nw_name = iter->second->set(field, nw_val);
			}
			catch (std::invalid_argument &e)
			{
				std::cout << e.what() << std::endl
						  << "Repeat";
				input_interface::pause();
			}

		}

	};
}

#endif // GYM_HPP
