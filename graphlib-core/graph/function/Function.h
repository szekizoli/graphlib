#ifndef GRAPHLIB_GRAPH_FUNCTION
#define GRAPHLIB_GRAPH_FUNCTION

#include <memory>
#include <string>
#include <vector>

namespace graphlib { namespace graph { namespace function {

	using std::vector;

	namespace {
		struct funcexample{};
	}

	using functiondata = double;
	using functionlist = vector < functiondata >;
	class Function;
	using functionptr = std::unique_ptr < Function > ;

	class Function {
	public:
		// evaluates the function
		virtual functiondata evaluate(const functionlist& input) const = 0;
		virtual functionptr clone(functiondata) const = 0;
		virtual std::string name() const = 0;
		virtual void value(functiondata) {}
		virtual ~Function() {}
		static void init();
	};

	class FunctionAdd : public Function {
	public:
		FunctionAdd() = default;
		FunctionAdd(funcexample);
		FunctionAdd(const FunctionAdd&) = delete;
		FunctionAdd(const FunctionAdd&&) = delete;
		FunctionAdd& operator=(const FunctionAdd&) = delete;
		FunctionAdd& operator=(const FunctionAdd&&) = delete;
		virtual std::string name() const override { return FunctionAdd::NAME; }
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	private:
		static FunctionAdd example;
		static const std::string NAME;
	};

	class FunctionConstant : public Function {
	public:
		FunctionConstant(functiondata value_);
		FunctionConstant(funcexample);
		FunctionConstant(const FunctionConstant&) = delete;
		FunctionConstant(const FunctionConstant&&) = delete;
		FunctionConstant& operator=(const FunctionConstant&) = delete;
		FunctionConstant& operator=(const FunctionConstant&&) = delete;
		virtual std::string name() const override { return FunctionConstant::NAME; }
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	
		static const std::string NAME;
	private:
		static FunctionConstant example;
		const functiondata _value;
	};

	// deprecated - will be replaced by FunctionReciprocal
	class FunctionDivide : public Function {
	public:
		FunctionDivide() = default;
		FunctionDivide(funcexample);
		FunctionDivide(const FunctionDivide&) = delete;
		FunctionDivide(const FunctionDivide&&) = delete;
		FunctionDivide& operator=(const FunctionDivide&) = delete;
		FunctionDivide& operator=(const FunctionDivide&&) = delete;
		virtual std::string name() const override { return ""; }
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	private:
		static FunctionDivide example;
		static const std::string NAME;
	};

	class FunctionInput : public Function {
	public:
		FunctionInput(functiondata value_ = 0);
		FunctionInput(funcexample);
		FunctionInput(const FunctionInput&) = delete;
		FunctionInput(const FunctionInput&&) = delete;
		FunctionInput& operator=(const FunctionInput&) = delete;
		FunctionInput& operator=(const FunctionInput&&) = delete;
		virtual std::string name() const override { return FunctionInput::NAME; }
		void value(functiondata value_) override;
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	
		static const std::string NAME;
	private:
		functiondata _value;
		static FunctionInput example;
	};

	class FunctionOpposite : public Function {
	public:
		FunctionOpposite() = default;
		FunctionOpposite(funcexample);
		FunctionOpposite(const FunctionOpposite&) = delete;
		FunctionOpposite(const FunctionOpposite&&) = delete;
		FunctionOpposite& operator=(const FunctionOpposite&) = delete;
		FunctionOpposite& operator=(const FunctionOpposite&&) = delete;
		virtual std::string name() const override { return FunctionOpposite::NAME; }
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	
		static const std::string NAME;
	private:
		static FunctionOpposite example;
	};

	class FunctionMultiply : public Function {
	public:
		FunctionMultiply() = default;
		FunctionMultiply(funcexample);
		FunctionMultiply(const FunctionMultiply&) = delete;
		FunctionMultiply(const FunctionMultiply&&) = delete;
		FunctionMultiply& operator=(const FunctionMultiply&) = delete;
		FunctionMultiply& operator=(const FunctionMultiply&&) = delete;
		virtual std::string name() const override { return FunctionMultiply::NAME; }
		virtual functiondata evaluate(const functionlist& input) const override;
		virtual functionptr clone(functiondata _value = 0.0) const override;
	private:
		static FunctionMultiply example;
		static const std::string NAME;
	};
}}}

#endif