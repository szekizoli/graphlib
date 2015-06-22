#include "Function.h"

#include <numeric>
#include "FunctionBuilder.h"

namespace graphlib { namespace graph { namespace function {
	void Function::init() {}
	
	FunctionAdd FunctionAdd::example(funcexample{});
	FunctionConstant FunctionConstant::example{ funcexample{} };
	FunctionDivide FunctionDivide::example{ funcexample{} };
	FunctionInput FunctionInput::example{ funcexample{} };
	FunctionSubtract FunctionSubtract::example{ funcexample{} };
	FunctionMultiply FunctionMultiply::example{ funcexample{} };

	//FunctionAdd
	FunctionAdd::FunctionAdd(funcexample)
		{ FunctionBuilder::registerFunction("ADD", this); }

	FunctionAdd::FunctionAdd(std::string name) {
		FunctionBuilder::registerFunction(name, this);
	}

	functiondata FunctionAdd::evaluate(const functionlist& input) const {
		return std::accumulate(begin(input), end(input), functiondata{ 0 });
	}

	functionptr FunctionAdd::clone(functiondata) const {
		return std::move(std::make_unique<FunctionAdd>());
	}

	// FunctionConstant
	
	FunctionConstant::FunctionConstant(funcexample) :_value(functiondata{0.0}) {
		FunctionBuilder::registerFunction("CONSTANT", this);
	}
	FunctionConstant::FunctionConstant(functiondata value_) : _value(value_)
	{  }
	functiondata FunctionConstant::evaluate(const functionlist&) const {
		return _value;
	}
	functionptr FunctionConstant::clone(functiondata value_) const {
		return std::move(std::make_unique<FunctionConstant>(value_));
	}

	//FunctionDivide
	FunctionDivide::FunctionDivide(funcexample){ 
		FunctionBuilder::registerFunction("DIVIDE", this); 
	}
	functiondata FunctionDivide::evaluate(const functionlist& input) const {
		return input[0] / input[1];
	}
	functionptr FunctionDivide::clone(functiondata) const {
		return std::move(std::make_unique<FunctionDivide>());
	}

	//FunctionInput
	FunctionInput::FunctionInput(funcexample){
		FunctionBuilder::registerFunction("INPUT", this);
	}
	FunctionInput::FunctionInput(functiondata value_) : _value(value_)
	{  }
	functiondata FunctionInput::evaluate(const functionlist&) const {
		return this->_value;
	}
	functionptr FunctionInput::clone(functiondata value_) const {
		return std::move(std::make_unique<FunctionInput>(value_));
	}
	void FunctionInput::value(functiondata value_) {
		_value = value_;
	}

	//FunctionSubtract
	FunctionSubtract::FunctionSubtract(funcexample){
		FunctionBuilder::registerFunction("SUBTRACT", this);
	}
	functiondata FunctionSubtract::evaluate(const functionlist& input) const {
		return input[0] - input[1];
	}
	functionptr FunctionSubtract::clone(functiondata) const {
		return std::move(std::make_unique<FunctionSubtract>());
	}

	//FunctionMultiply
	FunctionMultiply::FunctionMultiply(funcexample){
		FunctionBuilder::registerFunction("MULTIPLY", this);
	}
	functiondata FunctionMultiply::evaluate(const functionlist& input) const {
		return std::accumulate(begin(input), end(input), functiondata{ 1.0 }, std::multiplies<functiondata>());
	}
	functionptr FunctionMultiply::clone(functiondata) const {
		return std::move(std::make_unique<FunctionMultiply>());
	}
}}}