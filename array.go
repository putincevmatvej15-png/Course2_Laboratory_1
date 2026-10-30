package main

import (
	"errors"
	"fmt"
)

type MyArray struct {
	data     []string
	size     int
	capacity int
}

func (a *MyArray) PushBack(val string) {
	if a.size == a.capacity {
		newCap := 2
		if a.capacity > 0 {
			newCap = a.capacity * 2
		}
		newData := make([]string, newCap)
		copy(newData, a.data)
		a.data = newData
		a.capacity = newCap
	}
	a.data[a.size] = val
	a.size++
}

func (a *MyArray) InsertAt(index int, val string) error {
	if index < 0 || index > a.size {
		return errors.New("index out of range")
	}
	a.PushBack("")
	for i := a.size - 1; i > index; i-- {
		a.data[i] = a.data[i-1]
	}
	a.data[index] = val
	return nil
}

func (a *MyArray) RemoveAt(index int) error {
	if index < 0 || index >= a.size {
		return errors.New("index out of range")
	}
	for i := index; i < a.size-1; i++ {
		a.data[i] = a.data[i+1]
	}
	a.size--
	return nil
}

func (a *MyArray) RemoveByValue(val string) {
	for i := 0; i < a.size; i++ {
		if a.data[i] == val {
			a.RemoveAt(i)
			return
		}
	}
}

func (a *MyArray) UpdateAt(index int, val string) error {
	if index < 0 || index >= a.size {
		return errors.New("index out of range")
	}
	a.data[index] = val
	return nil
}

func (a *MyArray) Get(index int) (string, error) {
	if index < 0 || index >= a.size {
		return "", errors.New("index out of range")
	}
	return a.data[index], nil
}

func (a *MyArray) Length() int { return a.size }

func (a *MyArray) Print() {
	fmt.Print("[ ")
	for i := 0; i < a.size; i++ {
		fmt.Print(a.data[i], " ")
	}
	fmt.Print("]")
}

func (a *MyArray) GetData() []string {
	return a.data[:a.size]
}

func (a *MyArray) SetData(d []string) {
	a.size = len(d)
	a.capacity = len(d)
	a.data = make([]string, a.capacity)
	copy(a.data, d)
}
