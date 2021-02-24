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
			std::string __data;

			bprinter::TablePrinter __tp;
		public:
					Equipment(const std::string &name, 
					types::money cost, const std::string &purchase_date)
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

			std::string get_purchdate() const
			{
				return __data;
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
				source.__tp << source.get_type().substr(0, 30).c_str() << source.get_muscle_group().substr(0, 30).c_str() << source.__name.substr(0, 30).c_str()  << source.__cost << source.get_purchdate().substr(0, 30).c_str() ;
				source.__tp.set_stream(&std::cout);

				return out;
			}

			void print_footer(std::ostream &out)
			{
				__tp.set_stream(&out);
				__tp.PrintFooter();
				__tp.set_stream(&std::cout);
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
						const std::string &purchase_data)
					: Equipment(name, cost, purchase_data)
				{
				}

				std::string get_muscle_group() const override final
				{
					return "General";
				}

		};

		class SpecialEquipment
			: public Equipment
		{
			std::string __muscle_group;
		public:
			SpecialEquipment(const std::string &name, const std::string muscle_group,
					types::money cost, const std::string &purchase_data)
				: Equipment(name, cost, purchase_data), __muscle_group(muscle_group)
			{
			}

			std::string get_muscle_group() const override final
			{
				return __muscle_group;
			}
		};

		 class Dumbells
			 : public GeneralEquipment
		 {
			 public:
				 Dumbells(const std::string &name, types::money cost,
						  const std::string &purchase_data)
					 : GeneralEquipment(name, cost, purchase_data)
				 {
				 }

				 std::string get_type() const override
				 {
					 return "Dumbells";
				 }
		};

		class ExersizeMachine
			: public SpecialEquipment
		{
		public:
			ExersizeMachine(const std::string &name, const std::string &muscle_group,
					types::money cost, const std::string &purchase_data)
				: SpecialEquipment(name, muscle_group, cost, purchase_data)
				{
				}

			std::string get_type() const override
			{
				return "Exersize Machine";
			}
		};

		class Other
			: public GeneralEquipment
		{
		public:
			Other(const std::string &name, types::money cost, const std::string &purchase_data)
				: GeneralEquipment(name, cost, purchase_data)
			{
			}

			std::string get_type() const override
			{
				return "Other";
			}
		};
	};
}
		
#endif // __CLASSES_HPP__
