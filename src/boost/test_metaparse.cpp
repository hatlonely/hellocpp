#include <gtest/gtest.h>
#include <iostream>
#include <boost/metaparse/string.hpp>
#include <boost/type_index.hpp>
#include <boost/metaparse/int_.hpp>
#include <boost/metaparse/build_parser.hpp>
#include <boost/metaparse/entire_input.hpp>
#include <boost/metaparse/token.hpp>
#include <boost/metaparse/sequence.hpp>
#include <boost/metaparse/lit_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/quote.hpp>
#include <boost/metaparse/transform.hpp>
#include <boost/metaparse/repeated.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/metaparse/foldl.hpp>
#include <boost/metaparse/foldl_start_with_parser.hpp>
#include <boost/metaparse/one_of.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/times.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/metaparse/foldr_start_with_parser.hpp>
#include <boost/mpl/negate.hpp>
#include <boost/metaparse/middle_of.hpp>
#include <boost/metaparse/define_error.hpp>
#include <boost/metaparse/fail.hpp>
#include <boost/metaparse/fail_at_first_char_expected.hpp>
#include <boost/metaparse/first_of.hpp>
#include <boost/metaparse/foldl_reject_incomplete_start_with_parser.hpp>

using boost::metaparse::build_parser;
using boost::metaparse::entire_input;
using boost::metaparse::int_;
using boost::metaparse::token;
using boost::metaparse::sequence;
using boost::metaparse::lit_c;
using boost::metaparse::transform;
using boost::metaparse::repeated;
using boost::metaparse::one_of;

using exp_parser1 = build_parser<int_>;
using exp_parser2 = build_parser<entire_input<int_>>;
using exp_parser3 = build_parser<entire_input<token<int_>>>;
using exp_parser4 = build_parser<sequence<token<int_>, token<lit_c<'+'>>, token<int_>>>;

using int_token = token<int_>;
using plus_token = token<lit_c<'+'>>;

using exp_parser5 = build_parser<sequence<int_token, plus_token, int_token>>;

template <class Vector>
struct eval_plus : boost::mpl::plus<
    typename boost::mpl::at_c<Vector, 0>::type,
    typename boost::mpl::at_c<Vector, 2>::type
> {};

using exp_parser6 = build_parser<transform<sequence<int_token, plus_token, int_token>, boost::mpl::quote1<eval_plus>>>;

using exp_parser7 = build_parser<sequence<int_token, repeated<sequence<plus_token, int_token>>>>;

template <class Sum, class Item>
struct sum_items : boost::mpl::plus<
    Sum,
    typename boost::mpl::at_c<Item, 1>::type
> {};

using exp_parser8 = build_parser<
    sequence<
        int_token,
        transform<
            repeated<sequence<plus_token, int_token>>,
            boost::mpl::lambda<
                boost::mpl::fold<
                    boost::mpl::_1,
                    boost::mpl::int_<0>,
                    boost::mpl::quote2<sum_items>
                >
            >::type
        >
    >
>;

template <class Vector>
class sum_vector : boost::mpl::fold<
    Vector,
    boost::mpl::int_<0>,
    boost::mpl::lambda<
        boost::mpl::plus<boost::mpl::_1, boost::mpl::_2>
    >::type
> {};

using exp_parser9 = build_parser<
    transform<
        sequence<
            int_token,
            transform<
                repeated<sequence<plus_token, int_token>>,
                boost::mpl::lambda<
                    boost::mpl::fold<
                        boost::mpl::_1,
                        boost::mpl::int_<0>,
                        boost::mpl::quote2<sum_items>
                    >
                >::type
            >
        >,
        boost::mpl::quote1<sum_vector>
    >
>;

using exp_parser10 = build_parser<
    transform<
        sequence<
            int_token,
            boost::metaparse::foldl<
                sequence<plus_token, int_token>,
                boost::mpl::int_<0>,
                boost::mpl::quote2<sum_items>
            >
        >,
        boost::mpl::quote1<sum_vector>
    >
>;

using exp_parser11 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<plus_token, int_token>,
        int_token,
        boost::mpl::quote2<sum_items>
    >
>;

// add minus operator
using minus_token = token<lit_c<'-'>>;

using exp_parser12 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, int_token>,
        int_token,
        boost::mpl::quote2<sum_items>
    >
