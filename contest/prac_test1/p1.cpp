#include <iostream>
#include <deque>
#include <vector>

int main() {
  int n, m;
  std::cin >> n >> m;
  std::deque<std::vector<int>> items(m); 

  for (int i=0; i<m; i++) {
    std::string _;
    int a, b;
    std::cin >> _ >> a >> b;
    items[i] = {a, b};
  }

  int count=0;
  while (1)
  {
    count ++;

    for (int i=0; i<n; i++) {
        items.front().front() -= 64 / items.front().back();

        if (items.front().front() <= 0) {
            items.pop_front();
        }

        if (items.empty()) {
            std::cout << count;
            return 0;

        }
    }

  }
  

}