#include <iostream>
#include <vector>
#include <deque>

std::deque<std::vector<std::vector<int>>> papers;


bool is_paper_mixed(const std::vector<std::vector<int>>& paper) {
    int first = paper[0][0];
    for (const auto& row : paper) {
        for (int cell : row) {
            if (cell != first) {
                return true;
            }
        }
    }
    return false;
}

void cut_paper_4(const std::vector<std::vector<int>>& paper) {
    int n = paper.size();
    int half = n / 2;
    std::vector<std::vector<int>> top_left(half, std::vector<int>(half));
    std::vector<std::vector<int>> top_right(half, std::vector<int>(half));
    std::vector<std::vector<int>> bottom_left(half, std::vector<int>(half));
    std::vector<std::vector<int>> bottom_right(half, std::vector<int>(half));

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            top_left[i][j] = paper[i][j];
            top_right[i][j] = paper[i][j + half];
            bottom_left[i][j] = paper[i + half][j];
            bottom_right[i][j] = paper[i + half][j + half];
        }
    }

    papers.push_back(top_left);
    papers.push_back(top_right);
    papers.push_back(bottom_left);
    papers.push_back(bottom_right);
}



int main() {    
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(NULL);
    // std::cout.tie(NULL);

    int n;
    std::cin >> n;
    papers.push_back(std::vector<std::vector<int>>(n, std::vector<int>(n, 0)));

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            std::cin >> papers[0][i][j];
        }
    }

    int paper_perfect_count_0 = 0;
    int paper_perfect_count_1 = 0;

    while (!papers.empty()) {
        auto paper = papers.front();
        papers.pop_front();

        // std::cout << "paper size: " << paper.size() << "\n";

        if (is_paper_mixed(paper)) {
            cut_paper_4(paper);
        } else {
            if (paper[0][0] == 0) {
                paper_perfect_count_0++;
            } else {
                paper_perfect_count_1++;
            }
        }
    }


    

    std::cout << paper_perfect_count_0 << "\n" << paper_perfect_count_1 << "\n";

    





    return 0;
}