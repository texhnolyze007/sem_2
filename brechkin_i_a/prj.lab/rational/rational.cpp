#include <rational/rational.hpp>
#include<iostream>

Rational::Rational(int num) noexcept : num_(num), den_(1) {}

Rational::Rational(int num, int den) : num_(num), den_(den) {
	if (den == 0) {
		throw("Division by zero");
	}
	normalize();
}



bool Rational::operator<(const Rational& rat) const noexcept {
	return num() * rat.denom() < denom() * rat.num();
}

bool Rational::operator==(const Rational& rat) const noexcept {
	if (rat.denom() == denom() && rat.num() == num()) {
		return true;
	}
	return false;
}

bool Rational::operator!=(const Rational& rat) const noexcept {
	return !operator== (rat);
}

bool Rational::operator<=(const Rational& rat) const noexcept {
	return operator<(rat) || operator==(rat);
}

bool Rational::operator>(const Rational& rat) const noexcept {
	return !operator<=(rat);
}

bool Rational::operator>=(const Rational& rat) const noexcept {
	return !operator>(rat);
}

Rational Rational::operator-() const noexcept {
	return Rational(-num(), denom());
}

Rational::operator bool() const noexcept {
	return (bool)num();
}

Rational& Rational::operator*=(const Rational& rat) noexcept {
	num_ *= rat.num();
	den_ *= rat.denom();
	normalize();
	return *this;
}

Rational& Rational::operator+=(const Rational& rat) noexcept {
	num_ = rat.denom() * num() + rat.num() * denom();
	den_ *= rat.denom();
	normalize();
	return *this;
}

Rational& Rational::operator-=(const Rational& rat) noexcept {
	num_ = rat.denom() * num() - rat.num() * denom();
	den_ *= rat.denom();
	normalize();
	return *this;
}

Rational& Rational::operator/=(const Rational& rat) {
	if (rat.num() == 0) {
		throw("Division by zero");
	}
	num_ *= rat.denom();
	den_ *= rat.num();
	normalize();
	return *this;
}



std::ostream& Rational::OutPut(std::ostream& ostrm) const noexcept {
	ostrm << num() << ' ' << del() << ' ' << denom();
	return ostrm;
}

std::istream& Rational::InPut(std::istream& istrm) noexcept {
	int numerator, denominator;
	char delimiter;
	istrm >> numerator >> delimiter >> denominator;

	if (istrm.good()) {
		if (delimiter == delimiter_ && denominator > 0) {
			num_ = numerator;
			den_ = denominator;
			normalize();
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}

	return istrm;
}



int32_t gcd(int32_t a, int32_t b) {
	while (b) {
		int k = a;
		a = b;
		b = k % b;
	}
	return a;
}

void Rational::normalize() noexcept {
	if (num() < 0) {
		num_ = -num_;
		den_ = -den_;
	}

	int32_t g = gcd(num(), denom());

	num_ /= g;
	den_ /= g;
}



std::istream& operator>>(std::istream& istrm, Rational& rhs) noexcept {
	rhs.InPut(istrm);
	return istrm;
};

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) noexcept {
	rhs.OutPut(ostrm);
	return ostrm;
};