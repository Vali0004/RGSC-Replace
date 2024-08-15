#pragma once
#include "framework.h"

class mem
{
public:
	mem(void* p = nullptr) : m_ptr(p)
	{}
	mem(uint64_t p) : mem((void*)p)
	{}
public:
	template <typename T>
	T as()
	{
		return reinterpret_cast<T>(m_ptr);
	}
	mem add(uint64_t v)
	{
		return as<decltype(v)>() + v;
	}
	mem sub(uint64_t v)
	{
		return as<decltype(v)>() - v;
	}
	mem rip(uint8_t rip_relative = 4)
	{
		return add(*as<int*>()).add(rip_relative);
	}
	operator bool()
	{
		return m_ptr;
	}
private:
	void* m_ptr{};
};
class hmodule
{
public:
	hmodule(const char* name = nullptr) :
		m_begin(GetModuleHandleA(name)),
		m_size(m_begin ? m_begin.add(m_begin.as<IMAGE_DOS_HEADER*>()->e_lfanew).as<IMAGE_NT_HEADERS*>()->OptionalHeader.SizeOfImage : 0),
		m_end(m_begin.add(m_size))
	{}

	mem begin()
	{
		return m_begin;
	}
	mem end()
	{
		return m_end;
	}
	u64 size()
	{
		return m_size;
	}
	bool exists()
	{
		return size();
	}
protected:
	mem m_begin;
	mem m_end;
	u64 m_size;
};
typedef std::optional<uint8_t> byte_t;

inline byte_t char_to_hex(const char c)
{
	if (c >= 'a' && c <= 'f')
		return static_cast<uint8_t>(static_cast<int>(c) - 87);
	if (c >= 'A' && c <= 'F')
		return static_cast<uint8_t>(static_cast<int>(c) - 55);
	if (c >= '0' && c <= '9')
		return static_cast<uint8_t>(static_cast<int>(c) - 48);

	return {};
}

inline std::vector<byte_t> get_bytes_from_ptr(const std::string& ptr)
{
	std::vector<byte_t> bytes{};

	for (size_t i{}; i != ptr.size() - 1; ++i)
	{
		[[likely]] if (ptr[i] == ' ')
		{
			continue;
		}

		if (ptr[i] != '?')
		{
			[[likely]] if (auto c{ char_to_hex(ptr[i]) })
			{
				[[likely]] if (auto c2{ char_to_hex(ptr[i + 1]) })
				{
					bytes.emplace_back(static_cast<uint8_t>((*c * 0x10) + *c2));
				}
			}
		}
		else
		{
			bytes.push_back(std::nullopt);
		}
	}

	return bytes;
}
inline mem scan(const char* ptr, hmodule hmodule = {})
{
	std::vector<byte_t> bytes{ get_bytes_from_ptr(ptr) };
	int64_t max_shift{ static_cast<int64_t>(bytes.size()) };
	int64_t max_idx{ max_shift - 1 };

	// Get wildcard index, and store max shifable byte count
	int64_t wild_card_idx{ -1 };
	for (int64_t i{ max_idx - 1 }; i >= 0; --i)
	{
		if (!bytes[i])
		{
			max_shift = max_idx - i;
			wild_card_idx = i;
			break;
		}
	}

	// Store max shiftable bytes for non wildcards.
	std::array<int64_t, 0x100> shift_table{};
	shift_table.fill(max_shift);
	for (int64_t i{ wild_card_idx + 1 }; i != max_idx; ++i)
	{
		shift_table[*bytes[i]] = max_idx - i;
	}

	// Start search
	int64_t cur_idx{}, end_idx{ static_cast<int64_t>(hmodule.size() - bytes.size()) };
	mem scan_begin{ hmodule.begin() };
	while (cur_idx != end_idx)
	{
		for (int64_t sig_idx{ max_idx }; sig_idx >= 0; --sig_idx)
		{
			if (bytes[sig_idx].has_value() && *scan_begin.add(cur_idx + sig_idx).as<uint8_t*>() != bytes[sig_idx].value())
			{
				cur_idx += shift_table[*scan_begin.add(cur_idx + max_idx).as<uint8_t*>()];
				break;
			}

			if (!sig_idx)
			{
				return scan_begin.add(cur_idx);
			}
		}
	}

	return {};
}