#ifndef EQINTERFACE_H
#define EQINTERFACE_H


#include <iostream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <string>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif //WIN32

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
#ifdef WIN32
				Sleep(1000);
#else
				sleep(1);
#endif //WIN32
			}

			std::cout << std::endl;
		}

		inline void out_pause()
		{
			std::string tmp;
			clear_buf();
			std::getline(std::cin, tmp);
		}	

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
						std::cout << "Invalide input cost: " << std::endl;
					}
				}
	
				__data = time(nullptr);
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

			simulator::Equipment *create_eq()
			{
				return new simulator::Other(__get_name(), __get_cost(), __get_data());
			}
		};
	}
}

#endif // EQINTERFACE_H
