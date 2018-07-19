#include "Parser.hpp"

Parser::Parser( std::string input ) : _lexer( new Lexer(input) ) {
	
	return;
}

Parser::~Parser( void ) {

	delete _lexer;
	return;
}

void	Parser::parse( void ) {

	Token			*prevToken;
	Token			*token;
	size_t			line;

	while ( (token = _lexer->getNextToken()) != nullptr ) {

		if ( token->getType() == INVALID ) {
			std::cerr << "Line " << _lexer->getLine() << ": Parsing error: `" << token->getStr() << "' is an invalid token" << std::endl;
			// exit(1);
		}
		else if ( token->getType() == INSTR ) {

			if ( token->getInstr() == PUSH || token->getInstr() == ASSERT ) {
				
				line = _lexer->getLine();
				prevToken = token;				
				token = _lexer->getNextToken();
				
				if ( token->getType() == VALUE ) {
					_instructions.push_back(*prevToken);
					_instructions.push_back(*token);

				}
				else {
					std::cerr << "Line " << line << ": Parsing error: " << "expecting VALUE after `" << prevToken->getStr() << "'." << std::endl;
					// exit(1);
				}
			}
			else {
				
				line = _lexer->getLine();
				prevToken = token;
				token = _lexer->getNextToken();
				
				if ( token == nullptr || token->getType() == SEP ) {
					_instructions.push_back(*prevToken);
				}
				else {
					std::cerr << "Line " << line << ": Parsing error: " << "expecting <newline> after `" << prevToken->getStr() << "'." << std::endl;
					// exit(1);
				}
			}
			delete prevToken;
		}
		delete token;
	}
}

// ACCESSOR
std::vector<Token> const &	Parser::getInstructions( void ) const { return _instructions; }


// OPERATOR <<

std::ostream &		operator<<( std::ostream & o, Parser const & src ) {
	std::vector<Token> const &	v = src.getInstructions();
	size_t	len = v.size();

	std::cout << "--------------------" << std::endl;
	o << std::setw(20) << "STR"
		<< std::setw(8) << "TYPE"
		<< std::setw(8) << "INSTR"
		<< std::setw(8) << "VALUE"
		<< std::endl;

	for (size_t i = 0; i < len; i++)
	{
		o << std::setw(20) << v[i].getStr()
			<< std::setw(8) << v[i].getType()
			<< std::setw(8) << v[i].getInstr()
			<< std::setw(8) << v[i].getValue()
			<< std::endl;
	}
	std::cout << "--------------------" << std::endl;


	return o;
}