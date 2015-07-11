#include "graph\function\Function.h"
#include "graph\function\FunctionBuilder.h"
#include "graph\Node.h"
#include "graph\Graph.h"

using namespace graphlib::graph;
using namespace graphlib::graph::function;

int main() {
	vector<Node> nodes;
	nodes.emplace_back(Node{});
	Graph g(std::move(nodes));
	return 0;
}