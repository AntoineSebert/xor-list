/*
 * https://en.cppreference.com/w/cpp/container/list
 * https://en.wikipedia.org/wiki/XOR_linked_list
 */
export module xorlist;

import <cstddef>;

import <algorithm>;
import <iterator>;
import <limits>;
import <memory>;
import <stdexcept>;
import <type_traits>;
import <utility>;

/**
 - [x] list() noexcept(is_nothrow_default_constructible<allocator_type>::value);
 - [x] explicit list(const allocator_type& a);
 - [a] explicit list(size_type n);
 - [x] explicit list(size_type n, const allocator_type& a); // C++14
 - [a] list(size_type n, const value_type& value);
 - [x] list(size_type n, const value_type& value, const allocator_type& a);
 - [a] template <class Iter> list(Iter first, Iter last);
 - [x] template <class Iter> list(Iter first, Iter last, const allocator_type& a);
 - [x] list(const list& x);
 - [x] list(const list&, const allocator_type& a);
 - [x] list(list&& x) noexcept(is_nothrow_move_constructible<allocator_type>::value);
 - [x] list(list&&, const allocator_type& a);
 - [a] list(initializer_list<value_type>);
 - [x] list(initializer_list<value_type>, const allocator_type& a);
 - [x] ~list();
 - [x] list& operator=(const list& x);
 - [x] list& operator=(list&& x) noexcept(allocator_type::propagate_on_container_move_assignment::value &&
 is_nothrow_move_assignable<allocator_type>::value);
 - [x] list& operator=(initializer_list<value_type>);
 - [x] template <class Iter> void assign(Iter first, Iter last);
 - [x] void assign(size_type n, const value_type& t);
 - [x] void assign(initializer_list<value_type>);
 - [x] allocator_type get_allocator() const noexcept;
 */
/**
 - [x] reference front();
 - [x] const_reference front() const;
 - [x] reference back();
 - [x] const_reference back() const;
 */
/**
 - [x] iterator begin() noexcept;
 - [x] const_iterator begin() const noexcept;
 - [x] const_iterator cbegin() const noexcept;
 - [x] iterator end() noexcept;
 - [x] const_iterator end() const noexcept;
 - [x] const_iterator cend() const noexcept;
 - [x] reverse_iterator rbegin() noexcept;
 - [x] const_reverse_iterator rbegin() const noexcept;
 - [x] const_reverse_iterator crbegin() const noexcept;
 - [x] reverse_iterator rend() noexcept;
 - [x] const_reverse_iterator rend() const noexcept;
 - [x] const_reverse_iterator crend() const noexcept;
 */
/**
 - [x] bool empty() const noexcept;
 - [x] size_type size() const noexcept;
 - [x] size_type max_size() const noexcept;
 */
/**
 - [ ] void clear() noexcept;
 - [ ] iterator insert(const_iterator position, const value_type& x);
 - [ ] iterator insert(const_iterator position, value_type&& x);
 - [ ] iterator insert(const_iterator position, size_type n, const value_type& x);
 - [ ] template <class Iter> iterator insert(const_iterator position, Iter first, Iter last);
 - [x] iterator insert(const_iterator position, initializer_list<value_type> il);
 - [ ] template <class... Args> iterator emplace(const_iterator position, Args&&... args);
 - [ ] iterator erase(const_iterator position);
 - [ ] iterator erase(const_iterator position, const_iterator last);
 - [ ] void push_back(const value_type& x);
 - [ ] void push_back(value_type&& x);
 - [ ] template <class... Args> reference emplace_back(Args&&... args);  // reference in C++17
 - [ ] void pop_back();
 - [ ] void push_front(const value_type& x);
 - [ ] void push_front(value_type&& x);
 - [ ] template <class... Args> reference emplace_front(Args&&... args); // reference in C++17
 - [ ] void pop_front();
 - [ ] void resize(size_type sz);
 - [ ] void resize(size_type sz, const value_type& c);
 - [ ] void swap(list&) noexcept(allocator_traits<allocator_type>::is_always_equal::value);  // C++17
 */
/**
 - [x] void merge(list& x);
 - [x] void merge(list&& x);
 - [ ] template <class Compare> void merge(list& x, Compare comp);
 - [x] template <class Compare> void merge(list&& x, Compare comp);
 - [ ] void splice(const_iterator position, list& x);
 - [x] void splice(const_iterator position, list&& x);
 - [ ] void splice(const_iterator position, list& x, const_iterator i);
 - [x] void splice(const_iterator position, list&& x, const_iterator i);
 - [ ] void splice(const_iterator position, list& x, const_iterator first, const_iterator last);
 - [x] void splice(const_iterator position, list&& x, const_iterator first, const_iterator last);
 - [x] size_type remove(const value_type& value);
 - [x] template <class Pred> size_type remove_if(Pred pred);
 - [x] void reverse() noexcept;
 - [x] size_type unique();
 - [x] template <class BinaryPredicate> size_type unique(BinaryPredicate binary_pred);
 - [x] void sort();
 - [ ] template <class Compare> void sort(Compare comp);
 */
/*
 - [x] template<class T, class Alloc> bool operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs);
 - [x] template<class T, class Alloc> operator<=>(const list<T, Alloc> &lhs, const list<T, Alloc> &rhs);
 - [x] template<class T, class Alloc> void swap(list<T, Alloc>& lhs, list<T, Alloc>& rhs) noexcept;
 - [x] template<class T, class Alloc, class U> typename list<T, Alloc>::size_type erase(list<T, Alloc>& c, const U&
 value);
 - [x] template<class T, class Alloc, class Pred> typename list<T, Alloc>::size_type erase_if(list<T, Alloc>& c, Pred
 pred);
*/
/*
 - [x] template<class InputIt, class Alloc = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
 list(InputIt, InputIt, Alloc = Alloc()) -> list<typename std::iterator_traits<InputIt>::value_type, Alloc>;
*/

