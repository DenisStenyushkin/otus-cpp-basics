// Read files and prints top k word by frequency with parallel computations

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <vector>
#include <chrono>

const size_t TOPK = 10;

using Counter = std::unordered_map<std::string, std::size_t>;

std::string tolower(const std::string &str);

Counter count_words(const std::string& file_name);

void print_topk(std::ostream& stream, const Counter&, const size_t k);


Counter& operator+=(Counter& lhs, const Counter& rhs) {
    for (auto iter = rhs.cbegin(); iter != rhs.cend(); ++iter) {
        if (lhs[iter->first]) {
            lhs[iter->first] += iter->second;
        }
        else {
            lhs[iter->first] = iter->second;
        }
    }
    return lhs;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: topk_words [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::future<Counter>> tasks;
    
    for (int i = 1; i < argc; ++i) {
        tasks.push_back(std::async(std::launch::async, count_words, argv[i]));
    }

    Counter freq_dict;
    for (std::future<Counter>& t : tasks) {
        freq_dict += t.get();
    }

    print_topk(std::cout, freq_dict, TOPK);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

std::string tolower(const std::string &str) {
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch) { return std::tolower(ch); });
    return lower_str;
}

Counter count_words(const std::string& file_name) {
    std::ifstream input{file_name};
        if (!input.is_open()) {
            throw std::runtime_error("Failed to open file " + file_name + "\n");
        }
    
    Counter counter;
    std::for_each(std::istream_iterator<std::string>(input),
                  std::istream_iterator<std::string>(),
                  [&counter](const std::string &s) { ++counter[tolower(s)]; });
    return counter;
}

void print_topk(std::ostream& stream, const Counter& counter, const size_t k) {
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it) {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + k, std::end(words),
        [](auto lhs, auto &rhs) { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + k,
        [&stream](const Counter::const_iterator &pair) {
            stream << std::setw(4) << pair->second << " " << pair->first
                      << '\n';
        });
}
