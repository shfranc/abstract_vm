#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>
# include "Token.hpp"

# define	SEPARATOR "\n"

enum tokenType
{
	SEP,
	INSTRUCT,
	OPERAND
};

class Lexer {

public:

	Lexer( void );
	Lexer( std::string input );
	~Lexer( void );

	Token			getNextToken( void );	

private:
	size_t			_pos;
	size_t			_line;
	std::string		_input;

	bool			isWhitespaces( char c );
	bool			isNewline( char c );
	bool			isComment( char c );
	void			skipWhitespaces( void );
	void			skipNewline( void );
	void			skipComment( void );
	Token			createToken( void );


	Lexer( Lexer const & src );
	Lexer & operator=( Lexer const & rhs );
};

#endif