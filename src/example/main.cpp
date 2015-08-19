#include <iostream>

#include "graph/Algorithms.h"
#include "../core/graph/function/Function.h"
#include "../core/graph/function/FunctionBuilder.h"
#include "../core/graph/Node.h"
#include "../core/graph/Graph.h"
#include "../core/graph/GraphBuilder.h"


using namespace graphlib::graph;
using namespace graphlib::graph::algorithms;
using namespace graphlib::graph::function;

int main() {
	GraphBuilder gb;
	// B^2 - 4AC 
	// FInput A, B, C - How can I add values into A, B, C? As parameters
	auto node_a    = gb.addNode(L"A",      FunctionInput::NAME, 1);
	auto node_b    = gb.addNode(L"B",      FunctionInput::NAME, 3);
	auto node_c    = gb.addNode(L"C",      FunctionInput::NAME, 2);
	auto node_b2   = gb.addNode(L"B*B",    FunctionMultiply::NAME);
	auto node_4    = gb.addNode(L"4",      FunctionConstant::NAME, 4);
	auto node_4ac  = gb.addNode(L"4AC",    FunctionMultiply::NAME);
	auto node__4ac = gb.addNode(L"-4AC",   FunctionOpposite::NAME);
	auto node_res  = gb.addNode(L"Result", FunctionAdd::NAME);

	gb.addEdge(node_b, node_b2);
	gb.addEdge(node_b, node_b2);
	gb.addEdge(node_a, node_4ac);
	gb.addEdge(node_c, node_4ac);
	gb.addEdge(node_4, node_4ac);
	gb.addEdge(node_4ac, node__4ac);
	gb.addEdge(node_b2, node_res);
	gb.addEdge(node__4ac, node_res);

	Graph g = gb.build();

	auto re2 = topologicalSort<Graph, Node>(g);
	for (const auto node : re2) {
		std::wcout << node->label() << std::endl;
	}
	return 0;
}