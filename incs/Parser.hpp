#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"
# include <vector>
// # include <iostream>
# include <iomanip>
# include <sstream>

# define LINE_BEGIN			"' all lines must begin with an instruction."
# define INVALID_TOKEN		"' is not a valid token."
# define OPERAND_EXPECTED	"' is not followed by an OPERAND."
# define NEWLINE_EXPECTED	"' is not followed by a <newline>."

class Parser {

public:

	Parser( std::string input );
	~Parser( void );

	void						parse( void );

	// ACCESSOR
	std::vector<Token> *		getInstructions( void ) const;
	std::stringstream const &	getError( void ) const;
	
	// EXCEPTIONS
	class ParsingException : public std::exception {
	
	public:

		ParsingException( ParsingException const & src );
		ParsingException( std::string line, std::string error );
		virtual ~ParsingException( void ) throw();
		
		ParsingException &	operator=( ParsingException const & rhs );
		
		virtual const char *	what() const throw();

	private:
		std::string			_error;

		ParsingException( void );
	};

private:
	Lexer *						_lexer;
	std::vector<Token> *		_instructions;
	std::stringstream			_error;
	
	Parser( void );
	Parser( Parser const & src );	
	Parser & 	operator=( Parser const & rhs );

	void		analyseToken( Token * token );
	void		analyseInstruction( Token * token );
	void		analyseOperand( Token * token );
	Token *		skipLine( Token * token );

};

std::ostream &		operator<<( std::ostream & o, Parser const & src );

#endif