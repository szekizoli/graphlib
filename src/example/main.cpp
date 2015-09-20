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
	auto node_a = gb.addNode(L"A", FunctionInput::NAME, 1);
	auto node_b = gb.addNode(L"B", FunctionInput::NAME, 3);
	auto node_c = gb.addNode(L"C", FunctionInput::NAME, 2);
	auto node_m4 = gb.addNode(L"(-4)", FunctionConstant::NAME, -4);
	auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
	auto node_X1 = (-node_b + sqrt(node_b * node_b + node_m4 * node_a * node_c)) / (node_2 * node_a);
	auto node_X2 = (-node_b - sqrt(node_b * node_b + node_m4 * node_a * node_c)) / (node_2 * node_a);

	Graph g = gb.build();

	const auto order = topologicalSort<Graph, Node>(g);
	auto r = execute(order.begin(), order.end());
	//auto r = stack_execute(order.begin(), order.end());
	for (size_t i = 0; i < g.order(); ++i) {
		std::wcout << g[i].label() << L": " << r[i] << std::endl;
	}

	char c;
	std::cin.get(c);
	return 0;
}