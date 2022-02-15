#include<iostream>
#include<optional>

#include"smart_comparisons.h"

//class to test smart_comparable (ensure no dangling references or constructors are called)
template<typename t>
class num
{
private:
	std::optional<t> val;
friend int main(); //so that main may construct nums to be used but smart_comparable may not
	num(t&& a) : val(a) {}
	num(t const& a) : val(a) {}
public:
	num& operator=(t&& a) = delete;
	num& operator=(t const& a) = delete;

	~num() {val = std::nullopt;}

	auto operator==(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val == *rhs.val;
	}
	auto operator!=(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val != *rhs.val;
	}
	auto operator<=(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val <= *rhs.val;
	}
	auto operator>=(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val >= *rhs.val;
	}
	auto operator<(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val < *rhs.val;
	}
	auto operator>(num const& rhs) const
	{
		if(!val || !rhs.val) {throw;}
		return *val > *rhs.val;
	}
};

int main()
{
	num n7{7};
	num n11{11};
	num n20{20};
	const num n8{8};
	num n9{9};

	auto&& result = c(num{7}) == c(n7) < c(n11) == c(n11) == c(num{11}) < c(n20) <= c(n20) > c(n8) <= c(n9) < c(num{50});

	std::cout << bool{result};
	
	std::cout << bool{
		c(17.0) == c(17) > c(4.5) > c(3) < c(3.5)
	};

	std::cout << bool{
		c(10) <= c(10) < c(14) == c(18)
	};

	constexpr bool is_true{c(5)>c(1.5)<c(1.500001)};
	static_assert(is_true);
}