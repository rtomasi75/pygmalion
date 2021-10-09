#include <pygmalion-tictactoe-dynamics.h>

using namespace pygmalion;
using namespace pygmalion::dynamics;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	engine<pygmalion::tictactoe::generator> eng(std::cin, std::cout);
	eng.run();
	return 0;
}