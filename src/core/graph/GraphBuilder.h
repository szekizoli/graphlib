#ifndef GRAPHLIB_GRAPH_GRAPHBUILDER_H 
#define GRAPHLIB_GRAPH_GRAPHBUILDER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "graph/Node.h"
#include "graph/Graph.h"

namespace graphlib { namespace graph {

	class GraphBuilder {
	public:
		NodeId addNode(Label label_, std::string functionName_, functiondata value_ = 0.0);
		NodeId addNode(Label label_, functionptr&& function_);
		bool addEdge(NodeId from, NodeId to);
		bool addEdge(Label from, Label to);
		bool resolveNode(Label _label, NodeId& _id);
		Graph build();
	private:
		vector<Node> _nodes;
		std::map<Label, NodeId> _ids;
		void doAddEdge(NodeId from, NodeId to);
	};

}}

#endif