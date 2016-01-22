#include <list>
#include <string>

typedef std::list<std::string> StackTrace;

class Trace
{
private:
	static StackTrace ms_Trace;

public:
	Trace(const std::string& item) { ms_Trace.push_back(item); }
	~Trace() { ms_Trace.pop_back(); }

	friend const StackTrace& GetStackTrace() { return ms_Trace; }
};
StackTrace Trace::ms_trace;

//Visul C++
#define GUARD Trace __trace(__FUNCTION__ " [" __FILE__ ", line" __LINE__ "]")