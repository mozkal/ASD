#include <iostream>
#include <vector>

#define INFINITY 1000000001 //10^9 + 1

int main() {
    long long n, m, price, price_back, product, i;
    std::vector<long long> products;
    std::vector<long long> prices;
    std::vector<long long> results;
    std::vector<long long> maxi_even, maxi_odd, mini_even, mini_odd;

    std::cin >> n;
    prices.reserve(n);
    maxi_odd.reserve(n);
    maxi_even.reserve(n);
    mini_even.reserve(n);
    mini_odd.reserve(n);
    for(i = 0; i < n; i++) {
        std::cin >> price;
        prices.push_back(price);
    }
    std::cin >> m;
    products.reserve(m);
    for(i = 0; i < m; i++) {
        std::cin >> product;
        products.push_back(product);
    }   
    long long curr_even, curr_odd, curr_even_back, curr_odd_back;
    curr_even = -1;
    curr_odd = -1;
    curr_even_back = INFINITY;
    curr_odd_back = INFINITY;   
    for(i = 0; i < n; i++) {
        price = prices.at(i);
        price_back = prices.at(n - 1 - i);

        if((price % 2) == 0)
            curr_even = price;
        else
            curr_odd = price;

        if((price_back % 2) == 0)
            curr_even_back = price_back;
        else
            curr_odd_back = price_back;

        maxi_odd.push_back(curr_odd);
        maxi_even.push_back(curr_even);
        mini_odd.push_back(curr_odd_back);
        mini_even.push_back(curr_even_back);
    }

    results.reserve(n);
    long long sum = 0, sum1, sum2, max_even, max_odd, min_even, min_odd;
    for(i = 0; i < n; i++) {
        price = prices.at(n - i - 1);
        sum += price;
        if(sum % 2 != 0)
            results.push_back(sum);
        else if(i == n - 1)
            results.push_back(-1);
        else {
            max_even = maxi_even.at(n - i - 2);
            max_odd = maxi_odd.at(n - i - 2);
            min_even = mini_even.at(i);
            min_odd = mini_odd.at(i);

            if(max_even > 0 && min_odd < INFINITY)
                sum1 = sum - min_odd + max_even;
            else
                sum1 = -1;
            if(max_odd > 0 && min_even < INFINITY)
                sum2 = sum - min_even + max_odd;
            else
                sum2 = -1;

            if(sum1 >= sum2)
                results.push_back(sum1);
            else
                results.push_back(sum2);
        }
    }

    for(long long product : products)
        std::cout << results.at(product - 1) << "\n";

    return 0;
}
