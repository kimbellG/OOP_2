#ifndef GYM_HPP
#define GYM_HPP

#include "data.hpp"

#include <map>
#include <ctime>

namespace gym
{
	namespace io
	{


	}


	class Gym
			: std::map<std::string, simulator::Equipment *>
	{
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

		simulator::Equipment find(const std::string &name);
		void sort(sort_field);

		types::money total_cost();

		friend std::ostream &operator<<(std::ostream &out, Gym &source);
	};
}

#endif // GYM_HPP
