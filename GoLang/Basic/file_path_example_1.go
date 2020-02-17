package main

import (
	"fmt"
	"strings"
)

func manipulateFilePath(outPath string) {
	fmt.Println("\ninputPath", outPath)

	components := strings.Split(outPath, "/")
	fmt.Println("\ncomponents", components)

	fmt.Println("\n\ncomponents[:len(components)-1]", components[:len(components)-1])

	outPath = strings.Join(components[:len(components)-1], "/")
	fmt.Println("\noutPath", outPath)

	fileName := components[len(components)-1]
	fmt.Println("\nfilename", fileName)

}

func main() {

	inputPath := "/Users/sacchidanand/workspace/github-sac-code/GoLang/Basic"
	manipulateFilePath(inputPath)
}
