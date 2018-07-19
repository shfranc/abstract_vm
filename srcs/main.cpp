#include "Avm.hpp"

void	ft_usage( void )
{
	std::cerr << "./avm [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	Avm *				avm;
	IOperand const *	test;

	if (argc == 1)
		avm = new Avm();
	else if (argc == 2)
		avm = new Avm(argv[1]);
	else {
		ft_usage();
		return 1;
	}

	avm->readUserInput();
	avm->parseInstructions();
	
	test = avm->createOperand(INT8, "42");
	std::cout << test->toString() << std::endl;

	delete avm;
	return 0;
}
