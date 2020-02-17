package main

import (
	"flag"
	"fmt"
	"os"
)

func main() {
	args := os.Args
	fmt.Println(len(args), "\n", args)
	fmt.Println("without binary program name", args[1:])

	// this line will give error
	// fmt.Println("without binary program name", args[2:])

	namePtr := flag.String("name", "john", "a string")
	flag.Parse()

	fmt.Println(*namePtr)

	fmt.Println("Remaining tailed args which are not identified by flags", flag.Args())
}
