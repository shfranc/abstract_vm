#ifndef PARSER_HPP
# define PARSER_HPP

# include "Lexer.hpp"
# include <vector>
# include <iostream>
# include <iomanip>

# define LINE_BEGIN			"' intline must begin with an instruction."
# define INVALID_TOKEN		"' is an invalid token."
# define OPERAND_EXPECTED	"' is not followed by an OPERAND."
# define NEWLINE_EXPECTED	"' is not followed by a <newline>."

class Parser {

public:

	Parser( std::string input );
	~Parser( void );

	void						parse( void );

	// ACCESSOR
	std::vector<Token> *		getInstructions( void ) const;

	// EXCEPTIONS
	class ParsingException : public std::exception {
	
	public:

		ParsingException( std::string line, std::string error );
		ParsingException( ParsingException const & src );
		virtual ~ParsingException( void ) throw();
		
		ParsingException &	operator=( ParsingException const & rhs );
		virtual const char *	what() const throw();

	private:
		std::string			_line;
		std::string			_error;

		ParsingException( void );
	};

private:
	Lexer *						_lexer;
	std::vector<Token> *		_instructions;
	
	Parser( void );
	Parser( Parser const & src );	
	Parser & operator=( Parser const & rhs );

};

std::ostream &		operator<<( std::ostream & o, Parser const & src );

#endif