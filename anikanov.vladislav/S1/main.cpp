#include <iostream>
#include <cstring>
#include <memory>
#include "list.hpp"


/*
first 1 1 1
second 2 2 2 2
third
fourth 4 4
*/


int main()
{
  using namespace anikanov;

  std::unique_ptr< List< std::pair< char[51], List< int > > > > lists(new List< std::pair< char[51], List< int > > >);
  char input_name[51];
  int number;

  while (true) {

    if (!(std::cin >> input_name)) {
      break;
    }

    List< int > numbers;
    while (std::cin.peek() != '\n' && std::cin >> number) {
      numbers.push_back(number);
    }

    std::pair< char[51], List< int > > list_pair;
    std::strcpy(list_pair.first, input_name);
    list_pair.second = numbers;
    lists->push_back(list_pair);

    if (std::cin.eof()) { break; }
  }

  for (auto it = lists->begin(); it != lists->end(); ++it) {
    std::cout << it->first << " ";
  }
  std::cout << "\n";

  if (lists->empty()) {
    std::cout << "0\n";
    return 1;
  }

  bool finished = false;
  size_t idx = 0;
  List< int > sums;
  while (!finished) {
    finished = true;
    sums.push_back(0);
    for (auto list_it = lists->begin(); list_it != lists->end(); ++list_it) {
      const auto &list = *list_it;
      if (idx < list.second.size()) {
        auto num_it = list.second.begin();
        for (int i = 0; i < (idx == 0 ? 0 : idx - 1); ++i) {
          num_it++;
        }
        std::cout << *num_it << " ";
        *sums.back() += *num_it;
        finished = false;
      }
    }
    std::cout << (finished ? "" : "\n");
    idx++;
  }

  for (auto sum_it = sums.begin(); sum_it != sums.end(); ++sum_it) {
    if (sum_it != sums.back()) {
      std::cout << *sum_it << " ";
    }
  }

  std::cout << "\n";
  return 0;
}
