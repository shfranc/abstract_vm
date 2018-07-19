#include "Avm.hpp"

Avm::Avm( void ) : _reader( new Reader() ) {
	
	return;
}

Avm::Avm( std::string filename ) : _reader( new Reader(filename) ) {

	return;
}

Avm::~Avm( void ) {

	delete _reader;
	return;
}

void		Avm::readUserInput() {

	try {
		_reader->read();
	}
	catch ( std::invalid_argument e) { // create custom exceptions
		std::cout << e.what() << std::endl;		
	}
}	

void		Avm::parseInstructions() {

	try {
		_parser = new Parser( _reader->getContent() );
		_parser->parse();
		std::cout << *_parser;
	}
	catch ( std::invalid_argument e) { // create custom exceptions
		std::cout << e.what() << std::endl;		
	}
}
