#include "Avm.hpp"

void	ft_usage( void )
{
	std::cerr << "./avm [input_file]" << std::endl;
}

int main( int argc, char const *argv[] )
{
	Avm		*avm;

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

	delete avm;
	return 0;
}
