#include <iostream>
#include <map>
#include <vector>

int main()
{
	std::map<std::string, int> m;
	std::vector<int> a;

	
	m["e"] = 123;

	m.insert(std::pair<std::string, int>("a", 42));
	m.insert(std::pair<std::string, int>("c", 1));
	m.insert(std::pair<std::string, int>("b", 21));
	m.insert(std::pair<std::string, int>("A", 2));

	std::map<std::string, int>::iterator it;

	std::cout << m.equal_range("A").first->first << std::endl;
		std::cout << m.equal_range("A").second->first << std::endl;

	std::cout << m.upper_bound("A")->first << std::endl;
	std::cout << m.size() << std::endl;
	for (it = m.begin(); it != m.end(); it++)
	{
		std::cout << it->first << " " << it->second << std::endl;
	}

}
