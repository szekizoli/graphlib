#include "FunctionBuilder.h"

#include <iostream>
#include <utility>

namespace graphlib { namespace graph { namespace function {

	FunctionBuilder::FunctionBuilder(std::string type_) : _type(type_), _color("#0099AA"), _shape("rectangle") {
	}

	std::map<std::string, const Function*>& FunctionBuilder::registered() {
		static std::map<std::string, const Function*> functions_map;
		return functions_map;
	}

	std::map<std::string, const FunctionDescriptor>& FunctionBuilder::descriptors() {
		static std::map<std::string, const FunctionDescriptor> functions_map;
		return functions_map;
	}

	void FunctionBuilder::registerFunction(std::string _type, const Function* _func) {
		std::cout << "Registering function " << _type << std::endl;
		FunctionBuilder::registered()[_type] = _func;
	}

	void FunctionBuilder::registerDescriptor(std::string _type, FunctionDescriptor _descriptor) {
		FunctionBuilder::descriptors().insert(std::make_pair(_type, _descriptor));
	}

	std::unique_ptr<Function> FunctionBuilder::build(functiondata value_) {
		const auto it = FunctionBuilder::registered().find(_type);
		return it == FunctionBuilder::registered().end() ? nullptr : (*it).second->clone(value_);
	}

	FunctionBuilder& FunctionBuilder::color(std::string color_) {
		_color = color_;
		return *this;
	}

	FunctionBuilder& FunctionBuilder::shape(std::string shape_) {
		_shape = shape_;
		return *this;
	}

	FunctionDescriptor FunctionBuilder::buildDescriptor() {
		return FunctionDescriptor(_type, _color, _shape);
	}

}}}