>;

template <class L, char OP, class R> struct eval_binary_op;
template <class L, class R> struct eval_binary_op<L, '+', R> : boost::mpl::plus<L, R>::type {};
template <class L, class R> struct eval_binary_op<L, '-', R> : boost::mpl::minus<L, R>::type {};

template <class S, class Item>
struct binary_op : eval_binary_op<
    S,
    boost::mpl::at_c<Item, 0>::type::value,
    typename boost::mpl::at_c<Item, 1>::type
> {};

using exp_parser13 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, int_token>,
        int_token,
        boost::mpl::quote2<binary_op>
    >
>;

// add times operator
template <class L, class R> struct eval_binary_op<L, '*', R> : boost::mpl::times<L, R>::type {};

using times_token = token<lit_c<'*'>>;

using exp_parser14 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token, times_token>, int_token>,
        int_token,
        boost::mpl::quote2<binary_op>
    >
>;

// add precedence
using multi_exp1 = boost::metaparse::foldl_start_with_parser<
    sequence<times_token, int_token>,
    int_token,
    boost::mpl::quote2<binary_op>
>;

using exp_parser15 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, multi_exp1>,
        multi_exp1,
        boost::mpl::quote2<binary_op>
    >
>;

// add divides operator
template <class L, class R> struct eval_binary_op<L, '/', R> : boost::mpl::divides<L, R>::type {};

using divide_token = token<lit_c<'/'>>;

using multi_exp2 = boost::metaparse::foldl_start_with_parser<
    sequence<one_of<times_token, divide_token>, int_token>,
    int_token,
    boost::mpl::quote2<binary_op>
>;

using exp_parser16 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, multi_exp2>,
        multi_exp2,
        boost::mpl::quote2<binary_op>
    >
>;

// add associativity
template <class S, class Item>
struct reverse_binary_op : eval_binary_op<
    typename boost::mpl::at_c<Item, 0>::type,
    boost::mpl::at_c<Item, 1>::type::value,
    S
> {};

using multi_exp3 = boost::metaparse::foldr_start_with_parser<
    sequence<int_token, one_of<times_token, divide_token>>,
    int_token,
    boost::mpl::quote2<reverse_binary_op>
>;

using exp_parser17 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, multi_exp3>, multi_exp3,
        boost::mpl::quote2<binary_op>
    >
>;

// support unary operator
using unary_exp1 = boost::metaparse::foldr_start_with_parser<
    minus_token,
    int_token,
    boost::mpl::lambda<boost::mpl::negate<boost::mpl::_1>>::type
>;

using multi_exp4 = boost::metaparse::foldl_start_with_parser<
    sequence<one_of<times_token, divide_token>, unary_exp1>,
    unary_exp1,
    boost::mpl::quote2<binary_op>
>;

using exp_parser18 = build_parser<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, multi_exp4>,
        multi_exp4,
        boost::mpl::quote2<binary_op>
    >
>;

// add parens
using lparen_token = token<lit_c<'('>>;
using rparen_token = token<lit_c<')'>>;

using plus_exp1 = boost::metaparse::foldl_start_with_parser<
    sequence<one_of<plus_token, minus_token>, multi_exp4>,
    multi_exp4,
    boost::mpl::quote2<binary_op>
>;

using paren_exp1 = sequence<lparen_token, plus_exp1, rparen_token>;
using paren_exp2 = boost::metaparse::middle_of<lparen_token, plus_exp1, rparen_token>;
using primary_exp1 = one_of<int_token, paren_exp2>;
struct plus_exp2;
using paren_exp3 = boost::metaparse::middle_of<lparen_token, plus_exp2, rparen_token>;
using primary_exp2 = one_of<int_token, paren_exp2>;
using unary_exp2 = boost::metaparse::foldr_start_with_parser<
    minus_token,
    primary_exp2,
    boost::mpl::lambda<boost::mpl::negate<boost::mpl::_1>>::type
>;
using multi_exp5 = boost::metaparse::foldl_start_with_parser<
    sequence<one_of<times_token, divide_token>, unary_exp2>,
    unary_exp2,
    boost::mpl::quote2<binary_op>
>;
struct plus_exp2 : boost::metaparse::foldl_start_with_parser<
    sequence<one_of<plus_token, minus_token>, multi_exp5>,
    multi_exp5,
    boost::mpl::quote2<binary_op>
