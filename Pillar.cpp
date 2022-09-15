#include "Pillar.h"

namespace hanoi
{
	Pillar::Pillar(std::string name)
	{
		this->name = std::move(name);
	}

	Pillar::Pillar(std::string name, std::vector<int> start_plates) : Pillar{std::move(name)}
	{
		if (!std::is_sorted(start_plates.begin(), start_plates.end(), std::greater<int>()))
		{
			throw std::logic_error("输入的数据必须是从小到大排列好");
		}

		for (size_t i{ }; i < start_plates.size(); ++i)
		{
			this->store.emplace(start_plates[i]);
		}
	}
	const std::string& Pillar::get_name() const
	{
		return this->name;
	}
	const std::stack<int>& Pillar::get_store() const
	{
		return this->store;
	}
	void Pillar::move_one_plate_to(Pillar& other)
	{
		if (this->store.empty())
		{
			throw std::out_of_range("当前柱子为空，没有盘子可以移动");
		}

		auto plate{ this->get_plate() };
		other.add_plate(plate);
	}

	void Pillar::add_plate(int plate_num)
	{
		if (!this->store.empty() && this->store.top() <= plate_num) {
			throw std::logic_error("不能将大盘子" + std::to_string(plate_num) +
				"移动到小盘子" + std::to_string(this->store.top()) + "上");
		}

		this->store.push(plate_num);
	}

	int Pillar::get_plate()
	{
		if (this->store.empty())
		{
			throw std::out_of_range("当前柱子没有盘子，不能获取盘子");
		}

		int res{ this->store.top() };
		this->store.pop();

		return res;
	}
}

std::ostream& operator<<(std::ostream& stream, const hanoi::Pillar& pillar)
{
	stream << "|" << std::setw(8) << pillar.get_name() << " |";

	auto temp_store{ pillar.get_store() };

	std::vector<int> store(temp_store.size(), 0);

	for (size_t i{ }, size{ store.size() }; i < size; ++i)
	{
		store[size - i - 1] = temp_store.top();
		temp_store.pop();
	}

	for (auto& plate : store)
	{
		stream << std::setw(3) << plate;
	};

	return stream;
}