#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"
#include "Int8.hpp"
#include <stack>

class Avm {

public:

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		readUserInput();	
	void		parseInstructions();
	void		compute();

private:
	Reader *						_reader;
	Parser *						_parser;
	std::stack<IOperand*>			_stack;
	std::vector<Token> *			_instructions;


	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );
	
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;	

};

#endif