export module test;

import <string>;
import <algorithm>;
import <numeric>;
import <cassert>;
import xorlist;

export void constructor() {
	xorlist<std::string> words1{"the", "frogurt", "is", "also", "cursed"};

	xorlist<std::string> words2(words1.begin(), words1.end());

	xorlist<std::string> words3(words1);

	xorlist<std::string> words4(5, "Mo");
}

export void destructor() {
	xorlist<std::string>().~xorlist();
}

export void operator_assign() {
	xorlist<int> x{1, 2, 3}, y, z;
	const auto w = {4, 5, 6, 7};

	y = x;
	assert(!x.empty());
	assert(x == y);

	z = std::move(x);
	assert(z.size() == 3);
	assert(x.empty());

	z = w;
	assert(z.size() == 4);
}

export void assign() {
	xorlist<char> characters;

	characters.assign(5, 'a');

	assert(std::all_of(characters.begin(), characters.end(), [](auto e) { e == 'a'; }));
	assert(characters.size() == 5);

	const std::string extra(6, 'b');

	assert(std::all_of(characters.begin(), characters.end(), [](auto e) { e == 'b'; }));
	assert(characters.size() == 6);

	characters.assign({'C', '+', '+', '1', '1'});
	assert(characters.front() == 'C' && characters.back() == '1');
	assert(characters.size() == 5);
}

export void get_allocator() {
	xorlist<char, std::allocator<char>()> letters{};

	assert(letters.get_allocator() == std::allocator<char>());
}

// Element access

export void front() {
	xorlist<char> letters{'o', 'm', 'g', 'w', 't', 'f'};

	assert(!letters.empty() && letters.back() == 'o');
}

export void back() {
	xorlist<char> letters{'a', 'b', 'c', 'd', 'e', 'f'};

	assert(!letters.empty()  && letters.back() == 'f');
}

// Iterators

export void begin_cbegin() {
	xorlist<int> nums{1, 2, 4, 8, 16};
	xorlist<std::string> fruits{"orange", "apple", "raspberry"};
	xorlist<char> empty;

	assert(std::accumulate(nums.begin(), nums.end(), 0) == 31);
	assert(!fruits.empty()  && *fruits.begin() == "orange");
	assert(empty.begin() == empty.end());
}

export void end_cend() {
	xorlist<int> nums{1, 2, 4, 8, 16};
	xorlist<std::string> fruits{"orange", "apple", "raspberry"};
	xorlist<char> empty;

	assert(std::accumulate(nums.begin(), nums.end(), 0) == 31);
	assert(!fruits.empty() && *fruits.end() == "raspberry");
	assert(empty.begin() == empty.end());
}

export void rbegin_crbegin() {
	xorlist<int> nums{1, 2, 4, 8, 16};
	xorlist<std::string> fruits{"orange", "apple", "raspberry"};
	xorlist<char> empty;

	assert(std::accumulate(nums.rbegin(), nums.rend(), 0) == 31);
	assert(!fruits.empty() && *fruits.rbegin() == "raspberry");
	assert(empty.rbegin() == empty.rend());
}

export void rend_crend() {
	xorlist<int> nums{1, 2, 4, 8, 16};
	xorlist<std::string> fruits{"orange", "apple", "raspberry"};
	xorlist<char> empty;

	assert(std::accumulate(nums.rbegin(), nums.rend(), 0) == 31);
	assert(!fruits.empty() && *fruits.rend() == "orange");
	assert(empty.rbegin() == empty.rend());
}

// Capacity

export void empty() {
	xorlist<int> numbers;

	assert(numbers.empty());

	numbers.push_back(42);
	numbers.push_back(13317);

	assert(!numbers.empty());
}

export void size() {
	xorlist<int> nums{1, 3, 5, 7};

	assert(nums.size() == 4);
}

export void max_size() {
	assert(xorlist<char>().max_size() == std::numeric_limits<std::ptrdiff_t>::max());
}

// Modifiers

export void clear() {
	xorlist<int> container{1, 2, 3};

	assert(container.size() == 3);

	container.clear();

	assert(container.empty());
}

