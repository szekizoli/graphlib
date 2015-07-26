#ifndef GRAPHLIB_GRAPH_ALGORITHMS
#define GRAPHLIB_GRAPH_ALGORITHMS

#include <algorithm>
#include <vector>
#include "Graph.h"
#include "Node.h"

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

	///
	/// Creates a topological order of the input graph.
	///
	/// A topological order is an ordering of the nodes. ..
	///
	/// @param graph The input graph.
	/// @return Vector of the graph's node in topological order.
	//template <typename GraphType, typename NodeType>
	std::vector<const Node/*Type*/*> topologicalSort(const Graph/*Type*/ &graph) {
		std::vector<const Node/*Type*/*> result;
		const auto& nodes = graph.nodes();
		vector<unsigned> incomingEdges; // by node
		std::transform(begin(nodes), end(nodes), incomingEdges.begin(), [](const Node& n) {return n.predecessorSize(); });
		for (unsigned i = 0; i < incomingEdges.size(); ++i) {
			if (incomingEdges[i] == 0) {
				result.push_back(&nodes[i]);
				// iterate over the successors and decrement their incoming edges
			}
		}



		return result;
	}

} } }

#endif