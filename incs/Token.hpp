#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <regex>

enum tokenType
{
	INVALID,
	INSTR,
	VALUE,
	SEP,
	END_INSTR
};

enum tokenInstr
{
	NONE = 0,
	PUSH = 6,
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
	V_INT = 17,
	V_FLOAT,
	V_DOUBLE
};

class Token {

public:

	Token( void );
	Token( std::string str );
	Token( Token const & src );
	~Token( void );

	Token & 			operator=( Token const & rhs );
	std::string			getStr( void ) const;
	int					getInstr( void ) const;
	int					getValue( void ) const;
	int					getType( void ) const;

private:
	std::string			_str;
	int					_instr;
	int					_value;
	int					_type;

	int					checkInstr( void );
	int					checkValue( void );
	int					checkType( void );

};

#endif