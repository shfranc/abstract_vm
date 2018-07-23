#include "Avm.hpp"

Avm::Avm( void ) : _reader( new Reader() ) {
	
	return;
}

Avm::Avm( std::string filename ) : _reader( new Reader(filename) ) {

	return;
}

Avm::~Avm( void ) {

	delete _reader;
	delete _parser;
	return;
}

void				Avm::readUserInput() {

	try {
		_reader->read();
	}
	catch ( std::invalid_argument e) { // create custom exceptions
		std::cout << e.what() << std::endl;		
	}
}	

void				Avm::parseInstructions() {

	try {
		_parser = new Parser( _reader->getContent() );
		_parser->parse();
		std::cout << *_parser;
		_instructions = _parser->getInstructions();
	}
	catch ( std::invalid_argument e) { // create custom exceptions
		std::cout << e.what() << std::endl;		
	}
}

void				Avm::compute() {

	// IOperand const *	test;

	for (size_t i = 0; i < _instructions->size(); i++)
	{
		if ( (*_instructions)[i].getInstr() == PUSH )
		{
			push((*_instructions)[i + 1]);
			dump();
		}
	}
	
	// test = _factory.createOperand(INT8, "42");
	// std::cout << test->toString() << std::endl;
}

void				Avm::push( Token const & token ) {
	
	std::smatch m;
	std::regex e("\\((.+)\\)");

	std::cout << "** push" << std::endl;
	std::regex_search( token.getStr(), m, e );
	_stack.push( _factory.createOperand( token.getOperandType(), m[1] ) );
	return;
}

void				Avm::dump( void ) const {

	std::cout << "** dump" << std::endl;
	for (std::stack<IOperand const *> dump = _stack; !dump.empty(); dump.pop())
	 	std::cout << dump.top()->toString() << std::endl;
}
