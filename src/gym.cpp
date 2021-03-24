#include "../include/gym.hpp"
#include "../include/eqinterface.h"
#include "../include/filemanager.h"

#include <iostream>
#include <memory>

namespace gym
{
    Gym::Gym(const std::string &filename)
        : __tp(&std::cout), __field_w({31, 31, 31, 11, 21}), __filename(filename)
	{

		__tp.AddColumn("Type", 30);
		__tp.AddColumn("Muscle group", 30);
		__tp.AddColumn("Name", 30);
		__tp.AddColumn("Cost", 10);
		__tp.AddColumn("Purchase Data", 20);
	}

	void Gym::create_eq(const std::string &name)
	{
		for (auto ptr = begin(); ptr != end(); ptr++)
		{
			if (ptr->first == name)
			{
				throw std::invalid_argument("This name already exists");
			}
		}

		int choice;
		while (true)
		{
			std::cout << "Input type:\n"
				<< "\t1. Dumbels\n"
				<< "\t2. Exersize machine\n"
				<< "\t3. Other\n";
		
			try
			{
				std::string tmp;
				std::cin >> choice;

				if (choice < 1 || choice > 3)
				{
					throw std::invalid_argument("Incorrect choice. Input number between 1 and 3.");
				}

				break;
			}
			catch (std::invalid_argument &e)
			{
				std::cout << e.what();
			}

		}

		input_interface::InputEquipment *new_eq;
		switch (choice)
		{
			case 1:
				new_eq = new input_interface::InputDumbells(name);
				break;
			case 2:
				new_eq = new input_interface::InputEM(name);
				break;
			case 3:
				new_eq = new input_interface::InputOther(name);
				break;
		}

		operator[](name) = new_eq->create_eq();
		delete new_eq;
	}

	void Gym::delete_eq(const std::string &name)
	{
		try
		{
			int ret = erase(name);
			if (ret == 0)
			{
				throw std::invalid_argument("Invalid name of Equipment");
			}
		}
		catch (std::invalid_argument &e)
		{
			std::cout << e.what();
			throw;
		}
	}

	void Gym::find(const std::string &name)
	{
		try
		{
			std::cout << *at(name) << std::endl;

			std::cin.get();
		}
		catch (std::out_of_range &)
		{
			std::cout << "Incorrect key of search";
			throw;
		}

	}

	types::money Gym::total_cost()
	{
		types::money ret = 0;
		for (auto ptr = begin(); ptr != end(); ptr++)
		{
			ret += ptr->second->get_cost();
		}

		return ret;
	}

    void Gym::load_equipment_from_file()
    {
        FileManager in(__filename);

        std::string file_entry;
        while ((file_entry = in.getline()) != "")
        {
           std::string name = input_interface::get_eq_name_from_file_entry(file_entry);
           operator[](name) = create_eq_by_type_from_file(name, file_entry);
        }
    }

    simulator::Equipment *Gym::create_eq_by_type_from_file(const std::string &name, const std::string &file_entry)
    {

        std::string type = input_interface::get_eq_type_from_file_entry(file_entry);
        input_interface::InputEquipment *new_eq;

        if (type == "Dumbells")
        {
            new_eq = new input_interface::InputDumbells(name, file_entry);
        }
        else if (type == "ExersizeMachine")
        {
            new_eq = new input_interface::InputEM(name, file_entry);
        }
        else if (type == "Other")
        {
            new_eq = new input_interface::InputOther(name, file_entry);
        }

        simulator::Equipment *result = new_eq->create_eq();

        delete new_eq;
        return result;
    }

    void Gym::save_equipment_to_file()
    {
        std::ofstream out(__filename, std::ios_base::out | std::ios_base::trunc);

        for (auto eq : *this)
        {
            out << eq.second->string() << '\n';
        }
    }
}
