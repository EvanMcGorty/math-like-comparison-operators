# math-like-comparison-operators
small c++ proof-of-concept library to allow expressions like x>y>z with type flexibility and zero overhead

Using lots of templates and lots of std::forward, I threw this together one day out of boredom. I'm sure this has been done many times before.
The function c wraps an object (storing by reference, so no overhead) and lets you do c(x) (comparison) c(y) (comparison) c(z) etc.
It is smart enough to lazily evaluate so if x>y  evaluates to false in x>y>z then it will not bother evaluating y>z.
Everything is, of course, constexpr friendly.
operator!= is deleted for now due to the ambiguities/complexities of x!=y!=z.
Regardless of types or r/lvalue-ness, c(x)>c(y) works if x>y works, though auto&& z = c(x())>c(y()) will result in z storing dangling references.
