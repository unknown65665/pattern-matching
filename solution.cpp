#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

using namespace std;

// To generate (a raise to power b) % q, here a and b are non-negative integers and q is a prime number
long long power(long long a, long long b, long long q) {
    if (b == 0)
        return 1;
    else {
        if (b % 2 == 0)
            return ((power(a, b / 2, q) % q) * (power(a, b / 2, q) % q)) % q;
        else
            return (a * (power(a, (b - 1) / 2, q) % q) * (power(a, (b - 1) / 2, q) % q)) % q;
    }
}

// To check if a number is prime
bool isPrime(long long q) {
    if (q > 1) {
        for (long long i = 2; i <= sqrt(q); ++i) {
            if (q % i == 0)
                return false;
        }
        return true;
    }
    return false;
}

// To generate random prime less than N
long long randPrime(long long N) {
    vector<long long> primes;
    for (long long q = 2; q <= N; ++q) {
        if (isPrime(q))
            primes.push_back(q);
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, primes.size() - 1);
    return primes[dis(gen)];
}

// Return appropriate N that satisfies the error bounds
long long findN(double eps, long long m) {
    eps = min(eps, 0.01);
    long long rootN = static_cast<long long>(11 * m / eps);
    return rootN * rootN;
}

// Return sorted list of starting indices where p matches x
vector<long long> modPatternMatch(long long q, const string& p, const string& x) {
    long long m = p.length();
    long long n = x.length();
    long long pow = power(26, m - 1, q);
    long long pmod = 0;
    long long xmod = 0;

    for (long long i = 0; i < m; ++i) {
        pmod = (26 * pmod + (p[i] - 'A')) % q;
        xmod = (26 * xmod + (x[i] - 'A')) % q;
    }

    vector<long long> ans;
    for (long long i = 0; i <= n - m; ++i) {
        if (pmod == xmod) {
            ans.push_back(i);
        }
        if (i + m < n) {
            xmod = (26 * (xmod - (x[i] - 'A') * pow) + (x[i + m] - 'A')) % q;
            if (xmod < 0) xmod += q;
        }
    }
    return ans;
}

// Return sorted list of starting indices where p matches x with wildcard
vector<long long> modPatternMatchWildcard(long long q, const string& p, const string& x) {
    long long m = p.length();
    long long n = x.length();
    long long wild_index = p.find('?');
    long long pow = power(26, m - 1, q);
    long long pmod = 0;
    long long xmod = 0;

    for (long long i = 0; i < m; ++i) {
        if (p[i] == '?') {
            pmod = (26 * pmod) % q;
            xmod = (26 * xmod) % q;
        } else {
            pmod = (26 * pmod + (p[i] - 'A')) % q;
            xmod = (26 * xmod + (x[i] - 'A')) % q;
        }
    }

    vector<long long> ans;
    long long pow2 = power(26, m - wild_index - 1, q);
    for (long long i = 0; i <= n - m; ++i) {
        if (pmod == xmod) {
            ans.push_back(i);
        }
        if (i + m < n) {
            xmod = (26 * (xmod + (x[i + wild_index] - 'A') * pow2 - (x[i] - 'A') * pow) + 
                    (x[i + m] - 'A') - (x[i + wild_index + 1] - 'A') * pow2) % q;
            if (xmod < 0) xmod += q;
        }
    }
    return ans;
}

// Pattern matching
vector<long long> randPatternMatch(double eps, const string& p, const string& x) {
    long long N = findN(eps, p.length());
    long long q = randPrime(N);
    return modPatternMatch(q, p, x);
}

// Pattern matching with wildcard
vector<long long> randPatternMatchWildcard(double eps, const string& p, const string& x) {
    long long N = findN(eps, p.length());
    long long q = randPrime(N);
    return modPatternMatchWildcard(q, p, x);
}

int main() {
    // Example usage
    vector<long long> result = modPatternMatchWildcard(1000000007, "?A", "ABCDE");
    for (long long index : result) {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}

