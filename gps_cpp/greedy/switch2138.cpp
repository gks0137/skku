#include <iostream>
#include <vector>
#include <string>
#include <span>

void turn_switch(int idx, std::vector<int>& lst) {
    for (int i=idx; i<idx+3; i++)
        lst[i] = lst[i]==0 ? 1 : 0;
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);



    int n;
    int min_count[2] = {100001, 100001};
    std::cin >> n;

    std::string line1, line2;

    std::cin >> line1;
    std::cin >> line2;

    //get values
    std::vector<int> list_cur(n), list_ans(n);
    for(int i = 0; i < n; i++) {
        list_cur[i] = 0;
        list_ans[i] = line1[i]==line2[i] ? 0 : 1;
    }


    //when n==2 or n==3
    if (n==2) {
        if (list_ans == std::vector<int>{0, 0}) std::cout << 0;
        else if (list_ans == std::vector<int>{1, 1}) std::cout << 1;
        else std::cout << -1;
        return 0;
    } else if (n==3)
    {
        if (list_ans == std::vector<int>{0, 0, 0}) std::cout << 0;
        else if (list_ans[1] == 0) std::cout << 2;
        else if (list_ans[0]==0 && list_ans[2]==0) std::cout << 3;
        else std::cout << 1;
        return 0;
    }
    

    //when n>=4
    for (int trial=0; trial<2; trial++) {
        int count = 0;
        if (trial == 1) {
            count = 1;
            for (int _=0; _<2; _++)
                list_ans[_] = list_ans[_]==0 ? 1 : 0;
            for (int _=0; _<n; _++)
                list_cur[_] = 0;
        }

        //until n-3
        for(int i = 0; i<n-3; i++) {
            if (list_cur[i] != list_ans[i]) {
                turn_switch(i, list_cur);
                count++;
            }
        }
        
        //get last 3
        std::vector<int> last3(3);
        for (int i=0; i<3; i++) {
            last3[i] = list_cur[i+n-3]==list_ans[i+n-3] ? 0 : 1;
        }

        if (last3 == std::vector<int>{0, 0, 0}) count+=0;
        else if (last3 == std::vector<int>{1, 1, 1}) count+=1;
        else if (last3 == std::vector<int>{0, 1, 1}) count+=1;
        else if (last3 == std::vector<int>{1, 0, 0}) count+=2;
        else {
            continue;
        }
        min_count[trial] = count;
        continue;
    }
    int min = std::min(min_count[0], min_count[1]);
    if (min == 100001) std::cout << -1;
    else std::cout << min;
    return 0;
}