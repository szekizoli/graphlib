#ifndef GRAPHLIB_FUNCTION_DESCRIPTOR_H
#define GRAPHLIB_FUNCTION_DESCRIPTOR_H

#include <string>

namespace graphlib { namespace graph { namespace function {

	using std::string;

	class FunctionDescriptor {
	public:
		FunctionDescriptor(string typeString, string color, string shape = "roundrectangle") :
			_typeString(typeString), _color(color), _shape(shape) {}
		FunctionDescriptor(const FunctionDescriptor& other) = default;
		FunctionDescriptor& operator=(FunctionDescriptor& other) = default;
		string typeString() const { return _typeString; }
		string shape() const { return _shape; }
		string color() const { return _color; }
	private:
		string _typeString;
		string _shape;
		string _color;
	};

}}}
#endif