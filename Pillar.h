#pragma once

#include <stack>
#include <string>
#include <ostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

namespace hanoi
{
	class Pillar
	{
		std::stack<int> store;
		std::string name;

	public:
		Pillar() = default;
		Pillar(std::string name);
		Pillar(std::string name, std::vector<int> start_plates);

		const std::string& get_name() const;
		const std::stack<int>& get_store() const;

		void move_one_plate_to(Pillar& other);

	private:
		void add_plate(int plate_num);
		int get_plate();
	};
}


std::ostream& operator<<(std::ostream& stream, const hanoi::Pillar& pillar);