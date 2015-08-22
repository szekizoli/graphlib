#include <iostream>

#include "graph/Algorithms.h"
#include "executor/Executor.h"
#include "../core/graph/function/Function.h"
#include "../core/graph/function/FunctionBuilder.h"
#include "../core/graph/Node.h"
#include "../core/graph/Graph.h"
#include "../core/graph/GraphBuilder.h"

using namespace graphlib::executor;
using namespace graphlib::graph;
using namespace graphlib::graph::algorithms;
using namespace graphlib::graph::function;

int main() {
	GraphBuilder gb{};
	auto node_b = gb.addNode(L"B", FunctionInput::NAME, 3);
	auto node_b2 = gb.addNode(L"B*B", FunctionMultiply::NAME);
	auto node_a = gb.addNode(L"A", FunctionInput::NAME, 1);
	auto node_c = gb.addNode(L"C", FunctionInput::NAME, 2);
	auto node_m4 = gb.addNode(L"-4", FunctionConstant::NAME, -4);
	auto node_m4ac = gb.addNode(L"-4AC", FunctionMultiply::NAME);
	auto node_b2m4ac = gb.addNode(L"B*B-4AC", FunctionAdd::NAME);

	gb.addEdge(node_b, node_b2);
	gb.addEdge(node_b, node_b2);

	gb.addEdge(node_a, node_m4ac);
	gb.addEdge(node_c, node_m4ac);
	gb.addEdge(node_m4, node_m4ac);

	gb.addEdge(node_b2, node_b2m4ac);
	gb.addEdge(node_m4ac, node_b2m4ac);

	Graph g = gb.build();

	const auto order = topologicalSort<Graph, Node>(g);
	auto r = stack_execute(order.begin(), order.end());
	for (size_t i = 0; i < g.order(); ++i) {
		std::wcout << g[i].label() << L": " << r[i] << std::endl;
	}

	return 0;
}