#ifndef GRAPHLIB_GRAPH_GRAPH 
#define GRAPHLIB_GRAPH_GRAPH

#include <memory>
#include <vector>

#include "Node.h"

namespace graphlib { namespace graph {
	class Graph;
	class BFSIterator;
	class DFSIterator;
	typedef std::unique_ptr<Graph> GraphPtr;

	// Models an executable graph
	class Graph
	{
	public:
		// constructs an empty graph
		Graph();
		// constructs a graph with the given nodes
		Graph(std::vector<Node>&& nodes_);
		// copy constructor - deleted
		Graph(const Graph& other) = delete;
		// move constructor
		Graph(Graph&& other);
		// copy assignment operator - deleted
		Graph& operator=(const Graph& other) = delete;
		// move assignment operator
		Graph& operator=(Graph&& other);
		// descturctor;
		~Graph() = default;

		// gets the # of nodes
		size_t order() const;
		// gets the # of edges
		size_t size() const;

		// returns the list of nodes
		const NodeList& nodes() const { return _nodes; }

		// finds and returns the vector of  input nodes
		const NodePtrList find_input_nodes() const;
		// finds and returns the vector of output nodes
		const NodePtrList find_output_nodes() const;

		// utility to iterate over the graph using BFS
		struct bfs_iterator {
			bfs_iterator(const Graph& g_);
			bfs_iterator& operator=(const bfs_iterator&) = delete;
			BFSIterator begin() const;
			BFSIterator end() const;
		private:
			const Graph& graph;
		};

		// utility to iterate over the graph using DFS
		struct dfs_iterator {
			dfs_iterator(const Graph& g_);
			dfs_iterator& operator=(const dfs_iterator&) = delete;
			DFSIterator begin() const;
			DFSIterator end() const;
		private:
			const Graph& graph;
		};

		// bfs iterator
		bfs_iterator bfs() const {
			return bfs_iterator(*this);
		}

		// dfs iterator
		dfs_iterator dfs() const {
			return dfs_iterator(*this);
		}
	private:
		NodeList _nodes;
		Node _iterator_end;

		friend class GraphIterator;
		friend class BFSIterator;
		friend class DFSIterator;
	};
}}
#endif