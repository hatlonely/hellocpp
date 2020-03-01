#include <gtest/gtest.h>
#include <boost/proto/proto.hpp>
#include <iostream>

TEST(testProto, case1) {
    boost::proto::terminal<std::ostream&>::type cout_ = {std::cout};
    boost::proto::default_context               ctx;
    boost::proto::eval(cout_ << "hello world", ctx);
}

template <int I>
struct placeholder_t {};

struct calculator_context_t : boost::proto::callable_context<calculator_context_t const> {
    std::vector<double> args;
    typedef double      result_type;
    template <int I>
    double operator()(boost::proto::tag::terminal, placeholder_t<I>) const {
        return this->args[I];
    }
};

TEST(testProto, case2) {
    boost::proto::terminal<placeholder_t<0>>::type const _1 = {{}};
    boost::proto::terminal<placeholder_t<1>>::type const _2 = {{}};

    calculator_context_t ctx;
    ctx.args.push_back(45);
    ctx.args.push_back(50);

    double d = boost::proto::eval((_2 - _1) / _2 * 100, ctx);

    EXPECT_NEAR(d, 10, 0.0001);
}

template <typename E>
struct calculator_t;

struct calculator_grammar : boost::proto::or_<
                                boost::proto::plus<calculator_grammar, calculator_grammar>,
                                boost::proto::minus<calculator_grammar, calculator_grammar>,
                                boost::proto::multiplies<calculator_grammar, calculator_grammar>,
                                boost::proto::divides<calculator_grammar, calculator_grammar>,
                                boost::proto::terminal<boost::proto::_>> {};

struct calculator_domain : boost::proto::domain<boost::proto::generator<calculator_t>> {};

template <typename E>
struct calculator_t : boost::proto::extends<E, calculator_t<E>, calculator_domain> {
    typedef boost::proto::extends<E, calculator_t<E>, calculator_domain> base_type;

    calculator_t(E const& expr = E()) : base_type(expr){};

    typedef double result_type;

    double operator()(double x = 0, double y = 0) const {
        BOOST_MPL_ASSERT((boost::proto::matches<E, calculator_grammar>));

        calculator_context_t ctx;
        ctx.args.push_back(x);
        ctx.args.push_back(y);

        return boost::proto::eval(*this, ctx);
    }
};

TEST(testProto, case3) {
    calculator_t<boost::proto::terminal<placeholder_t<0>>::type> const _1;
    calculator_t<boost::proto::terminal<placeholder_t<1>>::type> const _2;

    double d = ((_2 - _1) / _2 * 100)(45.0, 50.0);
    EXPECT_NEAR(d, 10, 0.0001);
}
