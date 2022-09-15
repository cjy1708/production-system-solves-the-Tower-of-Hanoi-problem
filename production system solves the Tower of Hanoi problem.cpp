// production system solves the Tower of Hanoi problem.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <thread>

#include "Pillar.h"

constexpr int DURATION_MS = 400;

void show_with_duration(const std::vector<hanoi::Pillar>& tower, size_t step);
std::vector<int> create_data(size_t size);
size_t hanoi_solution(size_t size, hanoi::Pillar& pillar1, hanoi::Pillar& pillar2, hanoi::Pillar& pillar3);

size_t SIZE;
size_t step_count{ };
std::vector<hanoi::Pillar> towers;


int main()
{
    std::cout << "请输入需要需要移动的盘数: ";
    std::cin >> SIZE;

    /*hanoi::Pillar pillar1{ "pillar 1", create_data(SIZE)};
    hanoi::Pillar pillar2{ "pillar 2" };
    hanoi::Pillar pillar3{ "pillar 3" };*/

    towers.emplace_back(hanoi::Pillar{ "pillar 1", create_data(SIZE) });
    towers.emplace_back(hanoi::Pillar{ "pillar 2" });
    towers.emplace_back(hanoi::Pillar{ "pillar 3" });

    show_with_duration(towers, step_count++);

    size_t result{ hanoi_solution(SIZE, towers[0],towers[1],towers[2])};
    std::cout << "共需要: " << std::setw(4) << result << " 步来完成" << std::endl;

    return 0;
}

void show_with_duration(const std::vector<hanoi::Pillar>& tower, size_t step)
{
    static const int _line_size{ static_cast<int>(SIZE) * 5 + 22 };

    using namespace std;

    system("cls");

    cout << "当前正在执行第" << setw(4) << step << " 步" << endl;

    cout << std::string(_line_size, '-') << endl;
    
    for (auto& pillar : tower)
    {
        cout << pillar << endl;
    }

    cout << std::string(_line_size, '-') << endl;


    std::this_thread::sleep_for(std::chrono::milliseconds(DURATION_MS));
}

std::vector<int> create_data(size_t size)
{
    int _size = static_cast<int>(size);
    std::vector<int> res(_size, 0);
    for (auto& num : res)
    {
        num = _size--;
    }

    return res;
}

size_t hanoi_solution(size_t size, hanoi::Pillar& pillar1, hanoi::Pillar& pillar2, hanoi::Pillar& pillar3)
{
    size_t q{ };
    size_t p{ };

    if (size == 1)
    {
        pillar1.move_one_plate_to(pillar3);
        show_with_duration(towers, step_count++);

        return 1;
    }
    else
    {
        q = hanoi_solution(size - 1, pillar1, pillar3, pillar2);
        pillar1.move_one_plate_to(pillar3);
        show_with_duration(towers, step_count++);
        p = hanoi_solution(size - 1, pillar2, pillar1, pillar3);
    }

    return q + p + 1;
}
