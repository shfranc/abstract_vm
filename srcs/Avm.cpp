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

	if ( _reader->getContent() == "" )
		return;

	// try {
		_parser = new Parser( _reader->getContent() );
		_parser->parse();
		std::cout << *_parser;
		_instructions = _parser->getInstructions();
	// }
	// catch ( Parser::ParsingException e ) {
		// std::cout << e.what() << std::endl;
	// }
}

void				Avm::compute() {

	if ( !_instructions )
		return;

	for (size_t i = 0; i < _instructions->size(); i++)
	{
		switch ( (*_instructions)[i].getInstr() ) {
			case PUSH :
				push((*_instructions)[++i]);
				break;
			case POP :
				pop((*_instructions)[i]);
				break;
			case DUMP :
				dump();
				break;
			case ASSERT :
				assert((*_instructions)[++i]);
				break;
			case ADD :
				break;
			case SUB :
				break;
			case MUL :
				break;
			case DIV :
				break;
			case MOD :
				break;
			case PRINT :
				break;
			case EXIT :
				break;
			case NO_INSTR :
				break;										
		}
	}
}

void				Avm::push( Token const & token ) {
	
	std::cout << "** push" << std::endl;
	_stack.push( _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) ) );
	return;
}

void				Avm::pop( Token const & token ) {
	
	std::cout << "** pop" << std::endl;
	if ( _stack.size() )
		_stack.pop();
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}
	return;
}

void				Avm::dump( void ) const {

	std::cout << "** dump" << std::endl;
	for (std::stack<IOperand const *> dump = _stack; !dump.empty(); dump.pop())
	 	std::cout << dump.top()->toString() << std::endl;
}

void				Avm::assert( Token const & token ) {
	IOperand const *	reference = _factory.createOperand( token.getOperandType(), captureNumericValue(token.getStr()) );
	IOperand const *	temp;

	std::cout << "** assert" << std::endl;

	if ( _stack.size() ) {

		temp = _stack.top();
		if ( compareOperand(temp, reference) == false ) {
			std::cerr << "Line " << token.getLine() << ": Exec error: `" << temp->toString() << "' is not equal to `" << reference->toString() << "'." << std::endl;
		// exit(1);			
		}
	}
	else {
		std::cerr << "Line " << token.getLine() << ": Exec error: `" << token.getStr() << "' on an empty stack." << std::endl;
		// exit(1);
	}
	delete reference;
	return;
}

std::string 	Avm::captureNumericValue( std::string str ) const {

	std::smatch m;
	std::regex e("\\((.+)\\)");

	std::regex_search( str, m, e );
	return (m[1]);
}

bool			Avm::compareOperand(IOperand const * O1, IOperand const * O2) const {

	if ( O1->getType() == O2->getType() )
	{
		if ( std::strcmp( O1->toString().c_str(), O2->toString().c_str() ) == 0 )
			return (true);
	}
	return (false);
}
