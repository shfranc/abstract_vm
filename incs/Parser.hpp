#ifndef PARSER_HPP
# define PARSER_HPP

# include <vector>
# include "Lexer.hpp"


class Parser {

public:

	Parser( void );
	~Parser( void );

	void						parse( std::string input );

	std::vector<Token> const &	getInstructions( void ) const;

private:

	std::vector<Token>		_instructions;

	Parser( Parser const & src );	
	Parser & operator=( Parser const & rhs );

};

std::ostream &		operator<<( std::ostream & o, Parser const & src );

#endif