> {};

using exp_parser19 = build_parser<plus_exp2>;

// on fail
BOOST_METAPARSE_DEFINE_ERROR(missing_primary_expression, "Missing primary expression");
struct plus_exp3;
using paren_exp4 = boost::metaparse::middle_of<lparen_token, plus_exp3, rparen_token>;
using primary_exp3 = one_of<int_token, paren_exp4, boost::metaparse::fail<missing_primary_expression>>;
using unary_exp3 = boost::metaparse::foldr_start_with_parser<
    minus_token,
    primary_exp3,
    boost::mpl::lambda<boost::mpl::negate<boost::mpl::_1>>::type
>;
using multi_exp6 = boost::metaparse::foldl<
    sequence<one_of<times_token, divide_token>, unary_exp3>,
    unary_exp3,
    boost::mpl::quote2<binary_op>
>;
struct plus_exp3 : boost::metaparse::foldl_start_with_parser<
    sequence<one_of<plus_token, minus_token>, multi_exp6>,
    multi_exp6,
    boost::mpl::quote2<binary_op>
>{};

using exp_parser20 = build_parser<plus_exp3>;

// on fail throw expection
struct plus_exp4 : boost::metaparse::first_of<
    boost::metaparse::foldl_start_with_parser<
        sequence<one_of<plus_token, minus_token>, multi_exp6>,
        multi_exp6,
        boost::mpl::quote2<binary_op>
    >,
    boost::metaparse::fail_at_first_char_expected<
        sequence<one_of<plus_token, minus_token>, multi_exp6>
    >
> {};

using exp_parser21 = build_parser<plus_exp4>;

// using incomplete parser
struct plus_exp5 : boost::metaparse::foldl_reject_incomplete_start_with_parser<
    sequence<one_of<plus_token, minus_token>, multi_exp6>,
    multi_exp6,
    boost::mpl::quote2<binary_op>
> {};

using exp_parser22 = build_parser<plus_exp5>;

struct plus_exp6;
using paren_exp5 = boost::metaparse::middle_of<lparen_token, plus_exp6, rparen_token>;
using primary_exp4 = one_of<int_token, paren_exp5, boost::metaparse::fail<missing_primary_expression>>;
using unary_exp4 = boost::metaparse::foldr_start_with_parser<
    minus_token, primary_exp4,
    boost::mpl::lambda<boost::mpl::negate<boost::mpl::_1>>::type
>;
using multi_exp7 = boost::metaparse::foldl_reject_incomplete_start_with_parser<
    sequence<one_of<times_token, divide_token>, unary_exp4>,
    unary_exp4,
    boost::mpl::quote2<binary_op>
>;
struct plus_exp6 : boost::metaparse::foldl_reject_incomplete_start_with_parser<
    sequence<one_of<plus_token, minus_token>, multi_exp7>,
    multi_exp7,
    boost::mpl::quote2<binary_op>
> {};

using exp_parser23 = build_parser<plus_exp6>;

TEST(testMetaparse, case1) {
    std::cout << boost::typeindex::type_id_with_cvr<BOOST_METAPARSE_STRING("11 + 2")>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser6::apply<BOOST_METAPARSE_STRING("11 + 2")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser10::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 + 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser11::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 + 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser12::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 - 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser13::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 - 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser14::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 * 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser15::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 * 4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser16::apply<BOOST_METAPARSE_STRING("1 + 2 + 3 * 4 / 5")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser16::apply<BOOST_METAPARSE_STRING("8 / 4 / 2")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser18::apply<BOOST_METAPARSE_STRING("1 -2 + -4")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser19::apply<BOOST_METAPARSE_STRING("(1 + 2) * 3")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser20::apply<BOOST_METAPARSE_STRING("hello")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser21::apply<BOOST_METAPARSE_STRING("0+(1+2")>::type>() << std::endl;
    std::cout << boost::typeindex::type_id_with_cvr<exp_parser22::apply<BOOST_METAPARSE_STRING("0+(1+2")>::type>() << std::endl;
//    std::cout << boost::typeindex::type_id_with_cvr<exp_parser23::apply<BOOST_METAPARSE_STRING("0+(1+2")>::type>() << std::endl;
}
