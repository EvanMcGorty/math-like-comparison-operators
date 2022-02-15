template<typename tl, typename tr>
class smart_comparable
{
template<typename t>
friend constexpr smart_comparable<t&&,t&&> c(t&& a);
template<typename otl, typename otr>
friend class smart_comparable;
private:
	tl left_val;
	tr right_val;
	bool result;

	constexpr smart_comparable(tl&& l, tr&& r, bool b) : left_val(std::forward<tl>(l)), right_val(std::forward<tr>(r)), result(b){}
	
	template<typename rhs_tl, typename rhs_tr, typename operation_callable>
	constexpr smart_comparable<tl,rhs_tr> do_operation(smart_comparable<rhs_tl,rhs_tr>&& rhs,operation_callable const& operation)
	{
		if(result&&rhs.result) //to avoid extra computations when the result is already going to be false
		{
			return smart_comparable<tl,rhs_tr>(std::forward<tl>(left_val),std::forward<rhs_tr>(rhs.right_val),
			operation.template operator()<tr,rhs_tl>(std::forward<tr>(right_val),std::forward<rhs_tl>(rhs.left_val)));
		}
		else
		{
			return smart_comparable<tl,rhs_tr>(std::forward<tl>(left_val),std::forward<rhs_tr>(rhs.right_val),false);
		}
	}
public:
	smart_comparable(smart_comparable const&) = delete;
	smart_comparable(smart_comparable&&) = delete;
	smart_comparable& operator=(smart_comparable const&) = delete;
	smart_comparable& operator=(smart_comparable&&) = delete;
	~smart_comparable() = default;

	constexpr explicit operator bool() const {return result;}
	constexpr bool operator!() const {return !result;}

	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator==(smart_comparable<rhs_tl,rhs_tr>&& rhs) &&
	{
		return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)==std::forward<rt>(r);});
	}
	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator!=(smart_comparable<rhs_tl,rhs_tr>&& rhs) && = delete; //things like x!=y!=z are problematic
	// {
	// 	return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)!=std::forward<rt>(r);});
	// }
	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator<(smart_comparable<rhs_tl,rhs_tr>&& rhs) &&
	{
		return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)<std::forward<rt>(r);});
	}
	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator<=(smart_comparable<rhs_tl,rhs_tr>&& rhs) &&
	{
		return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)<=std::forward<rt>(r);});
	}
	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator>(smart_comparable<rhs_tl,rhs_tr>&& rhs) &&
	{
		return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)>std::forward<rt>(r);});
	}
	template<typename rhs_tl, typename rhs_tr>
	constexpr smart_comparable<tl,rhs_tr> operator>=(smart_comparable<rhs_tl,rhs_tr>&& rhs) &&
	{
		return do_operation(std::move(rhs),[]<typename lt,typename rt>(auto&& l, auto&& r){return std::forward<lt>(l)>=std::forward<rt>(r);});
	}
};

template<typename t>
constexpr smart_comparable<t&&,t&&> c(t&& a)
{
	return {std::forward<t>(a),std::forward<t>(a),true};
}
