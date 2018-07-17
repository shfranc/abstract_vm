#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>
#include <regex>

enum tokenType
{
	INVALID,
	INSTR,
	SEP,
	VALUE
};

enum tokenInstr
{
	NONE,
	PUSH,
	POP,
	DUMP,
	ASSERT,
	ADD,
	SUB,
	MUL,
	DIV,
	MOD,
	PRINT,
	EXIT,
};

enum tokenValue
{
	V_INT,
	V_FLOAT,
	V_DOUBLE
};

class Token {

public:

	Token( void );
	Token( std::string str );
	Token( Token const & src );
	~Token( void );

	Token & operator=( Token const & rhs );
	std::string		getStr( void ) const;
	int				getType( void ) const;
	int				getInstr( void ) const;
	int				getValue( void ) const;


private:
	std::string		_str;
	int				_type;
	int				_instr;
	int				_value;

	int				checkType( void );
	int				checkInstr( void );
	int				checkValue( void );

};

#endif