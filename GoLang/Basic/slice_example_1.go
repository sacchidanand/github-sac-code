package main

import "fmt"

func main() {
	fmt.Println("Slice example-1")

	// Option 1
	// s := make([]byte, 5, 5)

	//Option 2
	s := []byte{1, 2, 3, 4, 5}
	printSlice(s, "Just Created")

	s = s[:]
	printSlice(s, "changed to [:]")

	s = s[2:3]
	printSlice(s, "changed to [2:3]")

	s = s[0:2]
	printSlice(s, "changed to [0:2]")

	s = s[:cap(s)]
	printSlice(s, "changed to [:cap(s)]")
	fmt.Println(s[2])

	//copy operation for newly created slice t that does not share same underlying array
	var t []byte
	t = make([]byte, len(s), (cap(s)+1)*2)
	copyCounter := copy(t, s)
	fmt.Println("copyCounter=", copyCounter)
	printSlice(t, "copy operation for slice")

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
changed to [2:3]
Actual data in  slice [3]
Len :  1
Cap (Max len) :  3

##############################
changed to [0:2]
Actual data in  slice [3 4]
Len :  2
Cap (Max len) :  3

##############################
changed to [:cap(s)]
Actual data in  slice [3 4 5]
Len :  3
Cap (Max len) :  3

##############################
5
copyCounter= 3
copy operation for slice
Actual data in  slice [3 4 5]
Len :  3
Cap (Max len) :  8

##############################
shares same underlying array
Actual data in  slice [3 4 5]
Len :  3
Cap (Max len) :  3

##############################
panic: runtime error: slice bounds out of range

goroutine 1 [running]:
main.main()
        /Users/sacchidanand/Desktop/go_code_video/code/slice/code1/slice1.go:44 +0x36b
exit status 2
'''

*/
