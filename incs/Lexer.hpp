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

	bool			isWhitespaces( char c );
	bool			isNewline( char c );
	bool			isComment( char c );
	void			skipWhitespaces( void );
	void			skipNewline( void );
	void			skipComment( void );
	std::string		createToken( void );


	Lexer( Lexer const & src );
	Lexer & operator=( Lexer const & rhs );
};

#endif