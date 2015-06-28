#ifndef GRAPHLIB_GRAPH_GRAPHBUILDER_H 
#define GRAPHLIB_GRAPH_GRAPHBUILDER_H

#include <memory>
#include <string>
#include <vector>

#include "Node.h"
#include "Graph.h"

namespace graphlib { namespace graph {

	class GraphBuilder {
	public:
		GraphId addNode(Label _label, std::string functionName);
		void addEdge(GraphId from, GraphId to);
		void addEdge(Label from, Label to);
		GraphId resolveNode(Label _label);
		Graph build();
	private:

	};

}}

#endif