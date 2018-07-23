#ifndef AVM_HPP
# define AVM_HPP

#include "Reader.hpp"
#include "Parser.hpp"
#include "Factory.hpp"
#include "IOperand.hpp"
#include <stack>

class Avm {

public:
	Factory							_factory;

	Avm( void );
	Avm( std::string filename );
	~Avm( void );

	void		readUserInput();	
	void		parseInstructions();
	void		compute();

private:
	Reader *						_reader;
	Parser *						_parser;
	std::stack<IOperand const *>	_stack;
	std::vector<Token> *			_instructions;

	Avm( Avm const & src );
	Avm & operator=( Avm const & rhs );

	void	push( Token const & );
	void	pop( Token const & );
	void	dump( void ) const;
	void	assert( Token const & );

	bool	compareOperand(IOperand const * O1, IOperand const * O2) const;
};

#endif