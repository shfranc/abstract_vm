#include "Parser.hpp"

Parser::Parser( void ) {
	
	return;
}

Parser::~Parser( void ) {

	return;
}

void	Parser::parse( std::string input ) {

	Lexer			lexer(input);
	Token			*token;
	size_t			line;

	while ( (token = lexer.getNextToken()) != nullptr ) {

		if ( token->getType() == INVALID ) {
			std::cerr << "Line " << lexer.getLine() << ": Parser error: " << token->getStr() << " invalid token." << std::endl;
			exit(1);
		}
		else if ( token->getType() == INSTR ) {

			if ( token->getType() == PUSH || token->getType() == ASSERT ) {
				_instructions.push_back(*token);
				line = lexer.getLine();
				token = lexer.getNextToken();
				
				if ( token->getType() != VALUE ) {
					std::cerr << "Line " << line << ": Parser error: " << "a value was expected." << std::endl;
					exit(1);
				}
				else
					_instructions.push_back(*token);

			}
			else
				_instructions.push_back(*token);
		}

		std::cout << "je delete: ";
		delete token;
	}
}

// PRIVATE

// ACCESSOR
std::vector<Token> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<Token> const &	v = src.getInstructions();
	size_t	len = v.size();

	for (size_t i = 0; i < len; i++)
	{
		o << v[i].getStr() << "\t" << v[i].getType() << std::endl;
	}

	return o;
}