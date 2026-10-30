package main

import (
	"encoding/json"
	"fmt"
	"os"
)

type Database struct {
	Arrays       map[string]*MyArray
	ForwardLists map[string]*ForwardList
	DoublyLists  map[string]*DoublyList
	Stacks       map[string]*MyStack
	Queues       map[string]*MyQueue
}

func NewDatabase() *Database {
	return &Database{
		Arrays:       make(map[string]*MyArray),
		ForwardLists: make(map[string]*ForwardList),
		DoublyLists:  make(map[string]*DoublyList),
		Stacks:       make(map[string]*MyStack),
		Queues:       make(map[string]*MyQueue),
	}
}

func (db *Database) SaveToFile(filename string) error {
	j := make(map[string]interface{})
	
	arrs := make(map[string][]string)
	for k, v := range db.Arrays { arrs[k] = v.GetData() }
	j["array"] = arrs

	fl := make(map[string][]string)
	for k, v := range db.ForwardLists { fl[k] = v.GetData() }
	j["forward_list"] = fl

	dl := make(map[string][]string)
	for k, v := range db.DoublyLists { dl[k] = v.GetData() }
	j["doubly_list"] = dl

	st := make(map[string][]string)
	for k, v := range db.Stacks { st[k] = v.GetData() }
	j["stack"] = st

	q := make(map[string][]string)
	for k, v := range db.Queues { q[k] = v.GetData() }
	j["queue"] = q

	bytes, err := json.MarshalIndent(j, "", "    ")
	if err != nil { return err }
	return os.WriteFile(filename, bytes, 0644)
}

func (db *Database) LoadFromFile(filename string) error {
	bytes, err := os.ReadFile(filename)
	if err != nil { return nil }

	var j map[string]interface{}
	if err := json.Unmarshal(bytes, &j); err != nil { return err }

	if m, ok := j["array"].(map[string]interface{}); ok {
		for k, v := range m {
			slice := toStringSlice(v)
			db.Arrays[k] = &MyArray{}
			db.Arrays[k].SetData(slice)
		}
	}
	if m, ok := j["forward_list"].(map[string]interface{}); ok {
		for k, v := range m {
			slice := toStringSlice(v)
			db.ForwardLists[k] = &ForwardList{}
			db.ForwardLists[k].SetData(slice)
		}
	}
	if m, ok := j["doubly_list"].(map[string]interface{}); ok {
		for k, v := range m {
			slice := toStringSlice(v)
			db.DoublyLists[k] = &DoublyList{}
			db.DoublyLists[k].SetData(slice)
		}
	}
	if m, ok := j["stack"].(map[string]interface{}); ok {
		for k, v := range m {
			slice := toStringSlice(v)
			db.Stacks[k] = &MyStack{}
			db.Stacks[k].SetData(slice)
		}
	}
	if m, ok := j["queue"].(map[string]interface{}); ok {
		for k, v := range m {
			slice := toStringSlice(v)
			db.Queues[k] = &MyQueue{}
			db.Queues[k].SetData(slice)
		}
	}
	return nil
}

func toStringSlice(v interface{}) []string {
	arr, _ := v.([]interface{})
	res := []string{}
	for _, item := range arr { res = append(res, item.(string)) }
	return res
}
