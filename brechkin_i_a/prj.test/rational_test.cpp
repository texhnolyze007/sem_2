#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <rational/rational.hpp>
#include <sstream>

TEST_CASE("[rational] - Rational ctor") {
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(3) == Rational(3, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("[rational] - Rational add") {
    CHECK(Rational(3, 2) + Rational(5, 7) == Rational(31, 14));
    CHECK(Rational(5, 7) + Rational(3, 2) == Rational(31, 14));
    CHECK(Rational() + Rational() == Rational());
    CHECK(Rational() + Rational(29, 41) == Rational(29, 41));
    CHECK(Rational(5, 1) + Rational(3, 2) == Rational(13, 2));
}

TEST_CASE("[rational] - Rational subtract") {
    CHECK(Rational(31, 14) - Rational(5, 7) == Rational(3, 2));
    CHECK(Rational(25, 7) - Rational(2, 9) == Rational(211, 63));
    CHECK(Rational(2, 3) - Rational(7, 4) == Rational(-13, 12));
}

TEST_CASE("[rational] - Rational division") {
    CHECK(Rational(5, 2) / Rational(5, 2) == Rational(1, 1));
    CHECK(Rational(3, 2) / Rational(9, 8) == Rational(4, 3));
    CHECK_THROWS(Rational(3, 2) / Rational(5, 0));
}

TEST_CASE("[rational] - Rational minus") {
    CHECK(-Rational() == Rational());
    CHECK(Rational(-5, 3) == -Rational(5, 3));
    CHECK(Rational(25, 7) == -(-(Rational(25, 7))));
    CHECK(Rational(29, 41) == -Rational(-29, 41));

    SUBCASE("Correct inputs") {
        Rational r;
        std::stringstream sstrm;

        SUBCASE("Two in one line") {
            sstrm.str("2/3 1/3");
            sstrm >> r >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(1, 3));
        }

        SUBCASE("Simple") {
            sstrm.str("2/3");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(2, 3));
        }

        sstrm.clear();

        SUBCASE("Input with reducing") {
            sstrm.str("36/48");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(3, 4));
        }

        sstrm.clear();

        SUBCASE("Negative input") {
            sstrm.str("-8/7");
            sstrm >> r;
            CHECK(sstrm.rdstate() == std::ios_base::eofbit);
            CHECK(r == Rational(-8, 7));
        }
    }
}