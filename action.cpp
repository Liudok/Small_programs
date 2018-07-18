#include <iostream>

void function()
{
	std::cout<<1<<std::endl;
}
struct Functor
{
	std::string String;
	void operator()()
	{
		std::cout<<String<<std::endl;
	}
};

class Action
{
	
public:
	template<typename F>
	Action(F other) {
		*this = other;
	}

	void operator()()
	{
		callable_base *tmp = c.get();
		(*tmp)();
	}

	template<typename F>
	Action& operator=(F& other) {
		c.reset(new callable<F>(other));
		return *this;
	}

	template<typename F>
	Action(const Action& other) : c(other.c){}

private:

	struct callable_base
	{
	   virtual void operator()() = 0;
	   virtual ~callable_base() {}
	};

	template <typename F>
	struct callable : public callable_base
	{
	   F functor_;
	   callable(F functor) : functor_(functor) {}
	   void operator()()
	   {
	   		return functor_();
	   }
	};

	std::shared_ptr<callable_base> c;

};

int main()
{
	Action action=function;
	action();//1
	action=Functor{"qqq"};
	action();//qqq
	Action action2=action;
	action=Functor{"www"};
	action2();//qqq
	action();//www
	return 0;
}
