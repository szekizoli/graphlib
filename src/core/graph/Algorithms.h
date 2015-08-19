#ifndef GRAPHLIB_GRAPH_ALGORITHMS
#define GRAPHLIB_GRAPH_ALGORITHMS

#include <algorithm>
#include <vector>

#include "graph/Graph.h"
#include "graph/Node.h"

namespace graphlib { namespace graph { namespace algorithms {

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
	vector<size_t> predecessorCount(const Graph& graph) {
		vector<size_t> count(graph.order());
		const auto& nodes = graph.nodes();
		std::transform(begin(nodes), end(nodes), begin(count), [](const Node& n) { return n.predecessorSize(); });
		return std::move(count);
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