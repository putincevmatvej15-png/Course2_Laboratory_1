package main

import (
	"errors"
	"fmt"
)

type fNode struct {
	data string
	next *fNode
}

type ForwardList struct {
	head *fNode
	size int
}

func (l *ForwardList) PushFront(val string) {
	n := &fNode{data: val, next: l.head}
	l.head = n
	l.size++
}

func (l *ForwardList) PushBack(val string) {
	n := &fNode{data: val}
	if l.head == nil {
		l.head = n
	} else {
		cur := l.head
		for cur.next != nil {
			cur = cur.next
		}
		cur.next = n
	}
	l.size++
}

func (l *ForwardList) InsertBeforeAt(index int, val string) error {
	if index < 0 || index > l.size {
		return errors.New("index out of range")
	}
	if index == 0 {
		l.PushFront(val)
		return nil
	}
	cur := l.head
	for i := 0; i < index-1; i++ {
		cur = cur.next
	}
	n := &fNode{data: val, next: cur.next}
	cur.next = n
	l.size++
	return nil
}

func (l *ForwardList) InsertAfterAt(index int, val string) error {
	if index < 0 || index >= l.size {
		return errors.New("index out of range")
	}
	cur := l.head
	for i := 0; i < index; i++ {
		cur = cur.next
	}
	n := &fNode{data: val, next: cur.next}
	cur.next = n
	l.size++
	return nil
}

func (l *ForwardList) InsertBeforeValue(target string, val string) {
	if l.head == nil {
		return
	}
	if l.head.data == target {
		l.PushFront(val)
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.data != target {
		cur = cur.next
	}
	if cur.next != nil {
		n := &fNode{data: val, next: cur.next}
		cur.next = n
		l.size++
	}
}

func (l *ForwardList) InsertAfterValue(target string, val string) {
	cur := l.head
	for cur != nil && cur.data != target {
		cur = cur.next
	}
	if cur != nil {
		n := &fNode{data: val, next: cur.next}
		cur.next = n
		l.size++
	}
}

func (l *ForwardList) PopFront() error {
	if l.head == nil {
		return errors.New("list is empty")
	}
	l.head = l.head.next
	l.size--
	return nil
}

func (l *ForwardList) PopBack() error {
	if l.head == nil {
		return errors.New("list is empty")
	}
	if l.head.next == nil {
		l.head = nil
		l.size--
		return nil
	}
	cur := l.head
	for cur.next.next != nil {
		cur = cur.next
	}
	cur.next = nil
	l.size--
	return nil
}

func (l *ForwardList) RemoveAt(index int) error {
	if index < 0 || index >= l.size {
		return errors.New("index out of range")
	}
	if index == 0 {
		return l.PopFront()
	}
	cur := l.head
	for i := 0; i < index-1; i++ {
		cur = cur.next
	}
	cur.next = cur.next.next
	l.size--
	return nil
}

func (l *ForwardList) RemoveByValue(val string) {
	if l.head == nil {
		return
	}
	if l.head.data == val {
		l.head = l.head.next
		l.size--
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.data != val {
		cur = cur.next
	}
	if cur.next != nil {
		cur.next = cur.next.next
		l.size--
	}
}

func (l *ForwardList) RemoveAllByValue(val string) {
	for l.head != nil && l.head.data == val {
		l.PopFront()
	}
	if l.head == nil {
		return
	}
	cur := l.head
	for cur.next != nil {
		if cur.next.data == val {
			cur.next = cur.next.next
			l.size--
		} else {
			cur = cur.next
		}
	}
}

func (l *ForwardList) RemoveBeforeValue(target string) {
	if l.head == nil || l.head.data == target {
		return
	}
	if l.head.next != nil && l.head.next.data == target {
		l.PopFront()
		return
	}
	cur := l.head
	for cur.next != nil && cur.next.next != nil && cur.next.next.data != target {
		cur = cur.next
	}
	if cur.next != nil && cur.next.next != nil {
		cur.next = cur.next.next
		l.size--
	}
}

func (l *ForwardList) RemoveAfterValue(target string) {
	cur := l.head
	for cur != nil && cur.data != target {
		cur = cur.next
	}
	if cur != nil && cur.next != nil {
		cur.next = cur.next.next
		l.size--
	}
}

func (l *ForwardList) Find(val string) bool {
	cur := l.head
	for cur != nil {
		if cur.data == val {
			return true
		}
		cur = cur.next
	}
	return false
}

func (l *ForwardList) Print() {
	cur := l.head
	for cur != nil {
		fmt.Print(cur.data, " -> ")
		cur = cur.next
	}
	fmt.Print("NULL")
}

func (l *ForwardList) GetData() []string {
	res := []string{}
	cur := l.head
	for cur != nil {
		res = append(res, cur.data)
		cur = cur.next
	}
	return res
}

func (l *ForwardList) SetData(d []string) {
	l.head = nil
	l.size = 0
	for _, v := range d {
		l.PushBack(v)
	}
}
