#pragma once
#include <iostream>
#include <list>
#include <algorithm>
#include <future>
#include "thread_pool.h"

//c++ �汾�Ŀ��������㷨
template<typename T>
void quick_sort_recursive(T arr[], int start, int end) {
	if (start >= end) return;
	T key = arr[start];
	int left = start, right = end;
	while (left < right) {
		while (arr[right] >= key && left < right) right--;
		while (arr[left] <= key && left < right) left++;
		std::swap(arr[left], arr[right]);
	}

	if (arr[left] < key) {
		std::swap(arr[left], arr[start]);
	}


	quick_sort_recursive(arr, start, left - 1);
	quick_sort_recursive(arr, left + 1, end);
}

template<typename T>
void quick_sort(T arr[], int len) {
	quick_sort_recursive(arr, 0, len - 1);
}


template<typename T>
std::list<T> sequential_quick_sort(std::list<T> input)
{
	if (input.empty())
	{
		return input;
	}
	std::list<T> result;

	//  �� ��input�еĵ�һ��Ԫ�ط���result�У����ҽ����һ��Ԫ�ش�input��ɾ��
	result.splice(result.begin(), input, input.begin());

	//  �� ȡresult�ĵ�һ��Ԫ�أ����������Ԫ�����и�и�input�е��б�
	T const& pivot = *result.begin();

	//  ��std::partition ��һ����׼�⺯�������ڽ������������е�Ԫ�ذ���ָ�����������з�����
	// ʹ������������Ԫ�����ڲ�����������Ԫ��֮ǰ��
	// ���Ծ�������divide_pointָ�����input�е�һ�����ڵ���pivot��Ԫ��
	auto divide_point = std::partition(input.begin(), input.end(),
		[&](T const& t) {return t < pivot; });

	// �� ���ǽ�С��pivot��Ԫ�ط���lower_part��
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(),
		divide_point);

	// �����ǽ�lower_part���ݸ�sequential_quick_sort ����һ���µ�����Ĵ�С���������
	//lower_part �ж���С��divide_point��ֵ
	auto new_lower(
		sequential_quick_sort(std::move(lower_part)));
	// ������ʣ���input�б��ݸ�sequential_quick_sort�ݹ���ã�input�ж��Ǵ���divide_point��ֵ��
	auto new_higher(
		sequential_quick_sort(std::move(input)));
	//�ߵ���ʱnew_higher��new_lower���Ǵ�С��������õ��б�
	//��new_higher ƴ�ӵ�result��β��
	result.splice(result.end(), new_higher);
	//��new_lower ƴ�ӵ�result��ͷ��
	result.splice(result.begin(), new_lower);
	return result;
}

//���а汾
template<typename T>
std::list<T> async_quick_sort(std::list<T> input)
{
	if (input.empty())
	{
		return input;
	}
	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();
	auto divide_point = std::partition(input.begin(), input.end(),
		[&](T const& t) {return t < pivot; });
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(),
		divide_point);
	// ����Ϊlower_part�Ǹ��������Բ��в������������߼����������������future������
	std::future<std::list<T>> new_lower(
		std::async(&async_quick_sort<T>, std::move(lower_part)));

	// ��
	auto new_higher(
		async_quick_sort(std::move(input)));
	result.splice(result.end(), new_higher);
	result.splice(result.begin(), new_lower.get());
	return result;
}


//�̳߳ذ汾
//���а汾
template<typename T>
std::list<T> thread_pool_quick_sort(std::list<T> input)
{
	if (input.empty())
	{
		return input;
	}
	std::list<T> result;
	result.splice(result.begin(), input, input.begin());
	T const& pivot = *result.begin();
	auto divide_point = std::partition(input.begin(), input.end(),
		[&](T const& t) {return t < pivot; });
	std::list<T> lower_part;
	lower_part.splice(lower_part.end(), input, input.begin(),
		divide_point);
	// ����Ϊlower_part�Ǹ��������Բ��в������������߼���������Ͷ�ݸ��̳߳ش���
	auto new_lower = ThreadPool::instance().commit(&parallel_quick_sort<T>, std::move(lower_part));
	// ��
	auto new_higher(
		parallel_quick_sort(std::move(input)));
	result.splice(result.end(), new_higher);
	result.splice(result.begin(), new_lower.get());
	return result;
}

