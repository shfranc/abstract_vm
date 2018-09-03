#include "Parser.hpp"

Parser::Parser( std::string input ) : _lexer( new Lexer(input) ), _instructions( new std::vector<Token>() ) {
	
	return;
}

Parser::~Parser( void ) {

	delete _lexer;
	delete _instructions;
	return;
}

void						Parser::parse( void ) {

	Token			*token;

	while ( (token = _lexer->getNextToken()) != nullptr ) {

		try {
			analyseToken(token);
		} catch (ParsingException const & e) {
			_error << e.what() << std::endl;
		}
	}
}

void						Parser::analyseToken( Token * token ) {

	if ( token->getType() == INVALID ) {
		std::string message = token->getStr() + INVALID_TOKEN;
		token = skipLine( token );
		delete token;
		throw ParsingException( std::to_string(_lexer->getLine()), message );
	}
	else if ( token->getType() == INSTR ) {
		analyseInstruction(token);
	}
	else if ( token->getType() == OPERAND ) {
		std::string message = token->getStr() + LINE_BEGIN;
		delete token;
		throw ParsingException( std::to_string(_lexer->getLine()), message );
	}
	else
		delete token;
}


void						Parser::analyseInstruction( Token * token ) {

	Token			*prevToken;
	size_t			line;

	if ( token->getInstr() == PUSH || token->getInstr() == ASSERT ) {
		analyseOperand( token );
	}
	else {
		
		line = _lexer->getLine();
		prevToken = token;
		token = _lexer->getNextToken();
		
		if ( token == nullptr || token->getType() == SEP ) {
			_instructions->push_back( *prevToken );
			delete prevToken;
			delete token;
		}
		else {
			std::string message = prevToken->getStr() + NEWLINE_EXPECTED;
			token = skipLine( token );
			delete prevToken;
			delete token;
			throw ParsingException( std::to_string(line), message );
		}
	}

}

// When an error is detected, the line is skipped.
Token *					Parser::skipLine( Token * token ) {

	while ( token != nullptr && token->getType() != SEP ) {
		delete token;
		token = _lexer->getNextToken();
	}
	return ( token );
}

void						Parser::analyseOperand( Token * token ) {

	Token			*prevToken;
	size_t			line;

	line = _lexer->getLine();
	prevToken = token;				
	token = _lexer->getNextToken();
	
	if ( token->getType() == OPERAND ) {
		_instructions->push_back(*prevToken);
		_instructions->push_back(*token);
		delete prevToken;
		delete token;
	}
	else {
		std::string message = token->getStr() + OPERAND_EXPECTED;
		delete prevToken;
		delete token;		
		throw ParsingException( std::to_string(line), message );
	}
}

// ACCESSOR
std::vector<Token> *		Parser::getInstructions( void ) const { return _instructions; }
std::stringstream const &	Parser::getError( void ) const { return _error; }

// OPERATOR <<

std::ostream &				operator<<( std::ostream & o, Parser const & src ) {
	std::vector<Token> *	v = src.getInstructions();
	size_t	len = v->size();

	std::cout << "--------------------" << std::endl;
	o << std::setw(20) << "STR"
		<< std::setw(8) << "LINE"
		<< std::setw(8) << "TYPE"
		<< std::setw(8) << "INSTR"
		<< std::setw(8) << "VALUE"
		<< std::endl;

	for (size_t i = 0; i < len; i++)
	{
		o << std::setw(20) << (*v)[i].getStr()
			<< std::setw(8) << (*v)[i].getLine()
			<< std::setw(8) << (*v)[i].getType()
			<< std::setw(8) << (*v)[i].getInstr()
			<< std::setw(8) << (*v)[i].getOperandType()
			<< std::endl;
	}
	std::cout << "--------------------" << std::endl;

	return o;
}
