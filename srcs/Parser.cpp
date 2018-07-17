#include "Parser.hpp"

Parser::Parser( void ) {
	
	return;
}

Parser::~Parser( void ) {

	return;
}

void	Parser::parse( std::string input ) {

	Lexer			lexer(input);
	Token			*prevToken;
	Token			*token;
	size_t			line;

	while ( (token = lexer.getNextToken()) != nullptr ) {

		if ( token->getType() == INVALID ) {
			std::cerr << "Line " << lexer.getLine() << ": Parsing error: `" << token->getStr() << "' is an invalid token" << std::endl;
			// exit(1);
		}
		else if ( token->getType() == INSTR ) {

			if ( token->getInstr() == PUSH || token->getInstr() == ASSERT ) {
				std::cout << "check push or assert" << std::endl;
				
				line = lexer.getLine();
				prevToken = token;				
				token = lexer.getNextToken();
				
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
				
				line = lexer.getLine();
				prevToken = token;
				token = lexer.getNextToken();
				
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

	std::cout << "--------------" << std::endl;

	for (size_t i = 0; i < len; i++)
	{
		o << v[i].getStr() << "\t" << v[i].getType() << std::endl;
	}
	std::cout << "--------------" << std::endl;


	return o;
}