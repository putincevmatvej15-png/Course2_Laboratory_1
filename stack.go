package main

import (
	"errors"
	"fmt"
)

type MyStack struct {
	data []string
}

func (s *MyStack) Push(val string) { s.data = append(s.data, val) }

func (s *MyStack) Pop() (string, error) {
	if len(s.data) == 0 {
		return "", errors.New("stack is empty")
	}
	v := s.data[len(s.data)-1]
	s.data = s.data[:len(s.data)-1]
	return v, nil
}

func (s *MyStack) Print() {
	for i := len(s.data) - 1; i >= 0; i-- {
		fmt.Print(s.data[i], " ")
	}
}

func (s *MyStack) GetData() []string { return s.data }
func (s *MyStack) SetData(d []string) { s.data = d }
