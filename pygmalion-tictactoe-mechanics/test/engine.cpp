#include <pygmalion-tictactoe-mechanics.h>

using namespace pygmalion;
using namespace pygmalion::mechanics;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	engine<pygmalion::tictactoe::motor> eng(std::cin, std::cout);
	eng.run();
	return 0;
}