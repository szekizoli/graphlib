#include "Node.h"

#include <iostream>

namespace graphlib { namespace graph {
	Node::Node() {}

	Node::Node(NodeId id_, Label label_, functionptr&& func_)
		: _id(id_), _label(label_), _function(std::move(func_))
	{
	}

	Node::Node(NodeId id_, Label label_, functionptr&& func_, NodeDescriptor descriptor_)
		: _id(id_), _label(label_), _function(std::move(func_)), _descriptor(descriptor_)
	{
	}

	Node::Node(Node&& other) :
		_id(other._id), _label(other._label), _function(std::move(other._function)), _descriptor(other._descriptor)
	{
	}

	Node& Node::operator=(Node&& other)
	{
		std::swap(this->_id,         other._id);
		std::swap(this->_label,      other._label);
		std::swap(this->_function,   other._function);
		std::swap(this->_descriptor, other._descriptor);

		return *this;
	}

	void Node::addPredecessor(NodePtr predecessor) {
		this->_predecessors.push_back(predecessor);
	}

	void Node::addSuccessor(NodePtr successor) {
		this->_successors.push_back(successor);
	}

	void make_edge(Node& tail, Node& head) {
		tail.addSuccessor(&head);
		head.addPredecessor(&tail);
	}
}}