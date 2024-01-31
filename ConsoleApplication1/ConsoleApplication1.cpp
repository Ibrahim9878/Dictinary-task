#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;
template <typename PairTKey, typename PairTValue>
class KeyValuePair {
public:
	PairTKey key;
	PairTValue value;
	KeyValuePair() :key(), value() {}
	KeyValuePair(const PairTKey key, const PairTValue value)
		:key(key), value(value) {}
	PairTValue& operator[](PairTKey key) { return value; }
};
template <typename TKey, typename TValue>
class Dictionary {
private:
	KeyValuePair<TKey, TValue>* _pairs = nullptr;
	size_t _count = 0;
	size_t _capacity = 5;
public:
	Dictionary()
	{
		_pairs = new KeyValuePair<TKey, TValue>[_capacity];
	}
	TValue& item(const TKey key)
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key)
				return _pairs[i].value;
		}
	}
	TValue& operator[](const TKey key)
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key) return _pairs[i][key];
		}
	}
	void Add(KeyValuePair<TKey, TValue>& item)
	{
		if (containsKey(item.key))
			assert(!"Bu key movcuddur");

		if (_count < _capacity)
			_pairs[_count++] = item;
		else
		{
			auto newArray = new KeyValuePair<TKey, TValue>[_count + 1];

			for (size_t i = 0; i < _count; i++)
				newArray[i] = _pairs[i];

			newArray[_count] = item;
			_count++;

			if (_pairs != nullptr) delete[] _pairs;

			_pairs = newArray;
		}
	}

	void Add(TKey key, TValue value)
	{
		if (containsKey(key))
			assert(!"Bu key movcuddur");

		KeyValuePair<TKey, TValue> newItem(key, value);
		this->Add(newItem);
	}
	size_t count() const
	{
		return _count;
	}
	size_t capacity() const
	{
		return _capacity;
	}
	TKey* AllKeys()
	{
		if (_count == 0)
			return nullptr;

		TKey* newArray = new TKey[_count];

		for (size_t i = 0; i < _count; i++)
			newArray[i] = _pairs[i].key;

		return newArray;
	}
	TKey* AllValues()
	{
		if (_count == 0)
			return nullptr;

		TKey* newArray = new TKey[_count];

		for (size_t i = 0; i < _count; i++)
			newArray[i] = _pairs[i].key;

		return newArray;
	}
	KeyValuePair<TKey, TValue>* items()
	{
		return _pairs;
	}
	void clear()
	{
		delete[] _pairs;
	}
	bool containsKey(const TKey key) const
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key)return true;
		}
		return false;
	}
	bool containsValue(const TValue value) const
	{
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].value == value)return true;
		}
		return false;
	}
	bool remove(const TKey key)
	{
		if (!(containsKey(key)))
			return false;
		KeyValuePair<TKey, TValue>* NewArray = new KeyValuePair<TKey, TValue>[_count - 1];
		int index = 0;
		for (size_t i = 0; i < _count; i++)
		{
			if (_pairs[i].key == key)
				continue;
			NewArray[index++] = _pairs[i];
		}
		_count--;
		if (_pairs != nullptr) delete[] _pairs;
		_pairs = NewArray;
		return true;
	}

};
int main() {
	Dictionary<int, string > dict;
	dict.Add(1, "Apple");
	dict.Add(2, "Ibo");
	dict.Add(3, "Maga");
	dict.Add(4, "Maga");
	dict.Add(5, "Maga");
	dict.Add(6, "Maga");
	KeyValuePair<int, string> a(10, "ehe");
	dict.Add(a);
	cout << dict[4];

	cout << dict.remove(2) << endl;
	cout << dict[3] << endl;
}