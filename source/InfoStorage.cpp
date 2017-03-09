#include "InfoStorage.hpp"

using namespace std;

void InfoStorage::GetInfo()
{
	const uint max_size=10000;
	const char greet[]="Welcome to cellurar automata \"Steppers\" emulator!\n"
		"Before we get started, you will need to provide some info.\n";
	const char get_size[]="Please, type in height and width of the map in range"
		" from 1 to 10^4\n";
	const char get_window_size[]="Here is a list of window modes avalible:\n"
		"0: 640x480\n"
		"1: 800x600\n"
		"2: 1024x768\n"
		"3: 1280x1024\n"
		"4: 1600x900\n"
		"5: 1680x1050\n"
		"Choose one of them by typing in an integer from 0 to 6:\n";
	const char wrong_number[]="Sike! That's the wrong number!\n";
	const char get_delay[]="Now please type a desired delay for the steps(ms)\n";
	cout << greet << get_window_size;
	window_size_option = 10;
	cin >> window_size_option;
	if (window_size_option < 0 || window_size_option > 5 || cin.fail())
		do
		{
			cout << wrong_number << get_window_size;
			while (cin.fail())
			{
				cin.clear();
				char c;
				cin >> c;
			}
			cin >> window_size_option;
		} while (window_size_option < 0 || window_size_option > 5 || cin.fail());

	cout << get_size;
	cin >> height >> width;
	if (height < 1 || width < 1 || height > max_size || width > max_size || cin.fail())
		do
		{
			cout << wrong_number << get_size;
			if (cin.fail())
			{
				cin.clear();
				char c;
				cin >> c;
			}
			cin >> height >> width;
		} while  (height < 1 || width < 1 || height > max_size || width > max_size || cin.fail());
	cout << get_delay;
	cin >> delay;
	while (delay < 0 || cin.fail())
	{
		cout << wrong_number << get_delay;
		if (cin.fail())
		{
			cin.clear();
			char c;
			cin >> c;
		}
		cin >> delay;
	}
}
