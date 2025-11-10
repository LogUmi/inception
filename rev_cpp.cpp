#include <iostream> // std::cin, cout, cerr, clog
#include <string>	// std::string, .empty(), .c_str(), .size(), .clear(), .append, .replace, .substr, .swap
#include <cctype>	// toupper(char)..., tolower, isspace, isalnum, isalpha, iscntrl, isgraph, islower
#include <ctime>	// var clock_t, var size_t, var time_t, struct tm*, clock(), mktime, difftime, time(0), ctime
#include <iomanip>	// std::setfill, setw, setbase, setiosflags, resetiosflag
#include <fstream>	// std::ifstream, ofstream, .open, .close(), .eof(), .fail(), .bad()

int	get_str( std::string &input, std::string str )
{
	while (true)
	{
		std::cout << str;
		if (std::getline(std::cin, input)) // ou ifs
			return (0);
		else if (std::cin.eof())
		{
			std::cout << "\n[ERROR] End of file reached (EOF)." << std::endl;
			break;
		}
			else if (std::cin.fail())
		{
			std::cerr << "[ERROR] Logical error : failed to read (FAIL). May be wrong format." << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			continue;
		}
		else if (std::cin.bad())
		{	
			std::cerr << "\n[ERROR] Stream fatal error (BAD)!" << std::endl;
			break;
		}
	}
	return (1);
}

void	_displayTimestamp( void )
{
	time_t		stamp;
	struct tm*	ts;
	
	time( &stamp );
	ts = localtime(&stamp);
	std::cout 	<< "[" << ts->tm_year + 1900 << std::setfill('0') << std::setw(2) 
				<< ts->tm_mon << std::setw(2) << ts->tm_mday << "_" << std::setw(2)
				<< ts->tm_hour << std::setw(2) << ts->tm_min << std::setw(2)
				<< ts->tm_sec << "] ";
	return ;
}

