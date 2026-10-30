package main

import (
	"fmt"
	"os"
	"strconv"
	"strings"
)

func main() {
	filename := "data.json"
	query := ""

	args := os.Args[1:]
	for i := 0; i < len(args); i++ {
		switch args[i] {
		case "--file":
			if i+1 < len(args) { filename = args[i+1]; i++ }
		case "--query":
			if i+1 < len(args) { query = args[i+1]; i++ }
		}
	}

	db := NewDatabase()
	if err := db.LoadFromFile(filename); err != nil {
		fmt.Fprintln(os.Stderr, "Error loading:", err)
	}

	if query == "" { return }

	tokens := strings.Fields(query)
	if len(tokens) < 2 { return }

	cmd := tokens[0]
	name := tokens[1]
	val := ""
	if len(tokens) > 2 { val = tokens[2] }

	defer func() {
		if r := recover(); r != nil {
			fmt.Fprintln(os.Stderr, "Error:", r)
		}
	}()

	atoi := func(s string) int {
		v, err := strconv.Atoi(s)
		if err != nil { panic("expected integer") }
		return v
	}

	getOrCreateA := func(m map[string]*MyArray, n string) *MyArray {
		if _, ok := m[n]; !ok { m[n] = &MyArray{} }
		return m[n]
	}
	getOrCreateF := func(m map[string]*ForwardList, n string) *ForwardList {
		if _, ok := m[n]; !ok { m[n] = &ForwardList{} }
		return m[n]
	}
	getOrCreateD := func(m map[string]*DoublyList, n string) *DoublyList {
		if _, ok := m[n]; !ok { m[n] = &DoublyList{} }
		return m[n]
	}
	getOrCreateS := func(m map[string]*MyStack, n string) *MyStack {
		if _, ok := m[n]; !ok { m[n] = &MyStack{} }
		return m[n]
	}
	getOrCreateQ := func(m map[string]*MyQueue, n string) *MyQueue {
		if _, ok := m[n]; !ok { m[n] = &MyQueue{} }
		return m[n]
	}

	saveAndSay := func(msg string) {
		if err := db.SaveToFile(filename); err != nil {
			fmt.Fprintln(os.Stderr, "Save error:", err)
		}
		fmt.Println(msg)
	}

	switch cmd {
	case "PRINT":
		found := false
		if v, ok := db.Arrays[name]; ok { fmt.Print(name, ": "); v.Print(); fmt.Println(); found = true }
		if v, ok := db.ForwardLists[name]; ok { fmt.Print(name, ": "); v.Print(); fmt.Println(); found = true }
		if v, ok := db.DoublyLists[name]; ok { fmt.Print(name, ": "); v.Print(); fmt.Println(); found = true }
		if v, ok := db.Stacks[name]; ok { fmt.Print(name, ": "); v.Print(); fmt.Println(); found = true }
		if v, ok := db.Queues[name]; ok { fmt.Print(name, ": "); v.Print(); fmt.Println(); found = true }
		if !found { fmt.Fprintf(os.Stderr, "Error: Container '%s' not found\n", name) }

	case "MPUSH": getOrCreateA(db.Arrays, name).PushBack(val); saveAndSay("MPUSH ok")
	case "MINSERT": getOrCreateA(db.Arrays, name).InsertAt(atoi(val), tokens[3]); saveAndSay("MINSERT ok")
	case "MGET": v, _ := getOrCreateA(db.Arrays, name).Get(atoi(val)); fmt.Println(v)
	case "MUPDATE": getOrCreateA(db.Arrays, name).UpdateAt(atoi(val), tokens[3]); saveAndSay("MUPDATE ok")
	case "MDEL_AT": getOrCreateA(db.Arrays, name).RemoveAt(atoi(val)); saveAndSay("MDEL_AT ok")
	case "MDEL_VALUE": getOrCreateA(db.Arrays, name).RemoveByValue(val); saveAndSay("MDEL_VALUE ok")
	case "MLEN": fmt.Println(getOrCreateA(db.Arrays, name).Length())

	case "FPUSH_FRONT": getOrCreateF(db.ForwardLists, name).PushFront(val); saveAndSay("FPUSH_FRONT ok")
	case "FPUSH_BACK": getOrCreateF(db.ForwardLists, name).PushBack(val); saveAndSay("FPUSH_BACK ok")
	case "FINSERT_BEFORE_AT": getOrCreateF(db.ForwardLists, name).InsertBeforeAt(atoi(val), tokens[3]); saveAndSay("FINSERT_BEFORE_AT ok")
	case "FINSERT_AFTER_AT": getOrCreateF(db.ForwardLists, name).InsertAfterAt(atoi(val), tokens[3]); saveAndSay("FINSERT_AFTER_AT ok")
	case "FPOP_FRONT": getOrCreateF(db.ForwardLists, name).PopFront(); saveAndSay("FPOP_FRONT ok")
	case "FPOP_BACK": getOrCreateF(db.ForwardLists, name).PopBack(); saveAndSay("FPOP_BACK ok")
	case "FDEL_AT": getOrCreateF(db.ForwardLists, name).RemoveAt(atoi(val)); saveAndSay("FDEL_AT ok")
	case "FDEL_VALUE": getOrCreateF(db.ForwardLists, name).RemoveByValue(val); saveAndSay("FDEL_VALUE ok")
	case "FGET": fmt.Println(getOrCreateF(db.ForwardLists, name).Find(val))

	case "LPUSH_FRONT": getOrCreateD(db.DoublyLists, name).PushFront(val); saveAndSay("LPUSH_FRONT ok")
	case "LPUSH_BACK": getOrCreateD(db.DoublyLists, name).PushBack(val); saveAndSay("LPUSH_BACK ok")
	case "LINSERT_BEFORE_AT": getOrCreateD(db.DoublyLists, name).InsertBeforeAt(atoi(val), tokens[3]); saveAndSay("LINSERT_BEFORE_AT ok")
	case "LINSERT_AFTER_AT": getOrCreateD(db.DoublyLists, name).InsertAfterAt(atoi(val), tokens[3]); saveAndSay("LINSERT_AFTER_AT ok")
	case "LPOP_FRONT": getOrCreateD(db.DoublyLists, name).PopFront(); saveAndSay("LPOP_FRONT ok")
	case "LPOP_BACK": getOrCreateD(db.DoublyLists, name).PopBack(); saveAndSay("LPOP_BACK ok")
	case "LDEL_AT": getOrCreateD(db.DoublyLists, name).RemoveAt(atoi(val)); saveAndSay("LDEL_AT ok")
	case "LDEL_VALUE": getOrCreateD(db.DoublyLists, name).RemoveByValue(val); saveAndSay("LDEL_VALUE ok")
	case "LGET": fmt.Println(getOrCreateD(db.DoublyLists, name).Find(val))

	case "SPUSH": getOrCreateS(db.Stacks, name).Push(val); saveAndSay("SPUSH ok")
	case "SPOP": v, _ := getOrCreateS(db.Stacks, name).Pop(); fmt.Println(v); db.SaveToFile(filename)
	
	case "QPUSH": getOrCreateQ(db.Queues, name).Push(val); saveAndSay("QPUSH ok")
	case "QPOP": v, _ := getOrCreateQ(db.Queues, name).Pop(); fmt.Println(v); db.SaveToFile(filename)

	default:
		fmt.Fprintln(os.Stderr, "Unknown command:", cmd)
	}
}
