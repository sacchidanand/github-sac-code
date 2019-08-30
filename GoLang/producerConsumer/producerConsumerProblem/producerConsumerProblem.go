package main

// Problem:
// Crash is observed, if producer start producing before consumer is ready.
// ******************************************************************************

// Actual execution:
// D:\Go\src\github-sac-code>go run GoLang\producerConsumer\bufferedChannel.go
// fatal error: all goroutines are asleep - deadlock!
// goroutine 1 [chan send]:
// main.main()
//         D:/Go/src/github-sac-code/GoLang/producerConsumer/bufferedChannel.go:14 +0x94
// exit status 2
// ******************************************************************************

// RCA:
// In this code, Producer started producing data and pushing it to channel
// Consumer is actually starts listening after the producer.
// ******************************************************************************

// Solution:
// Correct order should be as follows
// 1. Consumer should be in listening/waiting state for input coming from channel
// 2. Produce should produce after the consumer is actively waiting for input
// This is covered in ProducerConsumerSolution.go
// ******************************************************************************

import (
	"fmt"
	"time"
)

func main() {
	ch := make(chan int, 2)

	// Producer
	ch <- 1
	ch <- 2
	ch <- 3

	fmt.Println("before consumer goroutine")
	// Consumer
	go func() {
		fmt.Println("inside consumer goroutine")
		for item := range ch {
			fmt.Println(item)
		}
	}()

	time.Sleep(5)
}
