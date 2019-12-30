package main

import "fmt"

// https://blog.golang.org/go-slices-usage-and-internals
// https://blog.golang.org/slices

func main() {
	fmt.Println("Slice example-1")

	// Option 1
	// s := make([]byte, 5, 5)

	//Option 2
	s := []byte{1, 2, 3, 4, 5}
	printSlice(s, "Just Created")

	s = s[:]
	printSlice(s, "changed to [:]")

	s = s[1:]
	printSlice(s, "changed to [1:]")

	s = s[2:3]
	printSlice(s, "changed to [2:3]")

	s = s[0:2]
	printSlice(s, "changed to [0:2]")

	s = s[:cap(s)]
	printSlice(s, "changed to [:cap(s)]")
	fmt.Println("s[1]=", s[1])

	//copy operation for newly created slice t that does not share same underlying array
	var t []byte
	t = make([]byte, len(s), (cap(s)+1)*2)
	// copy(dest, source)
	copyCounter := copy(t, s)
	fmt.Println("copyCounter=", copyCounter)
	printSlice(t, "copy operation [cap(s)+1)*2 allocated cap] for slice s to t")

	m := s[:]
	printSlice(m, "shares same underlying array")

	// below operation will give run time panic
	// 	panic: runtime error: slice bounds out of range
	// goroutine 1 [running]:
	// main.main()
	//         /Users/sacchidanand/Desktop/go_video/code/slice/code1/slice1.go:38 +0x36b
	// exit status 2
	copy(m[cap(s):(cap(s)*2)], s)
	printSlice(m, "experiment")

}

func printSlice(s []byte, msg string) {
	// fmt.Println("\n##############################")
	fmt.Println(msg)
	fmt.Println("Actual data in 	slice", s)
	fmt.Println("Len : ", len(s))
	fmt.Println("Cap (Max len) : ", cap(s))
	fmt.Println("\n##############################")
}

/* OutPut:

Slice example-1
Just Created
Actual data in  slice [1 2 3 4 5]
Len :  5
Cap (Max len) :  5

##############################
changed to [:]
Actual data in  slice [1 2 3 4 5]
Len :  5
Cap (Max len) :  5

##############################
changed to [1:]
Actual data in  slice [2 3 4 5]
Len :  4
Cap (Max len) :  4

##############################
changed to [2:3]
Actual data in  slice [4]
Len :  1
Cap (Max len) :  2

##############################
changed to [0:2]
Actual data in  slice [4 5]
Len :  2
Cap (Max len) :  2

##############################
changed to [:cap(s)]
Actual data in  slice [4 5]
Len :  2
Cap (Max len) :  2

##############################
s[1]= 5
copyCounter= 2
copy operation [cap(s)+1)*2 allocated cap] for slice s to t
Actual data in  slice [4 5]
Len :  2
Cap (Max len) :  6

##############################
shares same underlying array
Actual data in  slice [4 5]
Len :  2
Cap (Max len) :  2

##############################
panic: runtime error: slice bounds out of range

goroutine 1 [running]:
main.main()
        /Users/sacchidanand/workspace/github-sac-code/GoLang/Basic/slice_example_1.go:51 +0x3c6
exit status 2



*/
