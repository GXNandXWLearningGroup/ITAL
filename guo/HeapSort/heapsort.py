#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @Author: Guoxuenan
# @Date:   2015-12-24 02:51:58
# @Last Modified by:   Guoxuenan
# @Last Modified time: 2016-01-05 13:22:14
import numpy as np
def generate_random_point(number):
	return np.random.random_integers(0,100,number)

def LEFT(index):return index<<1
def RIGHT(index):return (index<<1)+1
def PARENT(index):return int(index/2)

def MAX_HEAPIFY(lists,index):
	length=len(lists);
	l=LEFT(index)
	r=RIGHT(index)
	largest=index

	if l<length and lists[l]>lists[index] :
		largest=l

	if r<length and lists[r]>lists[largest]:
		largest=r
	if largest!=index:
		temp=lists[index]
		lists[index]=lists[largest]
		lists[largest]=temp
		lists=MAX_HEAPIFY(lists,largest) 
	return lists

def BUILD_MAX_HEAP(lists):
	length=len(lists)
	for i in range(0,length/2):
		lists=MAX_HEAPIFY(lists,length/2-i)

def HEAP_SORT(lists):
	length=len(lists)
	BUILD_MAX_HEAP(lists)

	for i in range(1,length):
		lists[0]=lists[length-i]
		lists[length-i]=lists[1]
		lists[1]=lists[0]
		lists[0:length-i]=MAX_HEAPIFY(lists[0:length-i],1)
	return lists

if __name__ == '__main__':
	NUMBER=15
	list_origin=[None]
	list_origin+=list(generate_random_point(NUMBER))
	print "origin list  is:",list_origin[1:]
	print "After heap sort:", HEAP_SORT(list_origin)[1:]
	
	x=0
	for i in list_origin:
		if i<x:
			print False
		x=i
