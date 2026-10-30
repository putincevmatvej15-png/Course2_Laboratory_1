package main

import (
	"errors"
	"fmt"
)

type MyQueue struct {
	data []string
}

func (q *MyQueue) Push(val string) { q.data = append(q.data, val) }

func (q *MyQueue) Pop() (string, error) {
	if len(q.data) == 0 {
		return "", errors.New("queue is empty")
	}
	v := q.data[0]
	q.data = q.data[1:]
	return v, nil
}

func (q *MyQueue) Print() {
	for _, v := range q.data {
		fmt.Print(v, " ")
	}
}

func (q *MyQueue) GetData() []string { return q.data }
func (q *MyQueue) SetData(d []string) { q.data = d }
