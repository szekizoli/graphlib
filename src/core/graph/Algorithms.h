#ifndef GRAPHLIB_GRAPH_ALGORITHMS
#define GRAPHLIB_GRAPH_ALGORITHMS

#include <algorithm>
#include <stack>
#include <vector>

#include "graph/Graph.h"
#include "graph/Node.h"

namespace graphlib { namespace graph { namespace algorithms {

	using std::stack;
	using std::vector;

	///
	/// Splits the nodes of the graph into levels.
	///
	/// Nodes on the same level cannot be connected with an edge.
	/// Each node is as close to the output nodes as possible. 
	///
	/// @param graph The input graph.
	/// @return vector of vectors containing the nodes.
	//template <class GraphType, class NodeType>
	//void constructLayeredOrder(const GraphType &graph, vector<vector<NodeType>>& result);

	///
	/// Splits the nodes of the graph into levels.
	///
	/// Nodes on the same level cannot be connected with an edge.
	/// Each node is as close to the input nodes as possible. 
	///
	/// @param graph The input graph.
	/// @return vector of vectors containing the nodes.
	//template <class GraphType, class NodeType>
	//vector<vector<NodeType*>> partialTopologicalSortFromBottom(const GraphType &graph);

	// Creates a vector with the number of dependencies of each node
	template <typename GraphType, typename NodeType>
	vector<size_t> predecessorCount(const GraphType& graph) {
		vector<size_t> count(graph.order());
		const auto& nodes = graph.nodes();
		std::transform(begin(nodes), end(nodes), begin(count), [](const NodeType& n) { return n.predecessorSize(); });
		return std::move(count);
	}

	template <typename GraphType, typename NodeType, typename Func>
	vector<size_t> count(const GraphType& graph, Func func) {
		vector<size_t> count(graph.order());
		const auto& nodes = graph.nodes();
		std::transform(begin(nodes), end(nodes), begin(count), func);
		return std::move(count);
	}

	template <typename GraphType, typename NodeType>
	std::vector<const NodeType*> stackSort(const GraphType &graph) {
		stack<const NodeType*> toOrder;
		vector<const NodeType*> order;
		vector<size_t> succ_count = count<GraphType, NodeType>(graph, [](const NodeType& n) {return n.successorSize(); });
		vector<bool> added(graph.order(), false);
		vector<bool> preds_listed(graph.order(), false);

		const auto outputs = graph.find_output_nodes();
		for (const auto& n : outputs) {
			std::wcout << n->label() << std::endl;
			if (n->predecessorSize() == 0) {
				order.push_back(n);
				added[n->id()] = true;
			} else {
				toOrder.push(n);
			}
		}

		while (!toOrder.empty()) {
			const NodeType* node = toOrder.top();
			auto id = node->id();
			// 1) it may be added
			if (added[id]) {
				std::wcout << L"1: " << node->label() << std::endl;
				toOrder.pop();
				continue;
			}
			// 2) its predecessors are listed
			if (preds_listed[id]) {
				std::wcout << L"2: " << node->label() << std::endl;
				order.push_back(node);
				added[id] = true;
				toOrder.pop();
				continue;
			}
			// 3) list its prdecessors into the toOrder
			std::wcout << L"3: " << node->label() << std::endl;
			for (const auto& p : node->predecessors()) {
				toOrder.push(p);
			}
			preds_listed[id] = true;
 		}

		return std::move(order);
	}


	///
	/// Creates a topological order of the input graph.
	///
	/// A topological order is an ordering of the nodes. ..
	///
	/// @param graph The input graph.
	/// @return Vector of the graph's node in topological order.
	template <typename GraphType, typename NodeType>
	std::vector<const NodeType*> topologicalSort(const GraphType &graph) {
		std::vector<const NodeType*> result;
		const auto& nodes = graph.nodes();
		vector<unsigned> incomingEdges(nodes.size()); // by node
		std::transform(begin(nodes), end(nodes), incomingEdges.begin(), [](const Node& n) {return n.predecessorSize(); });
		int counter = 1;
		while (counter > 0) {
			counter = 0;
			for (unsigned id = 0; id < incomingEdges.size(); ++id) {
				if (incomingEdges[id] == 0) {
					result.push_back(&nodes[id]);
					// iterate over the successors and decrement their incoming edges
					for (const auto& n : nodes[id].successors()) {
						--incomingEdges[n->id()];
						++counter;
					}
					incomingEdges[id] = UINT32_MAX;
				}
			}
		}

		return result;
	}

} } }

#endif