#include <iostream> // std::cin, cout, cerr, clog
#include <ostream>	// std::ostream
#include <string>	// std::string, .empty(), .c_str(), .size(), .clear(), .append, .replace, .substr, .swap
#include <cctype>	// toupper(char)..., tolower, isspace, isalnum, isalpha, iscntrl, isgraph, islower
#include <ctime>	// var clock_t, var size_t, var time_t, struct tm*, clock(), mktime(tm), difftime, time(0), ctime
#include <iomanip>	// std::setfill, setw, setbase, setiosflags, resetiosflag
#include <fstream>	// std::ifstream, ofstream, .open, .close(), .eof(), .fail(), .bad()
#include <climits>	// INT_MIN, INT_MAX, CHAR_BIT, LONG_MIN, LONG_MAX ... 
#include <climits> 	// FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX, LDBL_MIN, LDBL_MAX
#include <cmath>	// exp, log, cos, acos, sin, asin, sqrt, pow, round, floor, ceil, fabs
#include <cstdlib>	// srand(time(NULL)), rand()%XX, strtod, atoi, itoa
#include <cstddef>	// size_t, NULL
#include <exception>// std::exception, bad_alloc, bad_cast,	bad_exception, bad_function_call, bad_typeid, bad_weak_ptr, ios_base::failure, logic_error, runtime_error
#include <stdexcept>// logic_error: domain_error, invalid_argument, length_error, out_of_range / runtime_error: range_error, overflow_error, underflow_error	U
#include <algorithm>// find, equal, sort, reverse, lower_bound, min
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <array>
#include <iterator>	// distance
#include <limits>	// std::numeric_limits<T>::min()
#include <utility>	// std::pair< int, int>, std::make_pair( v1, v2 )
#include <cstring>	// memset,

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

/* Tableau de fonctions
	typedef 			void (Harl::*functions)();
	struct 				dispatch_entry
		{
			std::string		name;
			functions		function;
		};
		dispatch_entry	table[4];
		...
		Harl::table[0].name = "DEBUG";
		Harl::table[0].function = &Harl::debug;
		...
		(this->*table[i].function)();
*/

/*
	Class Fixed
	{	
		public;
			Fixed&		operator=( const Fixed& f );
			bool		operator>( const Fixed& f ) const;
			bool		operator<( const Fixed& f ) const;
			bool		operator>=( const Fixed& f ) const;
			bool		operator<=( const Fixed& f ) const;
			bool		operator==( const Fixed& f ) const;
			bool		operator!=( const Fixed& f ) const;
			Fixed		operator+( const Fixed& f );
			Fixed		operator-( const Fixed& f );
			Fixed		operator*( const Fixed& f );
			Fixed		operator/( const Fixed& f );
			Fixed&		operator++();
			Fixed&		operator--();
			Fixed		operator++(int); {fixed temp(*this); this->value++; return (temp);}
			Fixed		operator--(int); {fixed temp(*this); this->value--; return (temp);}
			int&		operator[](int i);
			const int& 	operator[](int i) const;
			Vect2		operator-() const {return Vect2(-x, -y);
    }

			static Fixed&		min(Fixed & a, Fixed & b);
			static const Fixed&	min(const Fixed & a, const Fixed & b);
			static Fixed&		max(Fixed & a, Fixed & b);
			static const Fixed&	max(const Fixed & a, const Fixed & b);
			/* Methodes static car depend d'aucun objet -> appelees par Fixed::min(a, b);
}
*/

void highFivesGuys(void)
{
	int	i = 0;

	std::cout 	<< "\033[36mClapTrap " << this->name << ", wich is a FragTrap, ";
	if (this->energy_points == 0)
		i = 2;
	if (this->hit_points == 0)
		i++;
	switch(i)
	{
		case 0:
			break ;
		case 1:
			std::cout 	<< "is unable to request High fives: no more Hit points"
						<< "\033[0m" << std::endl;
			return ;
		case 2:
			break ;
		case 3:
			std::cout 	<< "is unable to request High fives: no more Energy nor Hit points"
						<< "\033[0m" << std::endl;
			return ;
		default:
			break ;
	}
	std::cout 	<< "says: High five, guys! ✋!\033[0m"
				<< std::endl;
	return ;
}

