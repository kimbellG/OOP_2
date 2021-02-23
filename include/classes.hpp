#ifndef __CLASSES_HPP__
#define __CLASSES_HPP__


#include <iostream>
#include <string>
#include <ctime>
#include <memory>
#include <iomanip>

namespace types
{
	typedef long double money;
}

namespace gym
{
	namespace simulator
	{
		class Equipment
		{
			std::string __name;

			types::money __cost;
			std::tm __purchase_date;
		public:
			Equipment(const std::string &name, 
				   	types::money cost, const std::tm &purchase_date)
				: __name(name), __cost(cost), __purchase_date(purchase_date)
			{
			}

			std::string get_name() const
			{
				return __name;
			}

			types::money get_cost() const
			{
				return __cost;
			}

			std::string get_purchdate(const std::string &time_format) const
			{
				char t_str[1024];

				int ret = std::strftime(t_str, 1024, time_format.c_str(), &__purchase_date);
				if (!ret)
				{
					throw std::invalid_argument("Incorrect time_format!!");
				}

				return t_str;	
			}

			virtual std::string get_type() const = 0;
			virtual std::string get_muscle_group() const = 0;

			friend std::ostream &operator<<(std::ostream &out, const gym::simulator::Equipment &source)
			{
				out << std::setw(12) << std::left << source.get_type() 
					<< std::setw(12) << source.get_muscle_group()
					<< std::setw(12) << source.__name 
					<< std::setw(6) << source.__cost
					<< std::setw(32) << source.get_purchdate("%x")
					<< std::endl;

				return out;
			}

			
			virtual ~Equipment()
			{
			}
			
			
		};

		class GeneralEquipment 
			: public Equipment
		{
			public:
				GeneralEquipment(const std::string &name, types::money cost,
						const std::tm &purchase_data)
					: Equipment(name, cost, purchase_data)
				{
				}

				std::string get_muscle_group() const override final
				{
					return "General";
				}

		};

		 class Dumbells
			 : public GeneralEquipment
		 {
			 public:
				 Dumbells(const std::string &name, types::money cost,
					  	  const std::tm &purchase_data)
					 : GeneralEquipment(name, cost, purchase_data)
				 {
				 }

				 std::string get_type() const override
				 {
					 return "Dumbells";
				 }
		};
	}
}
		
#endif // __CLASSES_HPP__
