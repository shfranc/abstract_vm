#ifndef LEXER_HPP
# define LEXER_HPP

# include <iostream>

class Lexer {

public:

	Lexer( void );
	Lexer( std::string input );
	~Lexer( void );

	std::string		getNextToken( void );	

private:
	size_t			_pos;
	size_t			_line;
	std::string		_input;

	Lexer( Lexer const & src );
	Lexer & operator=( Lexer const & rhs );
};

#endif