#ifndef __CLASSES_HPP__
#define __CLASSES_HPP__


#include <iostream>
#include <string>
#include <ctime>
#include <memory>
#include <iomanip>

#include <../bprinter-master/include/bprinter/table_printer.h>


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
			std::time_t __data;

			bprinter::TablePrinter __tp;
		protected:
			enum base_attr
			{
				__name_i = 2,
				__cost_i
			};
		public:
					Equipment(const std::string &name, 
					types::money cost, time_t purchase_date)
				: __name(name), __cost(cost), __data(purchase_date), __tp(&std::cout)
				{
					__tp.AddColumn("Type", 30);
					__tp.AddColumn("Muscle group", 30);
					__tp.AddColumn("Name", 30);
					__tp.AddColumn("Cost", 10);
					__tp.AddColumn("Purchase Data", 20);
				}

			std::string get_name() const
			{
				return __name;
			}

			types::money get_cost() const
			{
				return __cost;
			}

			std::string get_purchdate(const std::string &format) const
			{
				std::tm *data_tm = std::localtime(&__data);
				char time_str[1024];
				int ret = std::strftime(time_str, 1024, format.c_str(), data_tm);
	
				if (!ret)
				{
					throw std::invalid_argument("Invalid value time");
				}

				return time_str;
			}

			virtual std::string set(const int attr, const std::string &value)
			{
				switch (attr) {
				case __name_i:
					__name = value;
					break;
				case __cost_i:
					__cost = std::stold(value);
					break;
				default:
					throw std::invalid_argument("Incorrect attribute.");
				}

				return __name;
			}

			virtual std::string get_type() const = 0;
			virtual std::string get_muscle_group() const = 0;

			void print_header(std::ostream &out)
			{
				__tp.set_stream(&out);
				__tp.PrintHeader();
				__tp.set_stream(&std::cout);
			}
			friend std::ostream &operator<<(std::ostream &out, gym::simulator::Equipment &source)
			{
				source.__tp.set_stream(&out);
				source.__tp << source.get_type().substr(0, 30).c_str() << source.get_muscle_group().substr(0, 30).c_str() << source.__name.substr(0, 30).c_str()  << source.__cost << source.get_purchdate("%x").substr(0, 30).c_str() ;
				source.__tp.set_stream(&std::cout);

				return out;
			}

			void print_footer(std::ostream &out)
			{
				__tp.set_stream(&out);
				__tp.PrintFooter();
				__tp.set_stream(&std::cout);
			}

			virtual std::string string() const
			{
				return __name + ':' + std::to_string(__cost) + ':' + std::to_string(__data);
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
						time_t purchase_data)
					: Equipment(name, cost, purchase_data)
				{
				}

				std::string get_muscle_group() const override final
				{
					return "General";
				}

				std::string string() const override {
					return Equipment::string() + ':' + "General";
				}

		};

		class SpecialEquipment
			: public Equipment
		{
			std::string __muscle_group;
		public:
			SpecialEquipment(const std::string &name, const std::string muscle_group,
					types::money cost, std::time_t purchase_data)
				: Equipment(name, cost, purchase_data), __muscle_group(muscle_group)
			{
			}

			std::string get_muscle_group() const override final
			{
				return __muscle_group;
			}

			std::string set(const int attr, const std::string &value) override
			{
				if (attr == 1)
				{
					__muscle_group = value;
				}
				else
				{
					Equipment::set(attr, value);
				}

				return get_name();
			}

			std::string string() const override 
			{
				return Equipment::string() + ':' + __muscle_group;
			}
		};

		 class Dumbells
			 : public GeneralEquipment
		 {
			 public:
				 Dumbells(const std::string &name, types::money cost,
						  std::time_t purchase_data)
					 : GeneralEquipment(name, cost, purchase_data)
				 {
				 }

				 std::string get_type() const override
				 {
					 return "Dumbells";
				 }

				 std::string string() const override
				 {
					 return GeneralEquipment::string() + ':' + "Dumbells";
				 }
		};

		class ExersizeMachine
			: public SpecialEquipment
		{
		public:
			ExersizeMachine(const std::string &name, const std::string &muscle_group,
					types::money cost, std::time_t purchase_data)
				: SpecialEquipment(name, muscle_group, cost, purchase_data)
				{
				}

			std::string get_type() const override
			{
				return "Exersize Machine";
			}

			std::string string() const override
			{
				return SpecialEquipment::string() + ':' + "ExersizeMachine";
			}
		};

		class Other
			: public GeneralEquipment
		{
		public:
			Other(const std::string &name, types::money cost, std::time_t purchase_data)
				: GeneralEquipment(name, cost, purchase_data)
			{
			}

			std::string get_type() const override
			{
				return "Other";
			}

			std::string string() const override
			{
				return GeneralEquipment::string() + ':' + "Other";
			}
		};
	};
}
		
#endif // __CLASSES_HPP__
