#ifndef TOKEN_HPP
# define TOKEN_HPP

enum token
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
	EXIT
};

class Token {

public:

	Token( void );
	Token( std::string str );
	Token( Token const & src );
	~Token( void );

	Token & operator=( Token const & rhs );


private:
	std::string		_str;
	int				_type;

};

#endif