/* Classes en diament

	class DiamondTrap : public ScavTrap, public FragTrap
	{
		public:	
			using			ScavTrap::attack;
	}
	...
	class FragTrap : virtual public ClapTrap
	...
	class ScavTrap : virtual public ClapTrap
	...
	class claptrap
*/

/* Polymorphisme par sous-typage

	class Dog : public Animal
	{
		public:	
			virtual	~Dog( void );
			
			virtual void	makeSound( void ) const;
			std::string		getName( void ) const;

		private:
			Brain*		brain;
	}
	...
	class Cat : public Animal
	{
		public:	
			virtual	~Cat( void );

			virtual void	makeSound( void ) const;
			std::string		getName( void ) const;
		
		private:
			Brain*		brain;
	}
	...
	class Animal
	{
		public:
			virtual			~Animal( void )

			virtual void	makesound () const;
			std::string		getType( void ) const;
	...
	class	Brain
	{
		public:
			virtual	~Brain( void );
	}
	

	const Dog* a = new Dog();
	b = *(dog*)a; // cast de a en dog* (Dog*)a (supprime const) puis dereference Dog&

	Objet.Mehode1().Methode2() 	peut exister si Methode1 renvoi un objet alors
								la Methode2 de l'objet renvoye sera executee
*/

/* Classe abstraite - une methode = 0

	class Dog : public AAnimal
	{
		public:	
			virtual	~Dog( void );
			
			virtual void	makeSound( void ) const;
			std::string		getName( void ) const;

		private:
			Brain*		brain;
	}
	...
	class Cat : public AAnimal
	{
		public:	
			virtual	~Cat( void );

			virtual void	makeSound( void ) const;
			std::string		getName( void ) const;
		
		private:
			Brain*		brain;
	}
	...
	class AAnimal
	{
		public:
			virtual			~AAnimal( void )

			virtual void	makesound () const = 0;
			std::string		getType( void ) const;
	...
	class	Brain
	{
		public:
			virtual	~Brain( void );
	}
*/

/* Interface ou abstraite pure - toute methode = 0

	class Character : public ICharacter
	{
		private:
			std::string	name;
			AMateria*	inv[4];
			AMateria*	ground[100];
		
		public:
							Character( void );
							Character( std::string const & name);
							Character( const Character& am );
			virtual 		~Character( void );
			Character & 	operator=( Character const & am );
		
			virtual std::string const &		getName() const;
			virtual void 					equip(AMateria* m);
			virtual void 					unequip(int idx);
			virtual void 					use(int idx, ICharacter& target);
			AMateria const *				getInv(int const idx) const;
			bool							checkInventory( void ) const;
	...
	class ICharacter
	{
		public:
			virtual ~ICharacter( void );
			virtual std::string const & getName( void ) const = 0;
			virtual void equip( AMateria* m ) = 0;
			virtual void unequip(int idx) = 0;
			virtual void use( int idx, ICharacter& target ) = 0;
	};
	std::ostream &	operator<<(std::ostream& os, const Character& am);
*/

/*Exceptions et try/catch

	class Bureaucrat
	{
		public:
	
		
		class GradeTooHighException: public std::exception
		{
			public:
				virtual const char* what() const throw();	
		};
	...
	const char* Bureaucrat::GradeTooHighException::what() const throw()
	{
		return ("The grade is to high (< 1)");
	}

	void	Bureaucrat::upGrade()
	{
		this->grade--;
		if (this->grade < 1)
			throw GradeTooHighException();
		else if (this->grade > 150)
			throw GradeTooLowException();
	}
	...
	{
		try
	   	{
			burct.upGrade();
			std::cout << burct << std::endl;
	   	}
	   	catch(const Bureaucrat::GradeTooHighException& e)
	   	{
	        	std::cerr << burct << ": upGrade error: " << e.what() << std::endl;
	   	}
		
*/

/*	casting

	static_cast<void>(var);
	reinterpret_cast<uintptr_t>(ptr);

	try
	{
		A& a = dynamic_cast<A&>(p);
		static_cast<void>(a);
		std::cout << "A says identify&" << std::endl;
		return ;
	}
	catch (const std::exception & e){}
		
*/

/***** templates 1 ******/

#ifndef WHATEVER_HPP
# define WHATEVER_HPP

template < typename T >
const T &	min( const T & a, const T & b )
{
	return (a < b ? a : b);
}
#endif

int main( void )
{
	int a = 2;
	int b = 3;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
}