export template <typename T, class Allocator = std::allocator<T>> class xorlist {
  public:
	using size_type = std::allocator_traits<Allocator>::size_type;
	using allocator_type = Allocator;

  protected:
	// Member types
	using value_type = T;
	using difference_type = std::ptrdiff_t;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = std::allocator_traits<Allocator>::pointer;
	using void_pointer = std::allocator_traits<Allocator>::void_pointer;
	using const_pointer = std::allocator_traits<Allocator>::const_pointer;
	// iterator
	// https://gist.github.com/jeetsukumaran/307264
  public:
	class iterator {
	  private:
		pointer ptr;

	  public:
		using iterator_category = std::forward_iterator_tag;

		iterator() noexcept : ptr() {}
		iterator(pointer ptr) : ptr(ptr) {}
		[[nodiscard]] reference operator*() const noexcept { return *ptr; }
		[[nodiscard]] pointer operator->() const noexcept { return std::pointer_traits<pointer>::pointer_to(**this); }
		auto operator++() {
			ptr++;
			return *this;
		}
		auto operator++(int) {
			auto tmp = *this;
			++(*this);
			return tmp;
		}
		auto operator--() {
			ptr--;
			return *this;
		}
		auto operator--(int) {
			auto tmp = *this;
			--(*this);
			return tmp;
		}
		bool operator==(const iterator &rhs) const { return ptr == rhs.ptr; };
	};

	class const_iterator {
	  private:
		pointer ptr;

	  public:
		using iterator_category = std::forward_iterator_tag;

		const_iterator() noexcept : ptr() {}
		const_iterator(pointer ptr) : ptr(ptr) {}
		const_reference operator*() const noexcept { return ptr; }
		const_pointer operator->() const noexcept { return std::pointer_traits<pointer>::pointer_to(**this); }
		auto operator++() {
			auto tmp = *this;
			++(*this);
			return tmp;
		}
		auto operator++(int) {
			ptr++;
			return *this;
		}
		auto operator--() {
			ptr--;
			return *this;
		}
		auto operator--(int) {
			auto tmp = *this;
			--(*this);
			return tmp;
		}
		bool operator==(const const_iterator &rhs) { return ptr == rhs.ptr; }
	};
	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  private:
	// node
	template <class T> struct _node;
	using __alloc_traits = std::allocator_traits<allocator_type>;
	using __node_allocator = typename __alloc_traits::template rebind_alloc<_node<T>>;
	using __node_alloc_traits = std::allocator_traits<__node_allocator>;
	using __node_pointer = typename __node_alloc_traits::pointer;
	std::pair<size_type, __node_allocator> __size_alloc_;
	__node_allocator &__node_alloc() noexcept { return __size_alloc_.second; }
	const __node_allocator &__node_alloc() const noexcept { return __size_alloc_.second; }

	template <class T> struct _node {
		using __node_pointer = typename std::pointer_traits<void_pointer>::template rebind<_node<T>>;
		__node_pointer _link;
		T _value;

		_node() : _link(_self()) {}

		__node_pointer _self() { return std::pointer_traits<__node_pointer>::pointer_to(*this); }

		__node_pointer _as_node() { return static_cast<__node_pointer>(_self()); }

		__node_pointer _as_link() { return static_cast<__node_pointer>(_self()); }
	};

	pointer front0 = nullptr, front1 = nullptr, back0 = nullptr, back1 = nullptr;
	Allocator alloc;
	size_type _size{};
	_node<value_type> _end;

	/* Member functions */

  public:
	/**
	 * Default constructor. Constructs an empty container with a default-constructed allocator.
	 * Complexity: Constant
	 */
	xorlist() noexcept(std::is_nothrow_default_constructible_v<__node_allocator>) {}

	/**
	 * Constructs an empty container with the given allocator `alloc`.
	 * Parameters:
	 *   - alloc: allocator to use for all memory allocations of this container
	 * Complexity: Constant
	 */
	explicit xorlist(const allocator_type &alloc) : alloc(alloc) {}

	/**
	 * Constructs the container with count copies of elements with value value.
	 * Parameters:
	 *   - count: the size of the container
	 *   - value: the value to initialize elements of the container with
	 * Complexity: Linear in `count`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	xorlist(size_type count, const value_type &value, const Allocator &alloc = Allocator()) : alloc(alloc) {
		for (; count > 0; --count)
			push_back(value);
	}

	/**
	 * Constructs the container with `count`
	 * [default-inserted](https://en.cppreference.com/w/cpp/named_req/DefaultInsertable). No copies are made.
	 * Parameters:
	 *   - alloc: allocator to use for all memory allocations of this container
	 *   - count: the size of the container
	 *   - value: the value to initialize elements of the container with
	 * Complexity: Linear in `count`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	explicit xorlist(size_type count, const Allocator &alloc = Allocator()) : alloc(alloc) {
		for (; count > 0; --count)
			emplace_back();
	}

	/**
	 * Constructs the container with the contents of the range `[first, last)`. This overload participates in overload
	 * resolution only if `InputIt` satisfies
	 * [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator), to avoid ambiguity with the
	 * overload. Parameters:
	 *   - alloc: allocator to use for all memory allocations of this container
	 *   - first, last: the range to copy the elements from
	 * Complexity: Linear in distance between `first` and `last`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	template <class InputIt /*, std::enable_if_t<std::iterator_traits<InputIt>::value, bool> = true */>
	xorlist(InputIt first, InputIt last, const Allocator &alloc = Allocator()) : alloc(alloc) {
		for (; first != last; ++first)
			emplace_back(*first);
	}

	/**
	 * Copy constructor. Constructs the container with the copy of the contents of `other`. The allocator is obtained as
	 * if by calling
	 * `[std::allocator_traits](http://en.cppreference.com/w/cpp/memory/allocator_traits)<allocator_type>::select_on_container_copy_construction(other.get_allocator())`.
	 * Parameters:
	 *   - other: another container to be used as source to initialize the elements of the container with
	 * Complexity: Linear in size of `other`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	xorlist(const xorlist &other) {
		for (const_iterator i = other.begin(), e = other.end(); i != e; ++i)
			push_back(*i);
	}

	/**
	 * Constructs the container with the copy of the contents of `other`, using `alloc` as the allocator. The template
	 * parameter `Allocator` is only deduced from the first argument while used in [class template argument
	 * deduction](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction). Parameters:
	 *   - other: another container to be used as source to initialize the elements of the container with
	 *   - alloc: allocator to use for all memory allocations of this container
	 * Complexity: Linear in size of `other`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	xorlist(const xorlist &other, const Allocator &alloc) : alloc(alloc) {
		for (const_iterator i = other.begin(), e = other.end(); i != e; ++i)
			push_back(*i);
	}

	/**
	 * Move constructor. Constructs the container with the contents of `other` using move semantics. Allocator is
	 * obtained by move-construction from the allocator belonging to `other`. Parameters:
	 *   - other: another container to be used as source to initialize the elements of the container with
	 * Complexity: Constant Exceptions: Calls to `Allocator::allocate` may throw.
	 * Notes:
	 * After container move construction, references, pointers, and iterators (other than the end iterator) to other
	 * remain valid, but refer to elements that are now in `*this`. The current standard makes this guarantee via the
	 * blanket statement in [[container.rev.reqmts]/17](http://eel.is/c++draft/container.rev.reqmts#17), and a more
	 * direct guarantee is under consideration via [LWG 2321](https://cplusplus.github.io/LWG/issue2321).
	 */
	xorlist(xorlist &&other) noexcept(std::is_nothrow_move_constructible<T>::value) { splice(end(), other); }

	/**
	 * Allocator-extended move constructor. Using alloc as the allocator for the new container, moving the contents from
	 * other; if `alloc != other.get_allocator()`, this results in an element-wise move. The template parameter
	 * `Allocator` is only deduced from the first argument while used in [class template argument
	 * deduction](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction). Parameters:
	 *   - other: another container to be used as source to initialize the elements of the container with
	 *   - alloc: allocator to use for all memory allocations of this container
	 * Complexity: Linear if `alloc != other.get_allocator()`, otherwise constant
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	xorlist(xorlist &&other, const Allocator &alloc) : alloc(alloc) {
		if (alloc == other.get_allocator())
			splice(end(), other);
		else {
			typedef std::move_iterator<iterator> Ip;
			assign(Ip(other.begin()), Ip(other.end()));
		}
	}

	/**
	 * Constructs the container with the contents of the initializer list `init`.
	 * Parameters:
	 *   - init: initializer list to initialize the elements of the container with
	 *   - alloc: allocator to use for all memory allocations of this container
	 * Complexity: Linear in size of `init`
	 * Exceptions: Calls to `Allocator::allocate` may throw.
	 */
	xorlist(std::initializer_list<value_type> init, const Allocator &alloc = Allocator()) : alloc(alloc) {
		for (typename std::initializer_list<value_type>::const_iterator i = init.begin(), e = init.end(); i != e; ++i)
			push_back(*i);
	}

	/**
	 * Destructs the `list`. The destructors of the elements are called and the used storage is deallocated. Note, that
	 * if the elements are pointers, the pointed-to objects are not destroyed. Complexity: Linear in the size of the
	 * `list`.
	 */
	~xorlist() { clear(); }

	/**
	 * Copy assignment operator. Replaces the contents with a copy of the contents of other. If
	 * `[std::allocator_traits](http://en.cppreference.com/w/cpp/memory/allocator_traits)<allocator_type>::propagate_on_container_copy_assignment::value`
	 * is `true`, the allocator of `*this` is replaced by a copy of that of other. If the allocator of `*this` after
	 * assignment would compare unequal to its old value, the old allocator is used to deallocate the memory, then the
	 * new allocator is used to allocate it before copying the elements. Otherwise, the memory owned by `*this` may be
	 * reused when possible. In any case, the elements originally belong to `*this` may be either destroyed or replaced
	 * by element-wise copy-assignment. Parameters:
	 *   - other: another container to use as data source
	 * Return value: `*this`
	 * Complexity: Linear in the size of `*this` and `other`.
	 * Exceptions: May throw implementation-defined exceptions.
	 */
	xorlist &operator=(const xorlist &other) {
		if (this != std::addressof(other)) {
			_copy_assign_alloc(other);
			assign(other.begin(), other.end());
		}

		return *this;
	}

	/*
	 * Move assignment operator. Replaces the contents with those of other using move semantics (i.e. the data in other
	 * is moved from other into this container). other is in a valid but unspecified state afterwards. If
	 * `[std::allocator_traits](http://en.cppreference.com/w/cpp/memory/allocator_traits)<allocator_type>::propagate_on_container_copy_assignment::value`
	 * is `true`, the allocator of `*this` is replaced by a copy of that of other. If it is `false` and the allocators
	 * of `*this` and other do not compare equal, `*this` cannot take ownership of the memory owned by other and must
	 * move-assign each element individually, allocating additional memory using its own allocator as needed. In any
	 * case, all elements originally belong to `*this` are either destroyed or replaced by element-wise move-assignment.
	 * Parameters:
	 *   - other: another container to use as data source
	 * Return value: `*this`
	 * Complexity: Linear in the size of `*this` unless the allocators do not compare equal and do not propagate, in
	 * which case linear in the size of `*this` and `other`. Exceptions:
	 * [noexcept](https://en.cppreference.com/w/cpp/language/noexcept_spec) specification:
	 * `noexcept([std::allocator_traits](http://en.cppreference.com/w/cpp/memory/allocator_traits)<Allocator>::is_always_equal::value)`
	 * Notes:
	 * After container move assignment, unless element-wise move assignment is forced by incompatible allocators,
	 * references, pointers, and iterators (other than the end iterator) to other remain valid, but refer to elements
	 * that are now in `*this`. The current standard makes this guarantee via the blanket statement in
	 * [[container.rev.reqmts]/17](http://eel.is/c++draft/container.rev.reqmts#17), and a more direct guarantee is under
	 * consideration via [LWG 2321](https://cplusplus.github.io/LWG/issue2321).
	 */
	xorlist &operator=(xorlist &&other) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) {
		_move_assign(
			other,
			integral_constant<bool, std::allocator_traits<Allocator>::propagate_on_container_move_assignment::value>());
		return *this;
	}

	/*
	 * Replaces the contents with those identified by initializer list `ilist`.
	 * Parameters:
	 *   - ilist: initializer list to use as data source
	 * Return value: `*this`
	 * Complexity: Linear in the size of `*this` and `ilist`.
	 * Exceptions: May throw implementation-defined exceptions.
	 */
	xorlist &operator=(std::initializer_list<value_type> ilist) {
		assign(ilist.begin(), ilist.end());
		return *this;
	}

	/*
	 * Replaces the contents with `count` copies of value `value`.
	 * Parameters:
	 *   - count: the new size of the container
	 *   - value: the value to initialize elements of the container with
	 * Complexity: Linear in `count`
	 */
	void assign(size_type count, const value_type &value) {
		iterator i = begin();
		iterator e = end();

		for (; count > 0 && i != e; --count, (void)++i)
			*i = value;

		if (i == e)
			insert(e, count, value);
		else
			erase(i, e);
	}

	/*
	 * Replaces the contents with copies of those in the range `[first, last)`. The behavior is undefined if either
	 * argument is an iterator into `*this`. This overload participates in overload resolution only if `InputIt`
	 * satisfies [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator). Parameters:
	 *   - first, last: the range to copy the elements from
	 * Complexity: Linear in distance between `first` and `last`
	 */
	template <class InputIt, std::enable_if_t<std::iterator_traits<InputIt>::value, bool> = true>
	void assign(InputIt first, InputIt last) {
		iterator i = begin();
		iterator e = end();

		for (; first != last && i != e; ++first, (void)++i)
			*i = *first;

		if (i == e)
			insert(e, first, last);
		else
			erase(i, e);
	}

	/*
	 * Replaces the contents with the elements from the initializer list `ilist`.
	 * Parameters:
	 *   - ilist: initializer list to copy the values from
	 * Complexity: Linear in `ilist.size()`
	 */
	void assign(std::initializer_list<value_type> ilist) { assign(ilist.begin(), ilist.end()); }

	/*
	 * Returns the allocator associated with the container.
	 * Return value: The associated allocator.
	 * Complexity: Constant.
	 */
	allocator_type get_allocator() const noexcept { return allocator_type(__node_alloc()); }

	/* Element access */

	/*
	 * Returns a reference to the first element in the container. Calling `front` on an empty container causes
	 * [undefined behavior](https://en.cppreference.com/w/cpp/language/ub). Return value: reference to the first element
	 * Complexity: Constant
	 * Notes: For a container `c`, the expression `c.front()` is equivalent to `*c.begin()`.
	 */
	reference front() {
		assert(!empty(), "xorlist::front called on empty xorlist");
		return *(end()++);
	}

	/*
	 * Returns a reference to the first element in the container. Calling `front` on an empty container causes
	 * [undefined behavior](https://en.cppreference.com/w/cpp/language/ub). Return value: reference to the first element
	 * Complexity: Constant
	 * Notes: For a container `c`, the expression `c.front()` is equivalent to `*c.begin()`.
	 */
	const_reference front() const {
		assert(!empty(), "xorlist::front called on empty xorlist");
		return *(end()++);
	}

	/*
	 * Returns a reference to the last element in the container. Calling `back` on an empty container causes [undefined
	 * behavior](https://en.cppreference.com/w/cpp/language/ub). Return value: Reference to the last element.
	 * Complexity: Constant.
	 * Notes: For a non-empty container `c`, the expression `c.back()` is equivalent to `*std::prev(c.end())`
	 */
	reference back() {
		assert(!empty(), "xorlist::back called on empty xorlist");
		return *(end()--);
	}

	/*
	 * Returns a reference to the last element in the container. Calling `back` on an empty container causes [undefined
	 * behavior](https://en.cppreference.com/w/cpp/language/ub). Return value: Reference to the last element.
	 * Complexity: Constant.
	 * Notes: For a non-empty container `c`, the expression `c.back()` is equivalent to `*std::prev(c.end())`
	 */
	const_reference back() const {
		assert(!empty(), "xorlist::back called on empty xorlist");
		return *(end()--);
	}

	/* Iterators */

	/*
	 * Returns an iterator to the first element of the list. If the list is empty, the returned iterator will be equal
	 * to `end()`. Return value: Iterator to the first element. Complexity: Constant.
	 */
	iterator begin() noexcept { iterator(end()++, this); }

	/*
	 * Returns an iterator to the first element of the list. If the list is empty, the returned iterator will be equal
	 * to `end()`. Return value: Iterator to the first element. Complexity: Constant.
	 */
	const_iterator begin() const noexcept { const_iterator(end()++, this); }

	/*
	 * Returns an iterator to the first element of the list. If the list is empty, the returned iterator will be equal
	 * to `end()`. Return value: Iterator to the first element. Complexity: Constant.
	 */
	const_iterator cbegin() const noexcept { return begin(); }

	/*
	 * Returns an iterator to the element following the last element of the list. This element acts as a placeholder;
	 * attempting to access it results in undefined behavior. Return value: Iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	iterator end() noexcept { return iterator(end); }

	/*
	 * Returns an iterator to the element following the last element of the list. This element acts as a placeholder;
	 * attempting to access it results in undefined behavior. Return value: Iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	const_iterator end() const noexcept { return const_iterator(end); }

	/*
	 * Returns an iterator to the element following the last element of the list. This element acts as a placeholder;
	 * attempting to access it results in undefined behavior. Return value: Iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	const_iterator cend() const noexcept { return end(); }

	/*
	 * Returns a reverse iterator to the first element of the reversed list. It corresponds to the last element of the
	 * non-reversed list. If the list is empty, the returned iterator is equal to `rend()`. Return value: Reverse
	 * iterator to the first element. Complexity: Constant.
	 */
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }

	/*
	 * Returns a reverse iterator to the first element of the reversed list. It corresponds to the last element of the
	 * non-reversed list. If the list is empty, the returned iterator is equal to `rend()`. Return value: Reverse
	 * iterator to the first element. Complexity: Constant.
	 */
	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }

	/*
	 * Returns a reverse iterator to the first element of the reversed list. It corresponds to the last element of the
	 * non-reversed list. If the list is empty, the returned iterator is equal to `rend()`. Return value: Reverse
	 * iterator to the first element. Complexity: Constant.
	 */
	const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(end()); }

	/*
	 * Returns a reverse iterator to the element following the last element of the reversed list. It corresponds to the
	 * element preceding the first element of the non-reversed list. This element acts as a placeholder, attempting to
	 * access it results in undefined behavior. Return value: Reverse iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

	/*
	 * Returns a reverse iterator to the element following the last element of the reversed list. It corresponds to the
	 * element preceding the first element of the non-reversed list. This element acts as a placeholder, attempting to
	 * access it results in undefined behavior. Return value: Reverse iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }

	/*
	 * Returns a reverse iterator to the element following the last element of the reversed list. It corresponds to the
	 * element preceding the first element of the non-reversed list. This element acts as a placeholder, attempting to
	 * access it results in undefined behavior. Return value: Reverse iterator to the element following the last
	 * element. Complexity: Constant.
	 */
	const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin()); }

	/* Capacity */

	/*
	 * Checks if the container has no elements, i.e. whether `begin() == end()`.
	 * Return value: `true` if the container is empty, `false` otherwise
	 * Complexity: Constant.
	 */
	[[nodiscard]] bool empty() const noexcept { return _size == 0; }

	/*
	 * Returns the number of elements in the container, i.e. `std::distance(begin(), end())`.
	 * Return value: The number of elements in the container.
	 * Complexity: Constant.
	 */
	size_type size() const noexcept { return _size; }

	/*
	 * Returns the maximum number of elements the container is able to hold due to system or library implementation
	 * limitations, i.e. `std::distance(begin(), end())` for the largest container. Return value: Maximum number of
	 * elements. Complexity: Constant. Notes: This value typically reflects the theoretical limit on the size of the
	 * container, at most `std::numeric_limits<difference_type>::max()`. At runtime, the size of the container may be
	 * limited to a value smaller than `max_size()` by the amount of RAM available.
	 */
	size_type max_size() const noexcept {
		return std::min<size_type>(__node_alloc_max_size(), std::numeric_limits<difference_type>::max());
	}

	/* Modifiers */

	/*
	 * Erases all elements from the container. After this call,
	 * [`size()`](https://en.cppreference.com/w/cpp/container/list/size) returns zero. Invalidates any references,
	 * pointers, or iterators referring to contained elements. Any past-the-end iterator remains valid. Complexity:
	 * Linear in the size of the container, i.e., the number of elements.
	 */
	void clear() noexcept {
		if (!empty()) {
			__node_allocator &__na = __node_alloc();

			__node_pointer __f = _end._link;
			__node_pointer __l = __f;
			__unlink_nodes(__f, __l--);
			_size = 0;

			while (__f != __l) {
				__node_pointer __np = __f->_as_node();
				__f = __f->_link;
				__node_alloc_traits::destroy(__na, std::addressof(__np->_value));
				__node_alloc_traits::deallocate(__na, __np, 1);
			}
		}
	}

	/*
	 * Inserts `value` before `pos`.
	 * Parameters:
	 *   - pos: iterator before which the content will be inserted. `pos` may be the `end()` iterator
	 *   - value: element value to insert
	 * Type requirements:
	 *   - T must meet the requirements of [CopyInsertable](https://en.cppreference.com/w/cpp/named_req/CopyInsertable)
	 * in order to use overload Return value: Iterator pointing to the inserted value Complexity: Constant. Exceptions:
	 * If an exception is thrown, there are no effects (strong exception guarantee). Notes: No iterators or references
	 * are invalidated.
	 */
	iterator insert(const_iterator pos, const value_type &value) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Inserts `value` before `pos`.
	 * Parameters:
	 *   - pos: iterator before which the content will be inserted. `pos` may be the `end()` iterator
	 *   - value: element value to insert
	 * Type requirements:
	 *   - T must meet the requirements of [MoveInsertable](https://en.cppreference.com/w/cpp/named_req/MoveInsertable)
	 * in order to use overload Return value: Iterator pointing to the inserted value Complexity: Constant. Exceptions:
	 * If an exception is thrown, there are no effects (strong exception guarantee). Notes: No iterators or references
	 * are invalidated.
	 */
	iterator insert(const_iterator pos, value_type &&value) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Inserts `count` copies of the `value` before `pos`.
	 * Parameters:
	 *   - pos: iterator before which the content will be inserted. `pos` may be the `end()` iterator
	 *   - value: element value to insert
	 *   - count: number of elements to insert
	 * Type requirements:
	 *   - T must meet the requirements of [CopyAssignable](https://en.cppreference.com/w/cpp/named_req/CopyAssignable)
	 * and [CopyInsertable](https://en.cppreference.com/w/cpp/named_req/CopyInsertable) in order to use overload Return
	 * value: Iterator pointing to the first element inserted, or pos if `count==0` Complexity: Linear in `count`
	 * Exceptions: If an exception is thrown, there are no effects (strong exception guarantee).
	 * Notes: No iterators or references are invalidated.
	 */
	iterator insert(const_iterator pos, size_type count, const value_type &value) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Inserts elements from range `[first, last)` before `pos`.
	 * This overload participates in overload resolution only if `InputIt` qualifies as
	 * [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator), to avoid ambiguity with the
	 * overload. The behavior is undefined if `first` and `last` are iterators into `*this`. Parameters:
	 *   - pos: iterator before which the content will be inserted. `pos` may be the `end()` iterator
	 *   - first, last: the range of elements to insert, can't be iterators into container for which insert is called
	 * Type requirements:
	 *   - T must meet the requirements of
	 * [EmplaceConstructible](https://en.cppreference.com/w/cpp/named_req/EmplaceConstructible) in order to use overload
	 * Return value: Iterator pointing to the first element inserted, or `pos` if `first==last`.
	 * Complexity: Linear in `std::distance(first, last)`
	 * Exceptions: If an exception is thrown, there are no effects (strong exception guarantee).
	 * Notes: No iterators or references are invalidated.
	 */
	template <class InputIt> iterator insert(const_iterator pos, InputIt first, InputIt last) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Inserts elements from initializer list `ilist` before `pos`.
	 * Parameters:
	 *   - ilist: initializer list to insert the values from
	 * Type requirements:
	 *   - T must meet the requirements of
	 * [EmplaceConstructible](https://en.cppreference.com/w/cpp/named_req/EmplaceConstructible) in order to use overload
	 * Return value: Iterator pointing to the first element inserted, or `pos` if `ilist` is empty.
	 * Complexity: Linear in `ilist.size()`
	 * Exceptions: If an exception is thrown, there are no effects (strong exception guarantee).
	 * Notes: No iterators or references are invalidated.
	 */
	iterator insert(const_iterator pos, std::initializer_list<value_type> ilist) {
		return insert(pos, ilist.begin(), ilist.end());
	}

	/*
	 * Inserts a new element into the container directly before `pos`. The element is constructed through
	 * [`std::allocator_traits::construct`](https://en.cppreference.com/w/cpp/memory/allocator_traits/construct), which
	 * uses placement-new to construct the element in-place at a location provided by the container. The arguments
	 * `args...` are forwarded to the constructor as `std::forward<Args>(args)...`. `args...` may directly or indirectly
	 * refer to a value in the container. No iterators or references are invalidated. Parameters:
	 *   - pos: iterator before which the new element will be constructed
	 *   - args: arguments to forward to the constructor of the element
	 * Type requirements:
	 *   - T (the container's element type) must meet the requirements of
	 * [EmplaceConstructible](https://en.cppreference.com/w/cpp/named_req/EmplaceConstructible). Return value: Iterator
	 * pointing to the emplaced element. Complexity: Constant. Exceptions: If an exception is thrown, the container is
	 * left unmodified, as if this function was never called (strong exception guarantee).
	 */
	template <class... Args> iterator emplace(const_iterator pos, Args &&...args) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Removes the element at `pos`.
	 * Parameters:
	 *   - pos: iterator to the element to remove
	 * Return value: Iterator following the last removed element. If `pos` refers to the last element, then the `end()`
	 * iterator is returned. Complexity: Constant.
	 */
	iterator erase(const_iterator pos) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Removes the elements in the range `[first, last)`. References and iterators to the erased elements are
	 * invalidated. Other references and iterators are not affected. The iterator pos must be valid and dereferenceable.
	 * Thus the `end()` iterator (which is valid, but is not dereferenceable) cannot be used as a value for `pos`. The
	 * iterator `first` does not need to be dereferenceable if `first==last`: erasing an empty range is a no-op.
	 * Parameters:
	 *   - first, last: range of elements to remove
	 * Return value: If `last==end()` prior to removal, then the updated `end()` iterator is returned. If `[first,
	 * last)` is an empty range, then `last` is returned. Complexity: Linear in the distance between `first` and `last`.
	 */
	iterator erase(const_iterator first, const_iterator last) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Appends the given element value to the end of the container. The new element is initialized as a copy of value.
	 * No iterators or references are invalidated.
	 * Parameters:
	 *   - value: the value of the element to prepend
	 * Type requirements:
	 *   - `T` must meet the requirements of
	 * [CopyInsertable](https://en.cppreference.com/w/cpp/named_req/CopyInsertable) in order to use Complexity:
	 * Constant. Exceptions: If an exception is thrown (which can be due to `Allocator::allocate()` or element copy/move
	 * constructor/assignment), this function has no effect ([strong exception
	 * guarantee](https://en.cppreference.com/w/cpp/language/exceptions#Exception_safety)).
	 */
	void push_back(const value_type &value) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Appends the given element value to the end of the container. `value` is moved into the new element.
	 * No iterators or references are invalidated.
	 * Parameters:
	 *   - value: the value of the element to prepend
	 * Type requirements:
	 *   - `T` must meet the requirements of
	 * [MoveInsertable](https://en.cppreference.com/w/cpp/named_req/MoveInsertable) in order to use Complexity:
	 * Constant. Exceptions: If an exception is thrown (which can be due to `Allocator::allocate()` or element copy/move
	 * constructor/assignment), this function has no effect ([strong exception
	 * guarantee](https://en.cppreference.com/w/cpp/language/exceptions#Exception_safety)).
	 */
	void push_back(value_type &&value) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Appends a new element to the end of the container. The element is constructed through
	 * `std::allocator_traits::construct`, which typically uses placement-new to construct the element in-place at the
	 * location provided by the container. The arguments `args...` are forwarded to the constructor as
	 * `[std::forward](http://en.cppreference.com/w/cpp/utility/forward)<Args>(args)...`. No iterators or references are
	 * invalidated. Parameters:
	 *   - args: arguments to forward to the constructor of the element
	 * Type requirements:
	 *   - `T` (the container's element type) must meet the requirements of
	 * [EmplaceConstructible](https://en.cppreference.com/w/cpp/named_req/EmplaceConstructible). Return value: A
	 * reference to the inserted element. Complexity: Constant. Exceptions: If an exception is thrown, this function has
	 * no effect (strong exception guarantee).
	 */
	template <class... Args> reference emplace_back(Args &&...args) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Removes the last element of the container.
	 * Calling `pop_back` on an empty container results in undefined behavior.
	 * References and iterators to the erased element are invalidated.
	 * Complexity: Constant.
	 * Exceptions: Throws nothing.
	 */
	void pop_back() { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Prepends the given element value to the beginning of the container. No iterators or references are invalidated.
	 * Parameters:
	 *   - value: the value of the element to prepend
	 * Complexity: Constant.
	 * Exceptions: If an exception is thrown, this function has no effect ([strong exception
	 * guarantee](https://en.cppreference.com/w/cpp/language/exceptions#Exception_safety)).
	 */
	void push_front(const value_type &value) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Prepends the given element value to the beginning of the container. No iterators or references are invalidated.
	 * Parameters:
	 *   - value: the value of the element to prepend
	 * Complexity: Constant.
	 * Exceptions: If an exception is thrown, this function has no effect ([strong exception
	 * guarantee](https://en.cppreference.com/w/cpp/language/exceptions#Exception_safety)).
	 */
	void push_front(value_type &&value) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Inserts a new element to the beginning of the container. The element is constructed through
	 * `std::allocator_traits::construct`, which typically uses placement-new to construct the element in-place at the
	 * location provided by the container. The arguments `args...` are forwarded to the constructor as
	 * `[std::forward](http://en.cppreference.com/w/cpp/utility/forward)<Args>(args)...`. No iterators or references are
	 * invalidated. Parameters:
	 *   - args: arguments to forward to the constructor of the element
	 * Type requirements
	 *   - `T` must meet the requirements of
	 * [EmplaceConstructible](https://en.cppreference.com/w/cpp/named_req/EmplaceConstructible). Return value: A
	 * reference to the inserted element. Complexity: Constant. Exceptions: If an exception is thrown, this function has
	 * no effect (strong exception guarantee).
	 */
	template <class... Args> reference emplace_front(Args &&...args) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Removes the first element of the container. If there are no elements in the container, the behavior is undefined.
	 * References and iterators to the erased element are invalidated. Complexity: Constant. Exceptions: Does not throw.
	 */
	void pop_front() { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Resizes the container to contain `count` elements.
	 * If the current size is greater than `count`, the container is reduced to its first `count` elements.
	 * If the current size is less than `count`, additional
	 * [default-inserted](https://en.cppreference.com/w/cpp/named_req/DefaultInsertable) elements are appended.
	 * Parameters:
	 *   - count: new size of the container
	 * Type requirements:
	 *   - T must meet the requirements of
	 * [DefaultInsertable](https://en.cppreference.com/w/cpp/named_req/DefaultInsertable) in order to use Complexity:
	 * Linear in the difference between the current size and `count`. Notes: If value-initialization is undesirable, for
	 * example, if the elements are of non-class type and zeroing out is not needed, it can be avoided by providing a
	 * [custom `Allocator::construct`](http://stackoverflow.com/a/21028912/273767).
	 */
	void resize(size_type count) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Resizes the container to contain count elements.
	 * If the current size is greater than `count`, the container is reduced to its first `count` elements.
	 * If the current size is less than `count`, additional copies of `value` are appended.
	 * Parameters
	 *   - count: new size of the container
	 *   - value: the value to initialize the new elements with
	 * Type requirements:
	 *   - T must meet the requirements of [CopyInsertable](https://en.cppreference.com/w/cpp/named_req/CopyInsertable)
	 * in order to use. Complexity: Linear in the difference between the current size and `count`.
	 */
	void resize(size_type count, const value_type &value) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Exchanges the contents of the container with those of `other`. Does not invoke any move, copy, or swap operations
	 * on individual elements. All iterators and references remain valid. It is unspecified whether an iterator holding
	 * the past-the-end value in this container will refer to this or the other container after the operation. If
	 * `std::allocator_traits<allocator_type>::propagate_on_container_swap::value` is `true`, then the allocators are
	 * exchanged using an unqualified call to non-member swap. Otherwise, they are not swapped (and if `get_allocator()
	 * != other.get_allocator()`, the behavior is undefined). Parameters:
	 *   - other: container to exchange the contents with
	 * Exceptions: [`noexcept`](https://en.cppreference.com/w/cpp/language/noexcept_spec) specification:
	 *   `noexcept(std::allocator_traits<Allocator>::is_always_equal::value)`
	 * Complexity: Constant.
	 */
	void swap(xorlist &other) noexcept(std::allocator_traits<Allocator>::is_always_equal::value) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/* Operations */

	/*
	 * The function does nothing if `other` refers to the same object as `*this`.
	 * Otherwise, merges two sorted lists into one. The lists should be sorted into ascending order. No elements are
	 * copied. The container `other` becomes empty after the operation. No iterators or references become invalidated,
	 * except that the iterators of moved elements now refer into `*this`, not into `other`. Uses `operator<` to compare
	 * the elements. This operation is stable: for equivalent elements in the two lists, the elements from `*this` shall
	 * always precede the elements from `other`, and the order of equivalent elements of `*this` and `other` does not
	 * change. If `get_allocator() != * other.get_allocator()`, the behavior is undefined. Parameters:
	 *   - other: another container to merge
	 * Exceptions: If an exception is thrown, this function has no effect (strong exception guarantee), except if the
	 * exception comes from a comparison. Complexity: If `other refers to the same object as `*this`, no comparisons are
	 * performed. Otherwise, given $M$ and $N$ as `std::distance(begin(), end())` and `std::distance(other.begin(),
	 * other.end())`: at most $M + N - 1$ comparisons using `operator<`
	 */
	void merge(xorlist &other) { merge(other, std::less<value_type>()); }

	/*
	 * The function does nothing if `other` refers to the same object as `*this`.
	 * Otherwise, merges two sorted lists into one. The lists should be sorted into ascending order. No elements are
	 * copied. The container `other` becomes empty after the operation. No iterators or references become invalidated,
	 * except that the iterators of moved elements now refer into `*this`, not into `other`. Uses `operator<` to compare
	 * the elements. This operation is stable: for equivalent elements in the two lists, the elements from `*this` shall
	 * always precede the elements from `other`, and the order of equivalent elements of `*this` and `other` does not
	 * change. If `get_allocator() != * other.get_allocator()`, the behavior is undefined. Parameters:
	 *   - other: another container to merge
	 * Exceptions: If an exception is thrown, this function has no effect (strong exception guarantee), except if the
	 * exception comes from a comparison. Complexity: If `other refers to the same object as `*this`, no comparisons are
	 * performed. Otherwise, given $M$ and $N$ as `std::distance(begin(), end())` and `std::distance(other.begin(),
	 * other.end())`: at most $M + N - 1$ comparisons using `operator<`
	 */
	void merge(xorlist &&other) { merge(other); }

	/*
	 * The function does nothing if `other` refers to the same object as `*this`.
	 * Otherwise, merges two sorted lists into one. The lists should be sorted into ascending order. No elements are
	 copied. The container `other` becomes empty after the operation. No iterators or references become invalidated,
	 except that the iterators of moved elements now refer into `*this`, not into `other`. Uses  the given comparison
	 function `comp` to compare the elements.
	 * This operation is stable: for equivalent elements in the two lists, the elements from `*this` shall always
	 precede the elements from `other`, and the order of equivalent elements of `*this` and `other` does not change.
	 * If `get_allocator() != * other.get_allocator()`, the behavior is undefined.
	 * Parameters:
	 *   - other: another container to merge
	 *   - comp:
		   comparison function object (i.e. an object that satisfies the requirements of
	 [Compare](https://en.cppreference.com/w/cpp/named_req/Compare)) which returns ​`true` if the first argument is
	 less than (i.e. is ordered before) the second. The signature of the comparison function should be equivalent to the
	 following: `bool cmp(const Type1 &a, const Type2 &b);` While the signature does not need to have `const &`, the
	 function must not modify the objects passed to it and must be able to accept all values of type (possibly `const`)
	 `Type1` and `Type2` regardless of [value category]( the given comparison function comp) (thus, `Type1 &` is not
	 allowed, nor is `Type1` unless for `Type1` a move is equivalent to a copy). The types `Type1` and `Type2` must be
	 such that an object of type `list<T, Allocator>::const_iterator` can be dereferenced and then implicitly converted
	 to both of them.
	 * Exceptions: If an exception is thrown, this function has no effect (strong exception guarantee), except if the
	 exception comes from a comparison.
	 * Complexity:
	 * If `other refers to the same object as `*this`, no comparisons are performed.
	 * Otherwise, given $M$ and $N$ as `std::distance(begin(), end())` and `std::distance(other.begin(), other.end())`:
	 at most $M + N - 1$ comparisons using `comp`
	 */
	template <class Compare> void merge(xorlist &other, Compare comp) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * The function does nothing if `other` refers to the same object as `*this`.
	 * Otherwise, merges two sorted lists into one. The lists should be sorted into ascending order. No elements are
	 copied. The container `other` becomes empty after the operation. No iterators or references become invalidated,
	 except that the iterators of moved elements now refer into `*this`, not into `other`. Uses  the given comparison
	 function `comp` to compare the elements.
	 * This operation is stable: for equivalent elements in the two lists, the elements from `*this` shall always
	 precede the elements from `other`, and the order of equivalent elements of `*this` and `other` does not change.
	 * If `get_allocator() != * other.get_allocator()`, the behavior is undefined.
	 * Parameters:
	 *   - other: another container to merge
	 *   - comp:
		   comparison function object (i.e. an object that satisfies the requirements of
	 [Compare](https://en.cppreference.com/w/cpp/named_req/Compare)) which returns ​`true` if the first argument is
	 less than (i.e. is ordered before) the second. The signature of the comparison function should be equivalent to the
	 following: `bool cmp(const Type1 &a, const Type2 &b);` While the signature does not need to have `const &`, the
	 function must not modify the objects passed to it and must be able to accept all values of type (possibly `const`)
	 `Type1` and `Type2` regardless of [value category]( the given comparison function comp) (thus, `Type1 &` is not
	 allowed, nor is `Type1` unless for `Type1` a move is equivalent to a copy). The types `Type1` and `Type2` must be
	 such that an object of type `list<T, Allocator>::const_iterator` can be dereferenced and then implicitly converted
	 to both of them.
	 * Exceptions: If an exception is thrown, this function has no effect (strong exception guarantee), except if the
	 exception comes from a comparison.
	 * Complexity:
	 * If `other refers to the same object as `*this`, no comparisons are performed.
	 * Otherwise, given $M$ and $N$ as `std::distance(begin(), end())` and `std::distance(other.begin(), other.end())`:
	 at most $M + N - 1$ comparisons using `comp`
	 */
	template <class Compare> void merge(xorlist &&other, Compare comp) { merge(other, comp); }

	/*
	 * Transfers all elements from `other` into `*this`. The elements are inserted before the element pointed to by
	 * `pos`. The container `other` becomes empty after the operation. The behavior is undefined if `other` refers to
	 * the same object as `*this`. No elements are copied or moved, only the internal pointers of the list nodes are
	 * re-pointed. The behavior is undefined if: `get_allocator() != other.get_allocator()`. No iterators or references
	 * become invalidated, the iterators to moved elements remain valid, but now refer into `*this`, not into `other`.
	 * Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 * Exceptions: Throws nothing.
	 * Complexity: Constant
	 */
	void splice(const_iterator pos, xorlist &other) { throw std::logic_error::logic_error("Not yet implemented"); }

	/*
	 * Transfers all elements from `other` into `*this`. The elements are inserted before the element pointed to by
	 * `pos`. The container `other` becomes empty after the operation. The behavior is undefined if `other` refers to
	 * the same object as `*this`. No elements are copied or moved, only the internal pointers of the list nodes are
	 * re-pointed. The behavior is undefined if: `get_allocator() != other.get_allocator()`. No iterators or references
	 * become invalidated, the iterators to moved elements remain valid, but now refer into `*this`, not into `other`.
	 * Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 * Exceptions: Throws nothing.
	 * Complexity: Constant
	 */
	void splice(const_iterator pos, xorlist &&other) { splice(pos, other); }

	/*
	 * Transfers the element pointed to by `it` from `other` into `*this`. The element is inserted before the element
	 * pointed to by `pos`. No elements are copied or moved, only the internal pointers of the list nodes are
	 * re-pointed. The behavior is undefined if: `get_allocator() != other.get_allocator()`. No iterators or references
	 * become invalidated, the iterators to moved elements remain valid, but now refer into `*this`, not into `other`.
	 * Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 *   - it: the element to transfer from other to `*this`
	 * Exceptions: Throws nothing.
	 * Complexity: Constant
	 */
	void splice(const_iterator pos, xorlist &other, const_iterator it) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Transfers the element pointed to by `it` from `other` into `*this`. The element is inserted before the element
	 * pointed to by `pos`. No elements are copied or moved, only the internal pointers of the list nodes are
	 * re-pointed. The behavior is undefined if: `get_allocator() != other.get_allocator()`. No iterators or references
	 * become invalidated, the iterators to moved elements remain valid, but now refer into `*this`, not into `other`.
	 * Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 *   - it: the element to transfer from other to `*this`
	 * Exceptions: Throws nothing.
	 * Complexity: Constant
	 */
	void splice(const_iterator pos, xorlist &&other, const_iterator it) { splice(pos, other, it); }

	/*
	 * Transfers the elements in the range `[first, last)` from `other` into `*this`. The elements are inserted before
	 * the element pointed to by `pos`. The behavior is undefined if `pos` is an iterator in the range `[first,last)`.
	 * No elements are copied or moved, only the internal pointers of the list nodes are re-pointed. The behavior is
	 * undefined if: `get_allocator() != other.get_allocator()`. No iterators or references become invalidated, the
	 * iterators to moved elements remain valid, but now refer into `*this`, not into `other`. Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 *   - first, last: the range of elements to transfer from `other` to `*this`
	 * Exceptions: Throws nothing.
	 * Complexity: Constant if `other` refers to the same object as `*this`, otherwise linear in `std::distance(first,
	 * last)`.
	 */
	void splice(const_iterator pos, xorlist &other, const_iterator first, const_iterator last) {
		throw std::logic_error::logic_error("Not yet implemented");
	}

	/*
	 * Transfers the elements in the range `[first, last)` from `other` into `*this`. The elements are inserted before
	 * the element pointed to by `pos`. The behavior is undefined if `pos` is an iterator in the range `[first,last)`.
	 * No elements are copied or moved, only the internal pointers of the list nodes are re-pointed. The behavior is
	 * undefined if: `get_allocator() != other.get_allocator()`. No iterators or references become invalidated, the
	 * iterators to moved elements remain valid, but now refer into `*this`, not into `other`. Parameters:
	 *   - pos: element before which the content will be inserted
	 *   - other: another container to transfer the content from
	 *   - first, last: the range of elements to transfer from `other` to `*this`
	 * Exceptions: Throws nothing.
	 * Complexity: Constant if `other` refers to the same object as `*this`, otherwise linear in `std::distance(first,
	 * last)`.
	 */
	void splice(const_iterator pos, xorlist &&other, const_iterator first, const_iterator last) {
		splice(pos, other, first, last);
	}

	/*
	 * Removes all elements that are equal to value.
	 * Parameters:
	 *   - value: value of the elements to remove
	 * Return value: The number of elements removed.
	 * Complexity: Linear in the size of the container
	 */
	size_type remove(const value_type &value) {
		xorlist<value_type, Allocator> deleted_nodes(get_allocator()); // collect the nodes we're removing

		for (const_iterator i = begin(), e = end(); i != e;) {
			if (*i == value) {
				const_iterator j = std::next(i);

				for (; j != e && *j == value; ++j)
					;
				deleted_nodes.splice(deleted_nodes.end(), *this, i, j);
				i = j;

				if (i != e)
					++i;
			} else
				++i;
		}

		return deleted_nodes.size();
	}

	/*
	 * Removes all elements for which predicate `p` returns `true`.
	 * Parameters:
	 *   - p:
	 *     unary predicate which returns ​true if the element should be removed.
	 *     The expression `p(v)` must be convertible to `bool` for every argument `v` of type (possibly `const`) `T`,
	 * regardless of [value category](https://en.cppreference.com/w/cpp/language/value_category), and must not modify
	 * `v`. Thus, a parameter type of `T&` is not allowed, nor is `T` unless for `T` a move is equivalent to a copy.
	 * Return value: The number of elements removed.
	 * Complexity: Linear in the size of the container
	 */
	template <class UnaryPredicate> size_type remove_if(UnaryPredicate p) {
		xorlist<value_type, Allocator> deleted_nodes(get_allocator()); // collect the nodes we're removing

		for (iterator i = begin(), e = end(); i != e;) {
			if (p(*i)) {
				iterator j = std::next(i);

				for (; j != e && p(*j); ++j)
					;
				deleted_nodes.splice(deleted_nodes.end(), *this, i, j);
				i = j;

				if (i != e)
					++i;
			} else
				++i;
		}

		return deleted_nodes.size();
	}

	/*
	 * Reverses the order of the elements in the container. No references or iterators become invalidated.
	 * Complexity: Linear in the size of the container
	 */
	void reverse() noexcept {
		if (_size > 1) {
			iterator e = end();

			for (iterator i = begin(); *i != *e;) {
				std::swap((*i)--, (*i)++);
				*i = (*i)--;
			}

			std::swap((*e)--, (*e)++);
		}
	}

	/*
	 * Removes all *consecutive* duplicate elements from the container. Only the first element in each group of equal
	 * elements is left. The behavior is undefined if the selected comparator does not establish an equivalence
	 * relation. Uses `operator==` to compare the elements. Return value: The number of elements removed. Complexity:
	 * Exactly `size() - 1` comparisons of the elements, if the container is not empty. Otherwise, no comparison is
	 * performed.
	 */
	size_type unique() { return unique(std::equal_to<value_type>()); }

	/*
	 * Removes all consecutive duplicate elements from the container. Only the first element in each group of equal
	 * elements is left. The behavior is undefined if the selected comparator does not establish an equivalence
	 * relation. Uses the given binary predicate p to compare the elements. Parameters:
	 *   - p:
	 *     binary predicate which returns ​`true` if the elements should be treated as equal.
	 *     The signature of the predicate function should be equivalent to the following: `bool pred(const Type1 &a,
	 * const Type2 &b);` While the signature does not need to have `const &`, the function must not modify the objects
	 * passed to it and must be able to accept all values of type (possibly `const`) `Type1` and `Type2` regardless of
	 * [value category](https://en.cppreference.com/w/cpp/language/value_category) (thus, `Type1 &` is not allowed, nor
	 * is `Type1` unless for `Type1` a move is equivalent to a copy). The types `Type1` and `Type2` must be such that an
	 * object of type `xorlist<T,Allocator>::const_iterator` can be dereferenced and then implicitly converted to both
	 * of them. Return value: The number of elements removed. Complexity: Exactly `size() - 1` comparisons of the
	 * elements, if the container is not empty. Otherwise, no comparison is performed.
	 */
	template <class BinaryPredicate> size_type unique(BinaryPredicate p) {
		xorlist<value_type, Allocator> deleted_nodes(get_allocator()); // collect the nodes we're removing

		for (iterator i = begin(), e = end(); i != e;) {
			iterator j = std::next(i);

			for (; j != e && p(*i, *j); ++j)
				;

			if (++i != j) {
				deleted_nodes.splice(deleted_nodes.end(), *this, i, j);
				i = j;
			}
		}

		return deleted_nodes.size();
	}

	/*
	 * Sorts the elements in ascending order. The order of equal elements is preserved. Uses `operator<` to compare the
	 * elements. If an exception is thrown, the order of elements in `*this` is unspecified. Complexity: Approximately
	 * `N log N` comparisons, where `N` is the number of elements* in the list. Notes:
	 * [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort) requires random access iterators and so cannot be
	 * used with list. This function also differs from [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort)
	 * in that it does not require the element type of the list to be swappable, preserves the values of all iterators,
	 * and performs a stable sort.
	 */
	void sort() { sort(std::less<value_type>()); }

	/*
	 * Sorts the elements in ascending order. The order of equal elements is preserved. Uses the given comparison
	 * function `comp` to compare the elements. If an exception is thrown, the order of elements in `*this` is
	 * unspecified. Parameters:
	 *   - comp:
	 *     comparison function object (i.e. an object that satisfies the requirements of
	 * [Compare](https://en.cppreference.com/w/cpp/named_req/Compare)) which returns ​`true` if the first argument is
	 * *less* than (i.e. is ordered *before*) the second. The signature of the comparison function should be equivalent
	 * to the following: `bool cmp(const Type1 &a, const Type2 &b);` While the signature does not need to have `const
	 * &`, the function must not modify the objects passed to it and must be able to accept all values of type (possibly
	 * `const`) `Type1` and `Type2` regardless of [value
	 * category](https://en.cppreference.com/w/cpp/language/value_category) (thus, `Type1 &` is not allowed, nor is
	 * `Type1` unless for `Type1` a move is equivalent to a copy). The types `Type1` and `Type2` must be such that an
	 * object of type `xorlist<T,Allocator>::const_iterator` can be dereferenced and then implicitly converted to both
	 * of them. Complexity: Approximately `N log N` comparisons, where `N` is the number of elements* in the list.
	 * Notes:
	 * [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort) requires random access iterators and so cannot be
	 * used with list. This function also differs from [`std::sort`](https://en.cppreference.com/w/cpp/algorithm/sort)
	 * in that it does not require the element type of the list to be swappable, preserves the values of all iterators,
	 * and performs a stable sort.
	 */
	template <class Compare> void sort(Compare comp) { throw std::logic_error::logic_error("Not yet implemented"); }

  private:
	inline void __unlink_nodes(_node<T> *__f, _node<T> *__l) noexcept {
		__f->_link = __f;
		__l->_link = __l;
	}

	size_type __node_alloc_max_size() const noexcept { return __node_alloc_traits::max_size(alloc); }

	void _copy_assign_alloc(const xorlist &other) {
		if constexpr (std::allocator_traits<allocator_type>::propagate_on_container_copy_assignment::value) {
			if (alloc != other.get_allocator())
				clear();

			alloc = other.get_allocator();
		}
	}

	void _move_assign(xorlist &other, std::false_type) {
		if (alloc != other.get_allocator()) {
			using _Ip = std::move_iterator<iterator>;
			assign(_Ip(other.begin()), _Ip(other.end()));
		} else
			_move_assign(other, std::true_type);
	}

	void _move_assign(xorlist &other, std::true_type) noexcept(std::is_nothrow_move_assignable<allocator_type>::value) {
		clear();
		_move_assign_alloc(other);
		splice(end(), other);
	}
};

/* Non - member functions */

/*
 * Compares the contents of two lists. Checks if the contents of `lhs` and `rhs` are equal, that is, they have the same
 * number of elements and each element in `lhs` compares equal with the element in `rhs` at the same position. The <,
 * <=, >, >=, and != operators are
 * [synthesized](https://en.cppreference.com/w/cpp/language/operators#Relational_operators) from `operator<=>` and
 * `operator==` respectively. Parameters:
 *   - lhs, rhs: lists whose contents to compare
 * Type requirements:
 *  - T must meet the requirements of
 * [EqualityComparable](https://en.cppreference.com/w/cpp/named_req/EqualityComparable) in order to use overloads.
 * Return value: `true` if the contents of the lists are equal, `false` otherwise
 * Complexity: Constant if `lhs` and `rhs` are of different size, otherwise linear in the size of the list
 */
export template <class T, class Alloc> bool operator==(const xorlist<T, Alloc> &lhs, const xorlist<T, Alloc> &rhs) {
	return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

export template <class T, class Alloc> inline bool operator!=(const xorlist<T, Alloc> &x, const xorlist<T, Alloc> &y) {
	return !(x == y);
}

/*
 * Compares the contents of two lists.
 * Compares the contents of `lhs` and `rhs` lexicographically. The comparison is performed as if by calling
 [`std::lexicographical_compare_three_way`](https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare_three_way)
 on two lists with a function object performing synthesized three-way comparison. The return type is same as the result
 type of synthesized three-way comparison.
 * Given two `const E` lvalues `lhs` and `rhs` as left hand operand and right hand operand respectively (where `E` is
 `T`), *synthesized three-way comparison* is defined as:
 *   - if `std::three_way_comparable_with<E, E>` is satisfied, equivalent to `lhs <=> rhs;`
 *   - otherwise, if comparing two `const E` lvalues by `operator<` is well-formed and the result type satisfies
 [boolean-testable](https://en.cppreference.com/w/cpp/concepts/boolean-testable), equivalent to
 *     ```cpp
		lhs < rhs ? std::weak_ordering::less :
		rhs < lhs ? std::weak_ordering::greater :
					std::weak_ordering::equivalent
 *     ```
 *   - otherwise, synthesized three-way comparison is not defined, and `operator<=>` does not participate in overload
 resolution.
 * The behavior of `operator<=>` is undefined if
 [three_way_comparable_with](https://en.cppreference.com/w/cpp/utility/compare/three_way_comparable) or
 [boolean-testable](https://en.cppreference.com/w/cpp/concepts/boolean-testable) is satisfied but not modeled, or
 `operator<` is used but `E` and < do not establish a total order.
 * The <, <=, >, >=, and != operators are
 [synthesized](https://en.cppreference.com/w/cpp/language/operators#Relational_operators) from `operator<=>` and
 `operator==` respectively.
 * Parameters:
 *   - lhs, rhs: lists whose contents to compare
 * Type requirements:
 *  - T must meet the requirements of
 [EqualityComparable](https://en.cppreference.com/w/cpp/named_req/EqualityComparable) in order to use overloads.
 * Return value: The relative order of the first pair of non-equivalent elements in `lhs` and `rhs` if there are such
 elements, `lhs.size() <=> rhs.size()` otherwise.
 * Complexity: Linear in the size of the list
 */
export template <class value_type, class Alloc>
auto operator<=>(const xorlist<value_type, Alloc> &lhs, const xorlist<value_type, Alloc> &rhs) {
	return lhs.size() == rhs.size() && std::lexicographical_compare_three_way(lhs.begin(), lhs.end(), rhs.begin());
}

export template <class T, class Alloc> inline bool operator<(const xorlist<T, Alloc> &x, const xorlist<T, Alloc> &y) {
	return std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

export template <class T, class Alloc> inline bool operator>(const xorlist<T, Alloc> &x, const xorlist<T, Alloc> &y) {
	return y < x;
}

export template <class T, class Alloc> inline bool operator>=(const xorlist<T, Alloc> &x, const xorlist<T, Alloc> &y) {
	return !(x < y);
}

export template <class T, class Alloc> inline bool operator<=(const xorlist<T, Alloc> &x, const xorlist<T, Alloc> &y) {
	return !(y < x);
}

/*
 * Specializes the [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap) algorithm for `std::list`. Swaps the
 * contents of `lhs` and `rhs`. Calls `lhs.swap(rhs)`. Parameters:
 *   - lhs, rhs: containers whose contents to swap
 * Complexity: Constant.
 * Exceptions: [noexcept](https://en.cppreference.com/w/cpp/language/noexcept_spec) specification:
 * `noexcept(noexcept(lhs.swap(rhs)))` Notes: Although the overloads of
 * [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap) for container adaptors are introduced in C++11,
 * container adaptors can already be swapped by [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap) in
 * C++98. Such calls to [`std::swap`](https://en.cppreference.com/w/cpp/algorithm/swap) usually have linear time
 * complexity, but better complexity may be provided.
 */
export template <class value_type, class Alloc>
void swap(xorlist<value_type, Alloc> &lhs, xorlist<value_type, Alloc> &rhs) noexcept(noexcept(lhs.swap(rhs))) {
	lhs.swap(rhs);
}

/*
 * Erases all elements that compare equal to value from the container. Equivalent to `return c.remove_if([&](auto& elem)
 * { return elem == value; });` Parameters:
 *   - c: container from which to erase
 *   - value: value to be removed
 * Return value: The number of erased elements.
 * Complexity: Linear.
 * Notes:
 * Unlike [`xorlist::remove`](https://en.cppreference.com/w/cpp/container/list/remove), erase accepts heterogenous types
 * and does not force a conversion to the container's value type before invoking the `==` operator.
 */
export template <class value_type, class Alloc, class U>
typename xorlist<value_type, Alloc>::size_type erase(xorlist<value_type, Alloc> &c, const U &value) {
	return std::erase_if(c, [&](auto &e) { return e == value; });
}

/*
 * Erases all elements that satisfy the predicate pred from the container. Equivalent to `return c.remove_if(pred);`
 * Parameters:
 *   - c: container from which to erase
 *   - value: value to be removed
 *   - pred:
 *     unary predicate which returns ​`true` if the element should be erased.
 *     The expression `pred(v)` must be convertible to `bool` for every argument `v` of type (possibly `const`) `T`,
 * regardless of [value category](https://en.cppreference.com/w/cpp/language/value_category), and must not modify `v`.
 *     Thus, a parameter type of `T&` is not allowed, nor is `T` unless for `T` a move is equivalent to a copy.
 * Return value: The number of erased elements.
 * Complexity: Linear.
 * Notes:
 * Unlike `xorlist::remove`, erase accepts heterogenous types and does not force a conversion to the container's value
 * type before invoking the `==` operator.
 */
export template <class value_type, class Alloc, class Pred>
typename xorlist<value_type, Alloc>::size_type erase_if(xorlist<value_type, Alloc> &c, Pred pred) {
	return c.remove_if(pred);
}

/* Deduction guides */

/*
 * This [deduction guide](https://en.cppreference.com/w/cpp/language/class_template_argument_deduction) is provided for
 * list to allow deduction from an iterator range. This overload participates in overload resolution only if InputIt
 * satisfies [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator) and Alloc satisfies
 * [Allocator](https://en.cppreference.com/w/cpp/named_req/Allocator). Note: The extent to which the library determines
 * that a type does not satisfy [LegacyInputIterator](https://en.cppreference.com/w/cpp/named_req/InputIterator) is
 * unspecified, except that as a minimum integral types do not qualify as input iterators. Likewise, the extent to which
 * it determines that a type does not satisfy [Allocator](https://en.cppreference.com/w/cpp/named_req/Allocator) is
 * unspecified, except that as a minimum the member type `Alloc::value_type` must exist and the expression
 * `std::declval<Alloc&>().allocate(std::size_t{})` must be well-formed when treated as an unevaluated operand.
 */
export template <class InputIt, class Alloc = std::allocator<typename std::iterator_traits<InputIt>::value_type>>
xorlist(InputIt, InputIt, Alloc = Alloc()) -> xorlist<typename std::iterator_traits<InputIt>::value_type, Alloc>;
