#include <iostream>
#include <string>
#include "List.h"
#include "Map.h"

using namespace std;

class Shannon
{
private:
	List<bool> encoded_string; /* Хранит закодированную строку из нулей и единиц */
	map<char, float, List<bool>> map; /* символ, вероятнотность встречи, код символа */
	List<bool> code_symbols;	/* Промежуточный список, который хранит код символа при его составлении в set_codes */
	List<pair<char, float>> symbols_and_their_count;	/* символы и их количество в введенной строке */

	void set_codes(size_t indexL, size_t indexR);
public:
	string input_string;
	Shannon() = default;
	void show_on_display();
	List<bool> getEncodedString();
	void Convertion_input_string(string str);
	List<char> decode(string str);
};

List<char> Shannon::decode(string str)
{
	if (input_string.empty())
		throw runtime_error("Input string is empty");

	string encoded_string_to_decode = str;

	if (encoded_string_to_decode.empty())
		throw runtime_error("The string is empty");

	List<char> decoded_string;
	List<bool> temp_code;

	for (int i = 0; i < encoded_string_to_decode.length(); i++)
	{
		temp_code.push_back(encoded_string_to_decode.at(i) - 48);
		if (map.code(temp_code))
		{
			decoded_string.push_back(map.find_key(temp_code));
			temp_code.clear();
		}
	}

	if (!temp_code.isEmpty())
	{
		throw runtime_error("The string is wrong");
	}
	return decoded_string;
}

void Shannon::Convertion_input_string(string str)
{
	if (str.empty())
		throw runtime_error("Input string is empty");
	input_string = str;

	for (int i = 0; i < input_string.length(); i++)
	{
		map.insert(input_string.at(i), float(1), float(1));
	}

	for (int i = 0; i < input_string.length(); i++)
	{
		symbols_and_their_count.insert_with_sorting(input_string.at(i), map.find_value1(input_string[i]));
	}

	if (symbols_and_their_count.get_size() == 1)
	{
		code_symbols.push_back(0);
		map.set_value2(input_string.at(0), code_symbols);
	}
	else
		set_codes(0, symbols_and_their_count.get_size());

	for (size_t i = 0; i < input_string.length(); i++)
	{
		encoded_string.push_back(map.find_value2(input_string.at(i)));
	}
}

List<bool> Shannon::getEncodedString()
{
	return encoded_string;
}

void Shannon::show_on_display()
{
	if (input_string.empty())
		throw runtime_error("There is no string");
	cout << "Входная строка: ";
	cout << input_string << endl;

	cout << "Количество символов: ";
	cout << input_string.length() << endl;

	cout << "Закодированная строка: ";
	for (size_t i = 0; i < input_string.length(); i++)
	{
		map.find_value2(input_string.at(i)).print_to_console();
		cout << " ";
	}
	cout << '\n';
	cout << "Количество бит во входной строке: " << input_string.length() * 8 << endl;
	cout << "Количество бит в закодированной строке: " << encoded_string.get_size() << endl;
	cout << "Коэффициент сжатия:" << (float)encoded_string.get_size() * 100 / (input_string.length() * 8) << " %" << endl;

	cout << "Символ" << "\t" << "Частота встречаемости" << "\t" << "Код символа" << endl;
	for (int i = 0; i < symbols_and_their_count.get_size(); i++)
	{
		cout << " \"" << symbols_and_their_count.at(i).first << "\"\t          " << symbols_and_their_count.at(i).second << "              ";
		map.find_value2(symbols_and_their_count.at(i).first).print_to_console();
		cout << endl;
	}
}

void Shannon::set_codes(size_t indexL, size_t indexR)
{
	if (indexR - indexL == 2)
	{
		/* Осталось два символа, которые не получили свой код */
		code_symbols.push_back(0);
		map.set_value2(symbols_and_their_count.at(indexL).first, code_symbols);
		code_symbols.pop_back();
		code_symbols.push_back(1);
		map.set_value2(symbols_and_their_count.at(indexR - 1).first, code_symbols);
		code_symbols.pop_back();
		return;
	}
	else if (indexR - indexL == 1)
	{
		/* Остался один символ, который не получил свой код*/
		map.set_value2(symbols_and_their_count.at(indexL).first, code_symbols);
		return;
	}
	else
	{
		float dS = 0, sum = 0;
		for (int i = indexL; i < indexR; i++)
		{
			dS += symbols_and_their_count.at(i).second;
		}
		dS /= 2;
		size_t newIndex = indexL;
		for (int i = indexL; i < symbols_and_their_count.get_size(); i++)
		{
			sum += symbols_and_their_count.at(i).second;
			newIndex++;
			if (sum >= dS)
			{
				break;
			}
		}
		code_symbols.push_back(0);
		set_codes(indexL, newIndex);
		code_symbols.pop_back();
		code_symbols.push_back(1);
		set_codes(newIndex, indexR);
		code_symbols.pop_back();
	}
}