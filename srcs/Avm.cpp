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
	
	for (size_t i = 0; i < _instructions->size(); i++)
	{
		std::cout << (*_instructions)[i].getStr() << std::endl;
		if ( (*_instructions)[i].getType() == INSTR )
		{
			std::cout << "execute action" << std::endl;
		}
		else
		{

		}
	}
	
	// test = createOperand(INT8, "42");
	// std::cout << test->toString() << std::endl;
}

// IOperand const *	Avm::createOperand( eOperandType type, std::string const & value ) const {

// 	return (this->*_factory[type])( value );
// }

// IOperand const *	Avm::createOperand( eOperandType type, std::string const & value ) const {
// 	IOperand const *	operand;

// 	switch (type) {
// 		case INT8 :
// 			std::cout << "creating INT8" << std::endl;
// 			operand = new Int8(type, value);
// 			break;
// 		case INT16 :
// 			std::cout << "creating INT16" << std::endl;
// 			operand = new Int8(type, value);
// 			break;
// 		case INT32 :
// 			std::cout << "creating INT32" << std::endl;
// 			operand = new Int8(type, value);
// 			break;
// 		case FLOAT :
// 			std::cout << "creating FLOAT" << std::endl;
// 			operand = new Int8(type, value);
// 			break;
// 		case DOUBLE :
// 			std::cout << "creating DOUBLE" << std::endl;
// 			operand = new Int8(type, value);
// 			break;
// 		default :
// 			operand = nullptr;
// 			break;								
// 	}
// 	return operand;
// }
