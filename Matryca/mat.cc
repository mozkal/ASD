#include <iostream>
#include <string>

int main() {
    long i, l, min_l, n;
    char curr, prev;
    std::string napis;

    std::cin >> napis;
    n = napis.length();

    //ostatni znak różny od '*'
    prev = '#';
    l = 0;
    min_l = n;
    for(i = 0; i < napis.length(); i++) {
        curr = napis.at(i);
        if(curr == '*') {
            ++l;
        }
        else if(curr == prev || prev == '#') {
            l = 0;
            prev = curr;
        } else {
            ++l;
            if(l < min_l)
                min_l = l;
            l = 0;
            prev = curr;
        }
    }

    std::cout << napis.length() - min_l + 1 ;
    
    return 0;
}
