#include <pygmalion-chess-state.h>

using namespace pygmalion;
using namespace pygmalion::state;
using namespace pygmalion::chess;

int main(int argc, char* argv[])
{
	engine<pygmalion::chess::board> eng(std::cin, std::cout);
	eng.run();
	return 0;
}