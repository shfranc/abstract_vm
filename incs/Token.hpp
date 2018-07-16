#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <iostream>

enum tokenType
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
	SEP,
	VALUE
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


private:
	std::string		_str;
	int				_type;

	int				tokenType( void );

};

#endif