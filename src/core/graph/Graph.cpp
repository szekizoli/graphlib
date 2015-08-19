#include "graph/Graph.h"

#include <numeric>

namespace graphlib { namespace graph {

	Graph::Graph() {
	}

	Graph::Graph(std::vector<Node>&& nodes_) : _nodes(std::move(nodes_))
	{
	}

	Graph::Graph(Graph&& other) : _nodes(std::move(other._nodes)), _iterator_end(std::move(other._iterator_end)) 
	{
	}

	Graph& Graph::operator=(Graph&& other) {
		_nodes.swap(other._nodes);
		_iterator_end = std::move(other._iterator_end);
		return *this;
	}

	size_t Graph::order() const {
		return _nodes.size();
	}

	size_t Graph::size() const {
		return std::accumulate(begin(_nodes), end(_nodes), size_t{ 0 },
			[](size_t init, const Node& n){ return init + n.successorSize(); });
	}

	const NodePtrList Graph::find_input_nodes() const {
		NodePtrList input_nodes;
		for (const auto& n : _nodes) {
			if (n.predecessorSize() == 0) {
				input_nodes.push_back(&n);
			}
		}
		return std::move(input_nodes);
	}

	const NodePtrList Graph::find_output_nodes() const {
		NodePtrList output_nodes;
		for (const auto& n : _nodes) {
			if (n.successorSize() == 0) {
				output_nodes.push_back(&n);
			}
		}
		return std::move(output_nodes);
	}

	const Node& Graph::operator[](const NodeId idx) const
	{
		return _nodes[idx];
	}
}}