/***** templates 2 ******/
#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>

template < typename T >
class Array
{
	private:
		T*				data;
		unsigned int	n;
	public:
		Array		( void );
		Array		( unsigned int n );
		Array		( const Array & other);
		~Array		( void );
		
		Array<T> &	operator=( const Array & other );
		T &			operator[]( const unsigned int idx );
		const T & 	operator[]( const unsigned int idx ) const;
		
		unsigned int 	size( void ) const;
};
# include "Array.tpp"
#endif
//fichier .tpp
template < typename T >
Array<T>::Array( void )
:	data(0),
	n(0)
{}

/***** templates 3 ******/
#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <stack>
#include <deque>
#include <iterator>

template <typename T>
class MutantStack: public std::stack<T>
{
	private:

	public:
						MutantStack ( void ){};
						MutantStack ( const MutantStack & other ): std::stack<T>(other.c){};
						~MutantStack ( void ){};
		MutantStack &	operator=( MutantStack other )
		{
			std::swap(this->c, other.c);
			return (*this);
		};

		typedef typename std::stack<T>::container_type::iterator					iterator;
		typedef typename std::stack<T>::container_type::const_iterator			const_iterator;
		typedef typename std::stack<T>::container_type::reverse_iterator			reverse_iterator;
		typedef typename std::stack<T>::container_type::const_reverse_iterator	const_reverse_iterator;

		iterator				begin( void ) { return (this->c.begin()); };
		iterator				end( void ) { return(this->c.end()); };
		const_iterator			begin( void ) const { return (this->c.cbegin()); };
		const_iterator			end( void ) const { return(this->c.cend()); };
		reverse_iterator		rbegin( void ) { return (this->c.rbegin()); };
		reverse_iterator		rend( void ) { return(this->c.rend()); };
		const_reverse_iterator	rbegin( void ) const { return (this->c.crbegin()); };
		const_reverse_iterator	rend( void ) const { return(this->c.crend()); };
};
#endif

/***** treatfile ******/

void	treat_file( std::ifstream & ifs, bool type, BitcoinExchange & btc )
{
	std::string	str = "";
	std::string	result = "";
	int			i = 0;
	while (std::getline( ifs, result ))
	{
		str = str + result;
		if (ifs.eof() && !ifs.fail())
			break ;
		else if (ifs.eof() && ifs.fail())
			break ;
		else if (ifs.fail())
			throw std::runtime_error("ERROR: Logical error : failed to read (FAIL) file ");
		else if (ifs.bad())
			std::cerr 	<< "ERROR: Stream fatal error (BAD) on file " << std::endl;
		str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
		if ( i == 0 )
		{
			i++;
			if (str != "date,exchange_rate" && str != "date|value")
				throw std::runtime_error("Error: wrong format header in file ");
		}
		else if (type == true)
			btc.line_integration( str );
		else
			btc.seek_line( str );
		str.clear();
	}
	if (i == 0 && ifs.eof() && ifs.fail())
		throw std::runtime_error("Error: empty file ");	
}

/*

struct tm

Member	Type	Meaning	Range
tm_sec	int	seconds after the minute	0-61*
tm_min	int	minutes after the hour	0-59
tm_hour	int	hours since midnight	0-23
tm_mday	int	day of the month	1-31
tm_mon	int	months since January	0-11
tm_year	int	years since 1900	
tm_wday	int	days since Sunday	0-6
tm_yday	int	days since January 1	0-365
tm_isdst	int	Daylight Saving Time flag	

double 	m_us = 1e6 * static_cast<double>(mstop - mstart) / CLOCKS_PER_SEC;

std::deque<int>::iterator pos = std::lower_bound(dM.begin() + lft_bound
								, dM.begin() + rgt_bound, dPairs[i].second);
	j = pos - dM.begin();
				dM.insert(pos, dPairs[i].second);

string conversion

atof	Convert string to double (function)
atoi	Convert string to integer (function)
atol	Convert string to long integer (function)
atoll	Convert string to long long integer (function)
strtod	Convert string to double (function)
strtof	Convert string to float (function)
strtol	Convert string to long integer (function)
strtold	Convert string to long double (function)
strtoll	Convert string to long long integer (function)
strtoul	Convert string to unsigned long integer (function)
strtoull	Convert string to unsigned long long integer (function)

*/