#include <string>
#include <vector>
#include <tuple>
#include <cstdlib>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while (stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}

using ip_adress = std::tuple<uint8_t, uint8_t, uint8_t, uint8_t>;

/*
bool operator == ( ip_adress &lhs, ip_adress &rhs )
{
    if((std::get<0>(lhs) == std::get<0>(rhs)) &&
       (std::get<1>(lhs) == std::get<1>(rhs)) &&
       (std::get<2>(lhs) == std::get<2>(rhs)) &&
       (std::get<3>(lhs) == std::get<3>(rhs)))
        return true;
    else
        return false;
}*/

ip_adress getIpAdress(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);

	for(int i = 0; stop != std::string::npos; ++i)
		while (stop != std::string::npos)
		{
			r.push_back(str.substr(start, stop - start));
	
			start = stop + 1;
			stop = str.find_first_of(d, start);
		}
		r.push_back(str.substr(start));

	if(r.size() != 4)
		throw std::invalid_argument("wrong ip adress format!");

	return std::make_tuple(std::stoi(r.at(0)), std::stoi(r.at(1)), std::stoi(r.at(2)), std::stoi(r.at(3)));
}
