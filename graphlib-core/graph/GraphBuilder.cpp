#include "GraphBuilder.h"

#include <sstream>
#include <stdexcept>

#include "function\FunctionBuilder.h"

namespace graphlib { namespace graph {
	NodeId GraphBuilder::addNode(Label _label, std::string functionName, functiondata value_) {
		NodeId id{ this->_nodes.size() };
		auto func = FunctionBuilder(functionName).build(value_);
		this->_nodes.emplace_back(Node(id, _label, std::move(func), NodeDescriptor{}));
		this->_ids[_label] = id;
		return id;
	}

	bool GraphBuilder::addEdge(NodeId from, NodeId to) {
		auto size = this->_nodes.size();
		if (from >= size || to >= size) {
			return false;
		}
		this->doAddEdge(from, to);
		return true;
	}

	bool GraphBuilder::addEdge(Label label_from, Label label_to) {
		NodeId from;
		if (!resolveNode(label_from, from)) {
			return false;
		}
		NodeId to;
		if (!resolveNode(label_to, to)) {
			return false;
		}

		this->doAddEdge(from, to);
		return true;
	}

	void GraphBuilder::doAddEdge(NodeId from, NodeId to) {
		Node* n1 = &_nodes[from];
		Node* n2 = &_nodes[to];
		n1->addSuccessor(n2);
		n2->addPredecessor(n1);
	}

	bool GraphBuilder::resolveNode(Label _label, NodeId& _id) {
		auto it = this->_ids.find(_label);
		if (it == this->_ids.end()) {
			return false;
		}

		_id = it->second;
		return true;
	}

	Graph GraphBuilder::build() {
		return Graph(std::move(this->_nodes));
	}
}}