export void insert() {
	xorlist<int> c1(3, 100);
	assert(std::all_of(c1.begin(), c1.end(), [](auto e) { e == 100; }));
	assert(c1.size() == 3);

	auto it = c1.begin();
	assert(c1.front() == 200 && std::all_of(c1.begin()++, c1.end(), [](auto e) { e == 100; }));
	assert(c1.size() == 4);

	c1.insert(it, 2, 300);
	assert(c1.front() == 300 && c1.back() == 100);
	assert(c1.size() == 6);

	// reset `it` to the begin:
	it = c1.begin();

	xorlist<int> c2(2, 400);
	c1.insert(std::next(it, 2), c2.begin(), c2.end());
	assert(c1.front() == 300 && c1.back() == 100);
	assert(c1.size() == 8);

	int arr[] = {501, 502, 503};
	c1.insert(c1.begin(), arr, arr + std::size(arr));
	assert(c1.front() == 501 && c1.back() == 100);
	assert(c1.size() == 11);

	c1.insert(c1.end(), {601, 602, 603});
	assert(c1.front() == 501 && c1.back() == 603);
	assert(c1.size() == 14);
}

export void emplace() {
	struct A {
		std::string s;

		A(std::string str) : s(std::move(str)) {  }
		A(const A &o) : s(o.s) {  }
		A(A &&o) : s(std::move(o.s)) { }
		A &operator=(const A &other) {
			s = other.s;
			return *this;
		}
		A &operator=(A &&other) {
			s = std::move(other.s);
			return *this;
		}
	};

	xorlist<A> container;

	A two{"two"};
	A three{"three"};

	container.emplace(container.end(), "one");

	container.emplace(container.end(), two);

	container.emplace(container.end(), std::move(three));

	assert(container.size() == 3);
	assert(container.front().s == "one");
	assert(container.back().s == "three");
}

export void erase() {
	xorlist<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

	c.erase(c.begin());
	unsigned int acc = 0;
	assert(std::all_of(c.begin(), c.end(), [](auto e) { e == ++acc; }));

	xorlist<int>::iterator range_begin = c.begin();
	xorlist<int>::iterator range_end = c.begin();
	std::advance(range_begin, 2);
	std::advance(range_end, 5);

	c.erase(range_begin, range_end);
	assert(c == xorlist<int>({1, 2, 6, 7, 8, 9}));

	// Erase all even numbers
	for (xorlist<int>::iterator it = c.begin(); it != c.end();)
		if (*it % 2 == 0)
			it = c.erase(it);
		else
			++it;

	assert(c == xorlist<int>({1,7, 9}));
}

export void push_back() {
	xorlist<std::string> letters;

	letters.push_back("abc");
	std::string s{"def"};
	letters.push_back(std::move(s));

	assert(letters.front() == "abc" && letters.back() == "def");
	assert(s.empty());
}

export void emplace_back() {
	struct President {
		std::string name;
		std::string country;
		int year;

		President(std::string p_name, std::string p_country, int p_year)
			: name(std::move(p_name)), country(std::move(p_country)), year(p_year) {}
		President(President &&other)
			: name(std::move(other.name)), country(std::move(other.country)), year(other.year) {}
		President &operator=(const President &other) = default;
	};

	xorlist<President> elections;

	auto &ref = elections.emplace_back("Nelson Mandela", "South Africa", 1994);

	assert(ref.year == 1994 && elections.size() == 1);
}

export void pop_back() {
	xorlist<int> numbers;

	numbers.push_back(5);
	numbers.push_back(3);
	numbers.push_back(4);

	assert(numbers.size() == 3 && numbers.back() == 4);

	numbers.pop_back();

	assert(numbers.size() == 2 && numbers.back() == 3);
}

export void push_front() {
	xorlist<std::string> letters;

	letters.push_front("abc");
	std::string s{"def"};
	letters.push_front(std::move(s));

	assert(letters.front() == "def" && letters.back() == "abc");
	assert(s.empty());
}

export void emplace_front() {
	struct President {
		std::string name;
		std::string country;
		int year;

		President(std::string p_name, std::string p_country, int p_year)
			: name(std::move(p_name)), country(std::move(p_country)), year(p_year) {}
		President(President &&other)
			: name(std::move(other.name)), country(std::move(other.country)), year(other.year) {}
		President &operator=(const President &other) = default;
	};

	xorlist<President> elections;

	auto &ref = elections.emplace_front("Nelson Mandela", "South Africa", 1994);

	assert(ref.year == 1994 && elections.size() == 1);
}

export void pop_front() {
	xorlist<char> chars{'A', 'B', 'C', 'D'};

	assert(chars.size() == 4 && chars.front() == 'A');

	chars.pop_front();

	assert(chars.size() == 3 && chars.front() == 'B');
}

export void resize() {
	xorlist<int> c = {1, 2, 3};

	c.resize(5);

	assert(c == xorlist<int>({1, 2, 3, 0, 0}));

	c.resize(2);

	assert(c == xorlist<int>({1, 2}));

	c.resize(6, 4);

	assert(c == xorlist<int>({1, 2, 4, 4, 4, 4}));
}

