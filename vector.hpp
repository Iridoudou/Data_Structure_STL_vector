#ifndef SJTU_VECTOR_HPP
#define SJTU_VECTOR_HPP

#include "exceptions.hpp"

#include <climits>
#include <cstddef>
#include<iostream>

namespace sjtu 
{
	template<typename T>
	class vector
	{
	private:
		int currentSize;
		int capacity;
		T* object;
		void doubleSpace()
		{
			capacity *= 2;
			T* tmp = object;
			object = (T*)malloc(sizeof(T) * capacity);
			for (int i = 0; i < currentSize; i++)
				object[i] = tmp[i];
			for (int i = 0; i < capacity / 2; i++)
				object[i].~T();
			free(tmp);
		}
	public:
		class const_iterator;
		class iterator 
		{
		public:
			vector<T>* point;
			int num;//下标
		public:
			iterator(vector<T>* p = NULL, int n = 0):point(p),num(n){}
			iterator operator+(const int& n) const 
			{
				if (num + n >= point->currentSize)
					throw index_out_of_bound();
				iterator a(point, num + n);
				return a;
			}
			iterator operator-(const int& n) const 
			{
				if (num - n < 0)
					throw index_out_of_bound();
				iterator a(point, num - n);
				return a;
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const iterator& rhs) const
			{ 
				if (point != rhs.point)
					throw invalid_iterator();
				if (num <= rhs.num)
					return rhs.num - num;
				return num - rhs.num;
			}
			iterator operator+=(const int& n)
			{
				if (num + n >= point->currentSize)
					throw index_out_of_bound();
				num += n;
				return *this;
			}
			iterator operator-=(const int& n) 
			{
				if (num - n < 0)
					throw index_out_of_bound();
				num -= n;
				return *this;
			}
			iterator operator++(int)
			{
				iterator tmp = *this;
				num++;
				return tmp;
			}
			iterator& operator++() 
			{
				num++;
				return *this;
			}
			iterator operator--(int) 
			{
				iterator tmp = *this;
				num--;
				return tmp;
			}
			iterator& operator--()
			{
				num--;
				return *this;
			}
			T& operator*() const
			{
				return point->object[num];
			}
			/**
			 * a operator to check whether two iterators are same (pointing to the same memory).
			 */
			bool operator==(const iterator& rhs) const 
			{
				return (num == rhs.num && point == rhs.point);
			}
			bool operator==(const const_iterator& rhs) const
			{
				return (num == rhs.num && point == rhs.point);
			}
			bool operator!=(const iterator& rhs) const
			{
				return (num != rhs.num || point != rhs.point);
			}
			bool operator!=(const const_iterator& rhs) const
			{
				return (num != rhs.num || point != rhs.point);
			}
		};
		class const_iterator 
		{
		public:
			const vector<T>* point;
			int num;//下标
		public:
			const_iterator(const vector* p = NULL, int n = 0) :point(p), num(n) {}
			const_iterator operator+(const int& n) const
			{
				if (n + num >= point->currentSize)
					throw index_out_of_bound();
				const_iterator a(point, num + n);
				return a;
			}
			const_iterator operator-(const int& n) const
			{
				if (num - n < 0)
					throw index_out_of_bound();
				const_iterator a(point, num - n);
				return a;
			}
			// return th distance between two iterator,
			// if these two iterators points to different vectors, throw invaild_iterator.
			int operator-(const const_iterator& rhs) const
			{
				if (point != rhs.point)
					throw invalid_iterator();
				if (num <= rhs.num)
					return rhs.num - num;
				return num - rhs.num;
			}
			const_iterator operator+=(const int& n)
			{
				if (n + num >= point->currentSize)
					throw index_out_of_bound();
				num += n;
				return *this;
			}
			const_iterator operator-=(const int& n)
			{
				if (num - n < 0)
					throw index_out_of_bound();
				num -= n;
				return *this;
			}
			const_iterator operator++(int)
			{
				const_iterator tmp = *this;
				num++;
				return tmp;
			}
			const_iterator& operator++()
			{
				num++;
				return *this;
			}
			const_iterator operator--(int)
			{
				const_iterator tmp = *this;
				num--;
				return tmp;
			}
			const_iterator& operator--()
			{
				num--;
				return *this;
			}
			const T& operator*() const
			{
				return point->object[num];
			}
			bool operator==(const iterator& rhs) const
			{
				return (num == rhs.num && point == rhs.point);
			}
			bool operator==(const const_iterator& rhs) const
			{
				return (num == rhs.num && point == rhs.point);
			}
			bool operator!=(const iterator& rhs) const
			{
				return (num != rhs.num || point != rhs.point);
			}
			bool operator!=(const const_iterator& rhs) const
			{
				return (num != rhs.num || point != rhs.point);
			}
		};
		vector()
		{
			currentSize = 0;
			capacity = 100;
			object = (T*)malloc(sizeof(T) * capacity);
			memset(object, 0, sizeof(T) * 100);
		}
		vector(const vector& other) 
		{
			currentSize = other.currentSize;
			capacity = other.capacity;
			object = (T*)malloc(sizeof(T) * capacity);
			memset(object, 0, sizeof(T) * capacity);
			for (int i = 0; i < currentSize; i++)
				object[i] = other.object[i];
		}
		~vector()
		{
			for (int i = 0; i < capacity; i++)
				object[i].~T();
			free(object);
		}
		vector& operator=(const vector& other) 
		{
			if (this == &other)//防止自己复制自己
				return *this;
			currentSize = other.currentSize;
			capacity = other.capacity;
			for (int i = 0; i < capacity; i++)
				object[i].~T();
			free(object);
			object = (T*)malloc(sizeof(T) * capacity);
			memset(object, 0, sizeof(T) * capacity);
			for (int i = 0; i < currentSize; i++)
				object[i] = other.object[i];
			return *this;
		}
		T& at(const size_t& pos)
		{
			if (pos < 0 || pos >= currentSize)
				throw index_out_of_bound();
			return object[pos];
		}
		const T& at(const size_t& pos) const
		{
			if (pos<0||pos >= currentSize)
				throw index_out_of_bound();
			return object[pos];
		}
		T& operator[](const size_t& pos)
		{
			if (pos >= currentSize)
				throw index_out_of_bound();
			return object[pos];
		}
		const T& operator[](const size_t& pos) const 
		{
			if (pos >= currentSize)
				throw index_out_of_bound();
			return object[pos];
		}
		const T& front() const 
		{
			if (currentSize == 0)
				throw container_is_empty();
			return object[0];
		}
		const T& back() const 
		{
			if (currentSize == 0)
				throw container_is_empty();
			return object[currentSize - 1];
		}
		iterator begin()
		{
			iterator itr(this,0);
			return itr;
		}
		const_iterator cbegin() const 
		{
			const_iterator itr(this, 0);
			return itr;
		}
		iterator end() 
		{
			iterator itr(this, currentSize);
			return itr;
		}
		const_iterator cend() const
		{
			const_iterator itr(this, currentSize);
			return itr;
		}
		bool empty() const 
		{
			return currentSize == 0;
		}
		size_t size() const
		{
			return currentSize;
		}
		void clear()
		{
			memset(object, 0, sizeof(T) * capacity);
			currentSize = 0;
		}
		iterator insert(iterator pos, const T& value)
		{
			if (currentSize == capacity)
				doubleSpace();
			for (int i = currentSize - 1; i >= pos.num; i--)
				object[i + 1] = object[i];//搬运
			currentSize++;
			object[pos.num] = value;
			iterator itr(this, pos.num);
			return itr;
		}
		iterator insert(const size_t& ind, const T& value)
		{
			if (currentSize < ind)
				throw index_out_of_bound();
			if (currentSize == capacity)
				doubleSpace();
			for (int i = currentSize - 1; i >= ind; i--)
				object[i + 1] = object[i];//搬运
			currentSize++;
			object[ind] = value;
			iterator itr(this, ind);
			return itr;
		}
		iterator erase(iterator pos)
		{
			for (int i = pos.num + 1; i < currentSize; i++)
				object[i - 1] = object[i];
			currentSize--;
			if (pos.num == currentSize)
				return end();
			iterator itr(this, pos.num);
			return itr;
		}
		iterator erase(const size_t& ind) 
		{
			if (ind >= currentSize)
				throw index_out_of_bound();
			for (int i = ind + 1; i < currentSize; i++)
				object[i - 1] = object[i];
			currentSize--;
			if (ind == currentSize)
				return end();
			iterator itr(this, ind);
			return itr;
		}
		void push_back(const T& value)
		{
			if (currentSize == capacity)
				doubleSpace();
			object[currentSize++] = value;
		}
		void pop_back() 
		{
			if (size() == 0)
				throw container_is_empty();
			currentSize--;
		}
	};

}

#endif