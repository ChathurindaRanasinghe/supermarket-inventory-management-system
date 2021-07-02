#include "Supply.h"

ostream& operator<<(ostream& out, const Supply& obj)
{
	out << obj.source << "\n" << obj.vehicle_type << "\n" << obj.reg_number << "\n" << obj.supply_item_name << "\n" << obj.supply_quantity <<  "\n" << obj.origin_name << "\n" << obj.date_of_depature.day << "\n"
		<< obj.date_of_depature.month << "\n" << obj.date_of_depature.year << "\n" << obj.date_of_arrival.day << "\n"
		<< obj.date_of_arrival.month << "\n" << obj.date_of_arrival.year << "\n" << obj.status << endl;
	return out;
}

istream& operator >> (istream& in, Supply& obj)
{
	in >> obj.source;
	in >> obj.vehicle_type;
	in >> obj.reg_number;
	in >> obj.supply_item_name;
	in >> obj.supply_quantity;
	in >> obj.origin_name;
	in >> obj.date_of_depature.day;
	in >> obj.date_of_depature.month;
	in >> obj.date_of_depature.year;
	in >> obj.date_of_arrival.day;
	in >> obj.date_of_arrival.month;
	in >> obj.date_of_arrival.year;
	in >> obj.status;

	return in;
}

void Supply::get_data()
{
	display_source_type();
	display_vehicle_types();

	cout << "\nAdd New Supply Item\n---------------------------------------\n";

	cout << "Enter item name\t\t: ";
	getline(cin, supply_item_name);
	to_upper(supply_item_name, 1);

	supply_quantity = int_check("Enter number of items\t");

	cout << "Enter item origin\t: ";
	getline(cin, origin_name);
	to_upper(origin_name, 1);

	source = (supply_type_check() == 1 ? "Local" : "International");

	date_of_depature = check_date("Enter depature date");

	date_of_arrival = check_date("Enter arival date");

	if (source == "Local")
	{
		int v_t = vehicle_category_check();
		if (v_t == 1)
			vehicle_type = "Large Truck";
		else if (v_t == 2)
			vehicle_type = "Small Truck";
		else
			vehicle_type = "Van";
	}
	else
		vehicle_type = "Ship";
	
	cout << "Enter register number\t: ";
	getline(cin, reg_number);
	to_upper(reg_number, 1);

	status = 0;
	//ststus?????
	//cout << "Press Enter to save\n";
	//get keystroke

}

void Supply::show_data()
{
	cout << "\nSupply Details\n---------------------------------------\n";
	to_upper(supply_item_name, 0);
	cout << "Item name\t\t: " << supply_item_name << endl;
	cout << "Quantity\t\t: " << supply_quantity << endl;
	to_upper(origin_name, 0);
	cout << "Item origin\t\t: " << origin_name << endl;
	to_upper(source, 0);
	cout << "Item source\t\t: " << source << endl;
	cout << "Depature date\t\t: " << date_of_depature.year << "." << date_of_depature.month << "." << date_of_depature.day << endl;
	cout << "Arrival date\t\t: " << date_of_arrival.year << "." << date_of_arrival.month << "." << date_of_arrival.day << endl;
	to_upper(vehicle_type, 0);
	cout << "Vehicle type\t\t: " << vehicle_type << endl;
	cout << "Vehicle register number\t: " << reg_number << endl;
	cout << "Stock status\t\t: ";
	if (status)
		cout << "Accepted";
	else
		cout << "In transit";
	cout << endl;
}

void Supply::supply_write_data() {
	ofstream write_file;
	write_file.open("Supply\\supply_data.txt", ios::app);
	to_upper(this->source, 1);
	to_upper(this->vehicle_type, 1);
	to_upper(this->reg_number, 1);
	to_upper(this->supply_item_name, 1);
	to_upper(this->origin_name, 1);

	write_file << *this;
}

vector<Supply>  Supply::supply_read_data()
{
	vector<Supply> items;
	ifstream readfile;
	readfile.open("Supply\\Supply_data.txt");
	Supply item;
	while (readfile >> item)
		items.emplace_back(item);

	return items;
}

void Supply::update()
{
	Stock temp;
	vector<Stock> itm;

	find_and_display(temp, itm);

	int ctgry = temp.get_item_category();

	if (ctgry > 2) {
		temp.set_supply_type(supply_type_check());
	}

	int q = int_check("Enter number of items\t");

	temp.set_quantity(q);
	
	write_all_data(temp);
}