export void swap() {
	xorlist<int> a1{1, 2, 3}, a2{4, 5};

	auto it1 = std::next(a1.begin());
	auto it2 = std::next(a2.begin());

	int &ref1 = a1.front();
	int &ref2 = a2.front();

	assert(a1 == xorlist<int>({1, 2, 3}) && a2 == xorlist<int>({4, 5}));
	assert(*it1 == 2 && *it2 == 5 && ref1 == 1 && ref2 == 4);

	a1.swap(a2);

	assert(a1 == xorlist<int>({4, 5}) && a2 == xorlist<int>({1, 2, 3}));
	assert(*it1 == 2 && *it2 == 5 && ref1 == 1 && ref2 == 4);
}

// Operations

export void merge() {
	xorlist<int> list1 = {5, 9, 1, 3, 3};
	xorlist<int> list2 = {8, 7, 2, 3, 4, 4};

	list1.sort();
	list2.sort();

	list1.merge(list2);
	assert(list1 == xorlist<int>({1, 2, 3, 3, 3, 4, 4, 5, 7, 8, 9}));
}

export void splice() {
	xorlist<int> list1 = {1, 2, 3, 4, 5};
	xorlist<int> list2 = {10, 20, 30, 40, 50};

	auto it = list1.begin();
	std::advance(it, 2);

	list1.splice(it, list2);

	assert(list1 == xorlist<int>({1, 2, 10, 20, 30, 40, 50, 3, 4, 5}) && list2.empty());

	list2.splice(list2.begin(), list1, it, list1.end());

	assert(list1 == xorlist<int>({1, 2, 10, 20, 30, 40, 50}) && list2 == xorlist<int>({3, 4, 5}));
}

export void remove() {
	xorlist<int> l = {1, 100, 2, 3, 10, 1, 11, -1, 12};

	auto count1 = l.remove(1);
	assert(l == xorlist<int>({100, 2, 3, 10, 11, -1, 12}));

	auto count2 = l.remove_if([](int n) { return n > 10; });
	assert(l == xorlist<int>({2, 3, 10, -1}));
}

export void reverse() {
	xorlist<int> list = {8, 7, 5, 9, 0, 1, 3, 2, 6, 4};

	list.reverse();

	assert(list == xorlist<int>({9, 8, 7, 6, 5, 4, 3, 2, 1, 0}));
}

export void unique() {
	xorlist<int> c = {1, 2, 2, 3, 3, 2, 1, 1, 2};

	const auto count1 = c.unique();

	assert(c == xorlist<int>({1, 2, 3, 2, 1, 2}) && count1 == 3);

	c = {1, 2, 12, 23, 3, 2, 51, 1, 2, 2};
	const auto count2 = c.unique([mod = 10](int x, int y) { return (x % mod) == (y % mod); });

	assert(c == xorlist<int>({1, 2, 23, 2, 51, 2}) && count2 == 4);
}

export void sort() {
	xorlist<int> list = {8, 7, 5, 9, 0, 1, 3, 2, 6, 4};

	list.sort();

	assert(list == xorlist<int>({0, 1, 2, 3, 4, 5, 6, 7, 8, 9}));
}

export void operator_equivalent_threeway_comparison() {
	xorlist<int> alice{1, 2, 3};
	xorlist<int> bob{7, 8, 9, 10};
	xorlist<int> eve{1, 2, 3};

	// Compare non equal containers
	assert(!(alice == bob));
	assert(alice != bob);
	assert(alice < bob);
	assert(alice <= bob);
	assert(!(alice > bob));
	assert(!(alice >= bob));

	// Compare equal containers
	assert(alice == eve);
	assert(!(alice != eve));
	assert(!(alice < eve));
	assert(alice <= eve);
	assert(!(alice > eve));
	assert(alice >= eve);
}

export void algorithm_swap() {
	xorlist<int> alice{1, 2, 3};
	xorlist<int> bob{7, 8, 9, 10};

	std::swap(alice, bob);

	assert(alice == xorlist<int>({7, 8, 9, 10}));
	assert(bob == xorlist<int>({1, 2, 3}));
}

export void erase_erase_if() {
	xorlist<char> cnt(10);
	std::iota(cnt.begin(), cnt.end(), '0');

	std::erase(cnt, '3');
	assert(cnt == xorlist<int>({0, 1, 2, 4, 5, 6, 7, 8, 9}));

	auto erased = std::erase_if(cnt, [](char x) { return (x - '0') % 2 == 0; });

	assert(cnt == xorlist<int>({1, 5, 7, 9}) && erased == 5);
}
