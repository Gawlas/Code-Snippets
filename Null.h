#undef NULL
const class Null
{
public:
	template <typename T> operator T* () const { return 0; }
	template <class C, typename T> operator T C::*() { return 0; }
private:
	void operator & () const;
} NULL;