bool Supply::check_item()
{
	vector<Stock> items = find_item(supply_item_name, true);
	return bool(items.size());
}

//string Supply:: get_supply_item_name()
//{
//	return supply_item_name;
//}
//int Supply::get_supply_quantity()
//{
//	return supply_quantity;
//}
//string Supply::get_source()
//{
//	return source;
//}
//string Supply::get_origin_name()
//{
//	return origin_name;
//}
//Date Supply::get_date_of_depature()
//{
//	return date_of_depature;
//}
//Date Supply::get_date_of_arrival()
//{
//	return date_of_arrival;
//}
//string Supply::get_vehicle_type()
//{
//	return vehicle_type;
//}
//string Supply::get_reg_number()
//{
//	return reg_number;
//}
//bool Supply::get_status()
//{
//	return status;
//}

void Supply:: display_supply_table(vector <Supply>& supply)
{
	size_t max_name = 9, max_origin = 6, max_reg_num = 15;
	size_t size = supply.size();
	int length = 150;

	for (int i = 0; i < size; i++)
	{
		if (supply[i].supply_item_name.length() > max_name)
			max_name = supply[i].supply_item_name.length() + 1;
	}

	for (int i = 0; i < size; i++)
	{
		if (supply[i].origin_name.length() > max_origin)
			max_origin = supply[i].origin_name.length();
	}

	for (int i = 0; i < size; i++)
	{
		if (supply[i].reg_number.length() > max_reg_num)
			max_reg_num = supply[i].reg_number.length();
	}

	cout << "\n";
	for (int i = 0; i < (max_name + max_origin + max_reg_num + length - 18) / 2; i++)
		cout << " ";
	cout << "Supply Table\n";

	for (int i = 0; i < max_name + max_origin + max_reg_num + length; i++)
		cout << "-";

	cout << "\n|";
	for (int i = 0; i < (max_name) / 2; i++)
		cout << " ";
	cout << "   Item Name   ";
	for (int i = 0; i < (max_name) / 2; i++)
		cout << " ";
	cout << "|";

	cout << "     " << "Quantity" << "     |";

	cout << "     " << "Source" << "     |";

	for (int i = 0; i < (max_origin) / 2; i++)
		cout << " ";
	cout << "  Origin Name  ";
	for (int i = 0; i < (max_origin) / 2; i++)
		cout << " ";
	cout << "|";

	cout << " " << "Date of Depature" << " |";

	cout << " " << "Date of Arrival" << " |";

	cout << "   " << "Vehicle Type" << "   |";

	for (int i = 0; i < (max_reg_num) / 2; i++)
		cout << " ";
	cout << " Registration Number ";
	for (int i = 0; i < (max_reg_num) / 2; i++)
		cout << " ";
	cout << "|";

	cout << "     " << "Status" << "     |\n";

	for (int i = 0; i < max_name + max_origin + max_reg_num + length; i++)
		cout << "-";

	cout << endl;
	for (int i = 0; i < size; i++)
	{
		cout << endl;

		cout << "  ";

		to_upper(supply[i].supply_item_name, 0);
		cout << supply[i].supply_item_name;
		for (int j = 0; j < (max_name - supply[i].supply_item_name.length()); j++)
			cout << " ";
		cout << "    ";

		cout << supply[i].supply_quantity << "\t";

		cout << supply[i].source;
		for (int j = 0; j < (13 - supply[i].source.length()); j++)
			cout << " ";
		cout << "       ";

		to_upper(supply[i].origin_name, 0);
		cout << supply[i].origin_name;
		for (int j = 0; j < (max_origin - supply[i].origin_name.length()); j++)
			cout << " ";
		cout << "    ";

		cout << supply[i].date_of_depature.year << "." << supply[i].date_of_depature.month << "." << supply[i].date_of_depature.day <<"\t";

		cout << supply[i].date_of_arrival.year << "." << supply[i].date_of_arrival.month << "." << supply[i].date_of_arrival.day << "\t";

		cout << supply[i].vehicle_type;
		for (int j = 0; j < (12 - supply[i].vehicle_type.length()); j++)
			cout << " ";
		cout << "       ";

		cout << supply[i].reg_number;
		for (int j = 0; j < (max_reg_num - supply[i].reg_number.length()); j++)
			cout << " ";
		cout << "    ";

		if (supply[i].status)
			cout << "Accepted";
		else
			cout << "In transit";

	}
	cout << endl;
	for (int i = 0; i < max_name + max_origin + max_reg_num + length; i++)
		cout << "-";
	cout << endl;
}