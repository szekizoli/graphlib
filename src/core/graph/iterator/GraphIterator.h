#ifndef GRAPH_ITERATOR_H
#define GRAPH_ITERATOR_H

#include <iterator>
#include <queue>

#include "../Node.h"

namespace graphlib { namespace graph {
	using std::queue;

	/*
	* Class iterates over the Graph as BFS.
	*/
	class GraphIterator : public std::iterator<std::input_iterator_tag, NodePtr>
	{
	protected:
		NodePtr node;
		NodePtr end;
		queue<NodePtr> inputNodes;
		//GraphPtr graph;
		// This method chooses the next node and steps there
		virtual void moveNext() = 0;
		virtual void clear() = 0;
	public:
		GraphIterator(NodePtr node, NodePtr end);
		GraphIterator();
		GraphIterator(const GraphIterator& it);
		bool operator==(const GraphIterator& it) const;
		bool operator!=(const GraphIterator& it) const;
		NodePtr operator*() const;
		void setStartNode(NodePtr startNode);
	};
}}

#endif