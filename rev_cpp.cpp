#include <iostream> // std::cin, cout, cerr, clog
#include <string>	// std::string, .empty(), .c_str(), .size(), .clear(), .append, .replace, .substr, .swap
#include <cctype>	// toupper(char)..., tolower, isspace, isalnum, isalpha, iscntrl, isgraph, islower
#include <ctime>	// var clock_t, var size_t, var time_t, struct tm*, clock(), mktime, difftime, time(0), ctime
#include <iomanip>	// std::setfill, setw, setbase, setiosflags, resetiosflag
#include <fstream>	// std::ifstream, ofstream, .open, .close(), .eof(), .fail(), .bad()
#include <climits>	// INT_MIN, INT_MAX, CHAR_BIT, LONG_MIN, LONG_MAX ... 
#include <climits> 	// FLT_MIN, FLT_MAX, DBL_MIN, DBL_MAX, LDBL_MIN, LDBL_MAX
#include <cmath>	// exp, log, cos, acos, sin, asin, sqrt, pow, round, floor, ceil, fabs

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
		Fixed		operator-() const; {return (this->value * -1);}
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
		virtual 			~Character( void );
		Character & 		operator=( Character const & am );
		
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


/**************** static a verifier pour cpp02 ex02 ****************/
/**************** dog b = *(dog*)j avec const aninal* j = new dog();****************/
/**************** b.gotAnIdea direct ?****************/

