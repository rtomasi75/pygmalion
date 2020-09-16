#include <pygmalion-state.h>
#include "board.h"

using namespace pygmalion;
using namespace pygmalion::state;

int main(int argc, char* argv[])
{
	engine<test::board> eng(std::cin, std::cout);
	eng.run();
	return 0;
}