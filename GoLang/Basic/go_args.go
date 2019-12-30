package main

import "fmt"

func main() {
	fmt.Println("argument in go example")
	a := 10
	b := 20
	c := 0
	// sum(a, b, c)
	// fmt.Println("sum()", a, b, c)

	sumPtr(&a, &b, &c)
	fmt.Println("sumPtr()", a, b, c)
}

func sum(m, n, z int) {
	fmt.Println("Before", m, n, z)
	z = m + n
	fmt.Println("After", m, n, z)
}

func sumPtr(m, n, z *int) {
	fmt.Println("Before", *m, *n, *z)
	*z = *m + *n
	fmt.Println("After", *m, *n, *z)
}

/*
Output

argument in go example
Before 10 20 0
After 10 20 30
sumPtr() 10 20 30

*/
