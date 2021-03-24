#ifndef EQINTERFACE_H
#define EQINTERFACE_H


#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <ctime>

#include <windows.h>

#include "data.hpp"

namespace gym
{
	namespace input_interface
	{
		inline void clear_buf()
		{
			std::string tmp;
			std::getline(std::cin, tmp);
		}

		inline void clear_window()
		{
#ifdef WIN32
			std::system("cls");
#else
			std::system("clear");
#endif //WIN32

		}

		inline void pause()
		{
			std::cout.flush();
			for (std::size_t i = 0; i < 3; i++)
			{
				std::cout << '.';
				std::cout.flush();
				Sleep(1000);
			}

			std::cout << std::endl;
		}

		inline void out_pause()
		{
			std::string tmp;
			clear_buf();
			std::getline(std::cin, tmp);
		}	

        std::string get_eq_name_from_file_entry(const std::string &file_entry);
        std::string get_eq_cost_from_file_entry(const std::string &file_entry);
        std::string get_eq_date_from_file_entry(const std::string &file_entry);
        std::string get_eq_muscle_from_file_entry(const std::string &file_entry);
        std::string get_eq_type_from_file_entry(const std::string &file_entry);


		class InputEquipment
		{
			std::string __name;
			types::money __cost;
			std::time_t __data;
			
		protected:
			std::string __get_name()
			{
				return __name;
			}
			types::money __get_cost()
			{
				return __cost;
			}
			time_t __get_data()
			{
				return __data;
			}
	
		public:
			InputEquipment(const std::string &name_eq)
				: __name(name_eq)
			{	
	
				std::string cost_str;
				while (true)
				{
					std::cout << "\tCost: ";
					std::cin.clear();
					std::cin >> cost_str;
	
					try
					{
						__cost = std::stold(cost_str);
						break;
					}
					catch (...)
					{
                        std::cout << "Invalid input cost: " << std::endl;
					}
				}
	
				__data = time(nullptr);
			}

            InputEquipment(const std::string &name_eq, const std::string &file_entry)
            {
                __name = name_eq;
                __cost = std::stold(get_eq_cost_from_file_entry(file_entry));
                __data = std::stoul(get_eq_date_from_file_entry(file_entry));

            }
	
			class invalid_input 
				: public std::invalid_argument
			{
			public:
				invalid_input(const std::string &w)
					: std::invalid_argument(w)
				{
				}
			};
	
			virtual simulator::Equipment *create_eq() = 0;
            simulator::Equipment *create_eq_from_file();
			
			virtual ~InputEquipment()
			{
			}
		};
	
		class InputDumbells
			: public InputEquipment
		{
		public:
			InputDumbells(const std::string &name)
				: InputEquipment(name)
			{
			}

            InputDumbells(const std::string &name, const std::string &file_entry)
                : InputEquipment(name, file_entry) {}
		
			simulator::Equipment *create_eq() override final
			{
				
				return new simulator::Dumbells(__get_name(), __get_cost(), __get_data());
			}
		};

		class InputEM
			: public InputEquipment
		{
			std::string __muscle_group;

		public:
			InputEM(const std::string &name)
				: InputEquipment(name)
			{
				std::cout << "\tMuscle Group: ";
				std::cin >> __muscle_group;
			}

            InputEM(const std::string &name, const std::string &file_entry)
                : InputEquipment(name, file_entry)
            {
                __muscle_group = get_eq_muscle_from_file_entry(file_entry);
            }

			simulator::Equipment *create_eq()
			{
				return new simulator::ExersizeMachine(__get_name(), __muscle_group,
                        __get_cost(), __get_data());
            }
		};

		class InputOther
			: public InputEquipment
		{
		public:
			InputOther(const std::string &name)
				: InputEquipment(name)
			{
			}

            InputOther(const std::string &name, const std::string &file_entry)
                : InputEquipment(name, file_entry) {}

			simulator::Equipment *create_eq()
			{
				return new simulator::Other(__get_name(), __get_cost(), __get_data());
			}
		};

        std::string get_eq_name_from_file_entry(const std::string &file_entry);
        std::shared_ptr<simulator::Equipment> create_eq_from_file_entry(const std::string &file_entry);


	}
}

#endif // EQINTERFACE_H
