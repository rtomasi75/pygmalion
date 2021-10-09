#include <pygmalion-tictactoe-state.h>

using namespace pygmalion;
using namespace pygmalion::state;
using namespace pygmalion::tictactoe;

int main(int argc, char* argv[])
{
	engine<pygmalion::tictactoe::board> eng(std::cin, std::cout);
	eng.run();
	return 0;
}