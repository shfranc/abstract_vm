#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"
# include <vector>
# include <iostream>

class Parser {

public:

	Parser( std::string input );
	~Parser( void );

	void						parse( void );

	std::vector<Token> const &	getInstructions( void ) const;

private:
	Lexer					*_lexer;
	std::vector<Token>		_instructions;
	
	Parser( void );
	Parser( Parser const & src );	
	Parser & operator=( Parser const & rhs );

};

std::ostream &		operator<<( std::ostream & o, Parser const & src );

#endif