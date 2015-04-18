#ifndef _LIST2_H
#define _LIST2_H
#include <iostream>
#include "xcept.h"

using namespace std;

template<typename T>
class LinearList {
    public:
	LinearList();
	~LinearList() { delete [] element; }
	bool IsEmpty() const { return length == 0; }
	int Length() const { return length; }
	bool Find(int k, T& x) const;//返回第k个元素到x中
	int Search(const T& x) const;//返回x所在的位置
	LinearList<T>& Delete(int k, T& x);//删除第k个元素并将它返回到x中
	LinearList<T>& Insert(int k, const T& x);//在第k个元素之后插入x
	void Output(ostream& out) const;
    private:
	int length;
	int MaxSize;
	T *element;//一维动态数组
};
/**
 *新建线性表时，置MaxSize为1,之后在执行插入操作期间
 *如果在表中已经有了MaxSize个元素，则将MaxSize加倍
 *执行删除操作时，如果线性表的尺寸降至当前MaxSize的四分之一
 *，则分配一个更小的，尺寸为MaxSize/2的数组。
 * 
 */
template<typename T>
LinearList<T>::LinearList()
{
    MaxSize = 1;
    element = new T[MaxSize];
    length = 0;
}

template<typename T>
bool LinearList<T>::Find(int k, T& x) const
{
    //把第k个元素取至x中
    //如果不存在第k个元素，则返回false，否则返回true
    if (k < 1 || k > length)
	return false;
    x = element[k - 1];
    return true;
}

template<typename T>
int LinearList<T>::Search(const T&x) const
{
    //查找x,如果找到，则返回x所在的位置，
    //如果x不在表中，则返回 
    //
    for (int i = 0; i < length; i++)
	if (element[i] == x)
	    return ++i;
    return 0;
}
/**
 * 如果当前length已经降至当前的MaxSize的四分之一，
 * 则缩小数组大小
 */
template<typename T>
LinearList<T>& LinearList<T>::Delete(int k, T& x)
{
    //把第k个元素放入x中，并删除第k个元素
    //如果不存在第k个元素，就抛出OutOfBounds异常
    if (Find(k, x)) {
	for (int i = k; i < length; i++)
	    element[i-1] = element[i];
	length--;
	if (length <= MaxSize/4) {
	   T *new_elements = new T[MaxSize/4];
	   for (int i = 0; i < length; i++)
		new_elements[i] = element[i];
	   delete[] element;
	   element = new_elements;
	}
	return *this;
    } else throw OutOfBounds();
}
/**
 * 如果当前数组大小已经达到MaxSize,
 * 则数组大小再翻倍
 */
template<typename T>
LinearList<T>& LinearList<T>::Insert(int k, const T& x)
{
    //在第k个元素之后插入x
    //如果不存在第k个元素，则引发OutOfBounds异常
    //如果表满，则引发异常NoMem
    if (k < 0 || k > length) throw OutOfBounds();
    if (length == MaxSize) {
       T* new_elements = new T[2*MaxSize];
       for (int i = 0; i < length; i++)
    	   new_elements[i] = element[i];
       delete[] element;       
       element = new_elements;
    }

    for (int i = length-1; i >= k; i--)
	element[i+1] = element[i];
    element[k] = x;
    length++;
    return *this;
}

template<typename T>
void LinearList<T>::Output(ostream& out) const
{
    for (int i = 0; i < length; i++)
	out<<element[i]<<" ";
}

template<typename T>
ostream& operator<<(ostream& out, const LinearList<T>& x)
{
    x.Output(out);
    return out;
}
#endif
