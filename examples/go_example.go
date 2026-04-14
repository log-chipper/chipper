package main

import "github.com/log-chipper/chipper"

func main() {
	client, err := chipper.NewClient()
	if err != nil {
		panic(err)
	}
	defer client.Close()

	client.Log("info", "hello from go")
}

