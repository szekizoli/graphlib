#include "graph/GraphBuilder.h"

#include <sstream>
#include <stdexcept>

#include "graph/function/FunctionBuilder.h"

namespace graphlib { namespace graph {

	NodeBuilder::NodeBuilder() {}

	NodeBuilder::NodeBuilder(NodeId id_, GraphBuilder* builder_)
		: _id(id_), _builder(builder_) {
	}

	NodeId NodeBuilder::id() const {
		return _id;
	}

	GraphBuilder* NodeBuilder::graph_builder() const {
		return _builder;
	}

	NodeBuilder GraphBuilder::addNode(Label label_, std::string functionName, functiondata value_) {
		NodeId id{ this->_nodes.size() };
		NodeBuilder node{ id, this };
		auto func = FunctionBuilder(functionName).build(value_);
		this->_nodes.emplace_back(Node(id, label_, std::move(func), NodeDescriptor{}));
		this->_ids[label_] = id;
		return node;
	}

	NodeBuilder GraphBuilder::addNode(Label label_, functionptr&& function_) {
		NodeId id{ this->_nodes.size() };
		NodeBuilder node{ id, this };
		this->_nodes.emplace_back(Node(id, label_, std::move(function_), NodeDescriptor{}));
		this->_ids[label_] = id;
		return node;
	}

	bool GraphBuilder::addEdge(NodeBuilder from, NodeBuilder to) {
		auto size = this->_nodes.size();
		if (from.id() >= size || to.id() >= size) {
			return false;
		}
		this->doAddEdge(from.id(), to.id());
		return true;
	}

	bool GraphBuilder::addEdge(Label label_from, Label label_to) {
		NodeBuilder from;
		if (!resolve_node(label_from, from)) {
			return false;
		}
		NodeBuilder to;
		if (!resolve_node(label_to, to)) {
			return false;
		}

		this->doAddEdge(from.id(), to.id());
		return true;
	}

	void GraphBuilder::doAddEdge(NodeId from, NodeId to) {
		Node* n1 = &_nodes[from];
		Node* n2 = &_nodes[to];
		n1->addSuccessor(n2);
		n2->addPredecessor(n1);
	}

	bool GraphBuilder::resolve_node(Label label, NodeBuilder& id) {
		auto it = this->_ids.find(label);
		if (it == this->_ids.end()) {
			return false;
		}

		id._id = it->second;
		return true;
	}

	Graph GraphBuilder::build() {
		return Graph(std::move(this->_nodes));
	}
}}