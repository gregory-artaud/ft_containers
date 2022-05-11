#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <uchar.h> // doesn't compile on mac

namespace ft {
	// Internal definitions
	template <bool is_integral, typename T> struct is_integral_core {
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename> struct is_integral_specs : public is_integral_core<false, void> {};

	template <> struct is_integral_specs<bool> : public is_integral_core<true, bool> {};
	template <> struct is_integral_specs<char> : public is_integral_core<true, char> {};
	template <> struct is_integral_specs<char16_t> : public is_integral_core<true, char16_t> {};
	template <> struct is_integral_specs<char32_t> : public is_integral_core<true, char32_t> {};
	template <> struct is_integral_specs<wchar_t> : public is_integral_core<true, wchar_t> {};
	template <> struct is_integral_specs<signed char> : public is_integral_core<true, signed char> {};
	template <> struct is_integral_specs<short int> : public is_integral_core<true, short int> {};
	template <> struct is_integral_specs<int> : public is_integral_core<true, int> {};
	template <> struct is_integral_specs<long int> : public is_integral_core<true, long int> {};
	template <> struct is_integral_specs<long long int> : public is_integral_core<true, long long int> {};
	template <> struct is_integral_specs<unsigned char> : public is_integral_core<true, unsigned char> {};
	//template <> struct is_integral_specs<unsigned short int> : public is_integral_core<true, unsigned short int> {};
	//template <> struct is_integral_specs<unsigned int> : public is_integral_core<true, unsigned int> {};
	template <> struct is_integral_specs<unsigned long int> : public is_integral_core<true, unsigned long int> {};
	template <> struct is_integral_specs<unsigned long long int> : public is_integral_core<true, unsigned long long int> {};

	// Externaly used template
	template <typename T> struct is_integral : public is_integral_specs<T> {};
}

#endif
