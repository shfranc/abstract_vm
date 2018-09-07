#include "Avm.hpp"

void	ft_usage( void )
{
	std::cerr << "./avm [--parser] [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	Avm *				avm;
	bool 				display =  false;

	if ( argc == 1 )
		avm = new Avm();
	else if ( argc == 2 )
		avm = new Avm(argv[1]);
	else if ( argc == 3 && (std::string(argv[1]) == PARSER_OPT) ) {
		avm = new Avm(argv[2]);
		display = true;
	}
	else {
		ft_usage();
		return 1;
	}

	try {
		avm->readUserInput();
		avm->parseInstructions();
		if ( display )
			std::cout << *(avm-> getParser()) << std::endl;
		avm->compute();
	} catch ( std::invalid_argument const & e) {
		std::cerr << e.what() << std::endl;
	} catch ( std::exception const & e) {
		std::cerr << e.what() << std::endl;
	}	

	delete avm;
	return 0;
}
