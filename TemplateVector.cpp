#include <iostream>
#include <initializer_list>
using namespace std;


template<typename T>
class Array
{
	T* array = nullptr;
	int size = 0;
	int bound = 0;
	int grow = 5;

public:
	Array(initializer_list<T> list)
	{
		size = list.size();
		bound = size + grow;
		array = new T[bound];
		for (int i = 0; i < size; i++)
			array[i] = *(list.begin() + i);
	}
	Array(int size, T fill)
	{
		this->size = size;
		bound = this->size + grow;
		array = new T[bound];
		for (int i = 0; i < size; i++)
			array[i] = fill;
	}
	Array(int size)
		: Array(size, T())
	{}
	Array()
		: Array(10)
	{}
	Array(T& copy)
	{
		size = copy.size;
		bound = copy.bound;
		grow = copy.grow;
		if (array)
			delete[] array;
		array = new T[bound];
		for (int i = 0; i < size; i++)
			array[i] = copy.array[i];
	}
	Array(T&& move)
	{
		size = move.size;
		bound = move.bound;
		grow = move.grow;
		if (array)
			delete[] array;
		array = new T[bound];
		for (int i = 0; i < size; i++)
			array[i] = move.array[i];
	}
	~Array(void)
	{
		delete[] array;
	}

	int getSize()
	{
		return size;
	}
	void SetSize(int size, int grow = 5)
	{
		T* t = array;
		bound = size + grow;
		array = new T[bound];
		if (t)
		{
			int s = this->size < size ? this->size : size;
			for (int i = 0; i < s; i++)
				array[i] = t[i];
			delete[] t;
		}
		this->size = size;
		this->grow = grow;
	}
	bool IsEmpty()
	{
		if (array)
			return true;
		return false;
	}
	void FreeExtra()
	{
		if (array)
		{
			T* t = array;
			bound = size;
			array = new T[size];
			for (int i = 0; i < size; i++)
				array[i] = t[i];
			delete[] t;
		}
	}
	void RemoveAll()
	{
		delete[] array;
		size = 0;
		bound = 0;
	}
	T GetAt(int index)
	{
		if (0 <= index && index < size)
			return array[index];
	}
	void SetAt(int index, T add)
	{
		if (0 <= index && index < size)
			array[index] = add;
	}
	void Add(T add)
	{
		if (size == bound)
		{
			T* t = array;
			bound = size + grow;
			array = new T[bound];
			if (t)
			{
				for (int i = 0; i < size; i++)
					array[i] = t[i];
				delete[] t;
			}
		}
		array[size] = add;
		size++;
	}
	void Append(Array& second)
	{
		T* t = array;
		array = new T[bound + second.size];
		for (int i = 0; i < size; i++)
			array[i] = t[i];
		for (int i = size, j = 0; i < size + second.size; i++, j++)
			array[i] = second.array[j];
		size += second.size;
		bound += second.size;
		if (t)
			delete[] t;
	}
	T* GetData()
	{
		return array;
	}
	void InsertAt(T add, int index)
	{
		if (0 <= index && index < size) return;
		if (size == bound)
		{
			T* t = array;
			bound = size + grow;
			array = new T[bound];
			if (t)
			{
				for (int i = 0; i < size; i++)
					array[i] = t[i];
				delete[] t;
			}
		}
		T* t = array;
		array = new T[bound];
		size++;
		for (int i = 0, j = 0; i < size; i++, j++)
			if (i == index)
			{
				array[i] = t[j];
				j--;
			}
			else
				array[i] = t[j];
		if (t)
			delete[] t;
	}
	void RemoveAt(int index)
	{
		if (0 > index || index >= size) return;
		T* t = array;
		array = new T[bound];
		for (int i = 0, j = 0; i < size; i++, j++)
			if (i == index)
				j--;
			else
				array[j] = t[i];
		size--;
		if (t)
			delete[] t;
	}

	T& operator[](int index)
	{
		return array[index];
	}
	T& operator=(T& copy)
	{
		size = copy.size;
		bound = copy.bound;
		grow = copy.grow;
		if (array)
			delete[] array;
		array = new T[bound];
		for (int i = 0; i < size; i++)
			array[i] = copy.array[i];
		return *this;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
			cout << array[i] << " "; cout << endl;
	}
};



int main()
{
	Array<float> arr{1, 2, 3, 4, 5};
	arr.print();
	arr.Add(12);
	arr.print();
	Array<float> arr2{ 21, 22, 23, 24, 25 };
	arr.Append(arr2);
	arr.print();
	arr.RemoveAt(5);
	arr.print();
	return 0;
}