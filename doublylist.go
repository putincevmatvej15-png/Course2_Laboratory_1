package main

import (
	"errors"
	"fmt"
)

type dNode struct {
	data string
	prev *dNode
	next *dNode
}

type DoublyList struct {
	head *dNode
	tail *dNode
	size int
}

func (l *DoublyList) PushFront(val string) {
	n := &dNode{data: val}
	if l.head == nil {
		l.head = n
		l.tail = n
	} else {
		n.next = l.head
		l.head.prev = n
		l.head = n
	}
	l.size++
}

func (l *DoublyList) PushBack(val string) {
	n := &dNode{data: val}
	if l.tail == nil {
		l.head = n
		l.tail = n
	} else {
		n.prev = l.tail
		l.tail.next = n
		l.tail = n
	}
	l.size++
}

func (l *DoublyList) InsertBeforeAt(index int, val string) error {
	if index < 0 || index > l.size {
		return errors.New("index out of range")
	}
	if index == 0 {
		l.PushFront(val)
		return nil
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	n := &dNode{data: val, prev: cur.prev, next: cur}
	cur.prev.next = n
	cur.prev = n
	l.size++
	return nil
}

func (l *DoublyList) InsertAfterAt(index int, val string) error {
	if index < 0 || index >= l.size {
		return errors.New("index out of range")
	}
	if index == l.size-1 {
		l.PushBack(val)
		return nil
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	n := &dNode{data: val, next: cur.next, prev: cur}
	cur.next.prev = n
	cur.next = n
	l.size++
	return nil
}

func (l *DoublyList) PopFront() error {
	if l.head == nil {
		return errors.New("list is empty")
	}
	l.head = l.head.next
	if l.head != nil {
		l.head.prev = nil
	} else {
		l.tail = nil
	}
	l.size--
	return nil
}

func (l *DoublyList) PopBack() error {
	if l.tail == nil {
		return errors.New("list is empty")
	}
	l.tail = l.tail.prev
	if l.tail != nil {
		l.tail.next = nil
	} else {
		l.head = nil
	}
	l.size--
	return nil
}

func (l *DoublyList) RemoveAt(index int) error {
	if index < 0 || index >= l.size {
		return errors.New("index out of range")
	}
	if index == 0 {
		return l.PopFront()
	}
	if index == l.size-1 {
		return l.PopBack()
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	cur.prev.next = cur.next
	cur.next.prev = cur.prev
	l.size--
	return nil
}

func (l *DoublyList) RemoveByValue(val string) {
	cur := l.head
	for cur != nil && cur.data != val {
		cur = cur.next
	}
	if cur == nil {
		return
	}
	if cur == l.head {
		l.PopFront()
		return
	}
	if cur == l.tail {
		l.PopBack()
		return
	}
	cur.prev.next = cur.next
	cur.next.prev = cur.prev
	l.size--
}

func (l *DoublyList) Find(val string) bool {
	cur := l.head
	for cur != nil {
		if cur.data == val {
			return true
		}
		cur = cur.next
	}
	return false
}

func (l *DoublyList) Print() {
	cur := l.head
	for cur != nil {
		fmt.Print(cur.data, " <-> ")
		cur = cur.next
	}
	fmt.Print("NULL")
}

func (l *DoublyList) GetData() []string {
	res := []string{}
	cur := l.head
	for cur != nil {
		res = append(res, cur.data)
		cur = cur.next
	}
	return res
}

func (l *DoublyList) SetData(d []string) {
	l.head = nil
	l.tail = nil
	l.size = 0
	for _, v := range d {
		l.PushBack(v)
	}
}
