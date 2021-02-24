#ifndef GYM_HPP
#define GYM_HPP

#include "data.hpp"
#include "../bprinter-master/include/bprinter/table_printer.h"

#include <map>
#include <ctime>

namespace gym
{
	class Gym
			: std::map<std::string, simulator::Equipment *>
	{
		bprinter::TablePrinter __tp;
	public:
		Gym();

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

		void *operator new(std::size_t size)
		{
			throw std::bad_alloc();
		}

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

	};
}

#endif // GYM_HPP
