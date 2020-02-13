#include <gtest/gtest.h>
#include <chrono>
#include <iostream>
#include <map>
#include <random>

TEST(testRandomDevice, case1) {
    std::random_device rand;
    std::cout << "random_device: ";
    for (int i = 0; i < 10; i++) {
        std::cout << rand() % 100 << ", ";
    }
    std::cout << std::endl;
}

TEST(testPredefinedRandom, case1) {
    {
        std::minstd_rand rand(std::time(nullptr));
        std::cout << "minstd_rand: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::minstd_rand0 rand(std::time(nullptr));
        std::cout << "minstd_rand0: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::mt19937 rand(std::time(nullptr));
        std::cout << "mt19937: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::mt19937_64 rand(std::time(nullptr));
        std::cout << "mt19937_64: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::ranlux24_base rand(std::time(nullptr));
        std::cout << "ranlux24_base: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::ranlux48_base rand(std::time(nullptr));
        std::cout << "ranlux48_base: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::ranlux24 rand(std::time(nullptr));
        std::cout << "ranlux24: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::ranlux48 rand(std::time(nullptr));
        std::cout << "ranlux48: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::knuth_b rand(std::time(nullptr));
        std::cout << "knuth_b: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
    {
        std::default_random_engine rand(std::time(nullptr));
        std::cout << "default_random_engine: ";
        for (int i = 0; i < 10; i++) {
            std::cout << rand() % 100 << ", ";
        }
        std::cout << std::endl;
    }
}

TEST(testDistribution, case1) {
    std::random_device         rd;
    std::default_random_engine rand(rd());

    {
        std::uniform_int_distribution<int> dis(0, 9);
        std::map<int, int>                 times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "uniform_int_distribution(均匀分布整数): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        std::uniform_real_distribution<> dis(0, 9);
        std::map<int, int>               times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "uniform_real_distribution(均匀分布实数): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        std::normal_distribution<> dis(5, 2.0);  // 平均值为 5，标准差为 2.0
        std::map<int, int>         times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "normal_distribution(标准正态分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 对数正态分布（logarithmic normal distribution）是指一个随机变量的对数服从正态分布。
        // 对数正态分布从短期来看，与正态分布非常接近。但长期来看，对数正态分布向上分布的数值更多一些
        std::lognormal_distribution<> dis(1.6, 0.25);
        std::map<int, int>            times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "lognormal_distribution(对数正态分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 若n个相互独立的随机变量ξ₁，ξ₂，...,ξn ，均服从标准正态分布（也称独立同分布于标准正态分布）
        // 则这n个服从标准正态分布的随机变量的平方和构成一新的随机变量，其分布规律称为卡方分布
        std::chi_squared_distribution<> dis(4);
        std::map<int, int>              times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "chi_squared_distribution(卡方分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 柯西分布是一个数学期望不存在的连续型概率分布。当随机变量X满足它的概率密度函数时，称X服从柯西分布
        std::cauchy_distribution<> dis(5, 2.0);
        std::map<int, int>         times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "cauchy_distribution(柯西分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // F分布是1924年英国统计学家R.A.Fisher提出，并以其姓氏的第一个字母命名的。
        // 它是一种非对称分布，有两个自由度，且位置不可互换。F分布有着广泛的应用，如在方差分析、回归方程的显著性检验中都有着重要的地位
        std::fisher_f_distribution<> dis(5, 2.0);
        std::map<int, int>           times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "fisher_f_distribution(F分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 在概率论和统计学中，t-分布（t-distribution）用于根据小样本来估计呈正态分布且方差未知的总体的均值。
        // 如果总体方差已知（例如在样本数量足够多时），则应该用正态分布来估计总体均值
        std::student_t_distribution<> dis(5);
        std::map<int, int>            times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "student_t_distribution(t分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        std::bernoulli_distribution dis(0.25);  // true 的概率为 0.25
        std::map<bool, int>         times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "bernoulli_distribution(伯努利分布，又叫 0-1 分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 二项分布是由伯努利提出的概念，指的是重复n次独立的伯努利试验
        // 在每次试验中只有两种可能的结果，而且两种结果发生与否互相对立，并且相互独立，与其它各次试验结果无关
        // 事件发生与否的概率在每一次独立试验中都保持不变，则这一系列试验总称为n重伯努利实验
        // 当试验次数为1时，二项分布服从0-1分布
        std::binomial_distribution dis(4, 0.5);
        std::map<int, int>         times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "binomial_distribution(二项分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 负二项分布是统计学上一种离散概率分布。满足以下条件的称为负二项分布：
        // 实验包含一系列独立的实验， 每个实验都有成功、失败两种结果，成功的概率是恒定的，实验持续到r次成功，r为正整数。
        std::negative_binomial_distribution dis(5, 0.75);
        std::map<int, int>                  times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "negative_binomial_distribution(负二项分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 几何分布（Geometric distribution）是离散型概率分布。
        // 其中一种定义为：在n次伯努利试验中，试验k次才得到第一次成功的机率。
        // 详细地说，是：前k-1次皆失败，第k次成功的概率。几何分布是帕斯卡分布当r=1时的特例。
        std::geometric_distribution<> dis;
        std::map<int, int>            times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "geometric_distribution(几何分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // Poisson分布，是一种统计与概率学里常见到的离散概率分布
        // 由法国数学家西莫恩·德尼·泊松（Siméon-Denis Poisson）在1838年时发表。
        std::poisson_distribution<> dis(4);
        std::map<int, int>          times;
        for (int i = 0; i < 10000; i++) {
            ++times[dis(rand)];
        }

        std::cout << "poisson_distribution(泊松分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 指数分布
        std::exponential_distribution<> dis(1);
        std::map<int, int>              times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "exponential_distribution(指数分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 伽玛分布（Gamma Distribution）是统计学的一种连续概率函数，是概率统计中一种非常重要的分布
        // “指数分布”和“χ2分布”都是伽马分布的特例
        std::gamma_distribution<> dis(1, 2);
        std::map<int, int>        times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "gamma_distribution(伽马分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 韦布尔分布，即韦伯分布（Weibull distribution），又称韦氏分布或威布尔分布，是可靠性分析和寿命检验的理论基础
        std::weibull_distribution<> dis;
        std::map<int, int>          times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "weibull_distribution(韦伯分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 极值分布是指在概率论中极大值（或者极小值）的概率分布，
        // 从很多个彼此独立的值中挑出来的各个极大值应当服从的概率密度分布数f(x)
        std::extreme_value_distribution<> dis;
        std::map<int, int>                times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "extreme_value_distribution(极值分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 按照权重分布
        std::discrete_distribution<> dis({40, 10, 10, 40});
        std::map<int, int>           times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "discrete_distribution(离散分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        // 50% 概率生成 0-2，50% 概率生成 10-15
        std::vector<double>                    nums    = {0, 2, 10, 15};
        std::vector<double>                    weights = {1, 0, 1};
        std::piecewise_constant_distribution<> dis(nums.begin(), nums.end(), weights.begin());
        std::map<int, int>                     times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "piecewise_constant_distribution(分段常数分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
    {
        std::vector<double>                  nums    = {0, 5, 10, 15};
        std::vector<double>                  weights = {0, 1, 1, 0};
        std::piecewise_linear_distribution<> dis(nums.begin(), nums.end(), weights.begin());
        std::map<int, int>                   times;
        for (int i = 0; i < 10000; i++) {
            ++times[std::floor(dis(rand))];
        }

        std::cout << "piecewise_linear_distribution(分段线性分布): " << std::endl;
        for (auto p : times) {
            std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                      << p.first << ' ' << std::string(p.second / 100, '*') << '\n';
        }
    }
}
