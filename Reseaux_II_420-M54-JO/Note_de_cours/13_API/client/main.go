package main

import (
	"encoding/json"
	"fmt"
	"io"
	"net/http"
	"net/url"
)

type DogFact struct {
	Facts   []string `json:"facts"`
	Success bool     `json:"success"`
}

func main() {

	// Site génial d'API : https://github.com/public-apis/public-apis
	// Permet de lire un API (exemple dog)
	var webSiteURL = "http://dog-api.kinduff.com/api/facts"
	u, _ := url.Parse(webSiteURL)

	values, _ := url.ParseQuery(u.RawQuery)
	values.Set("number", "1")
	u.RawQuery = values.Encode()

	req, _ := http.NewRequest(
		http.MethodGet,
		u.String(),
		nil,
	)

	req.Header.Add("Accept", "application/json")
	res, _ := http.DefaultClient.Do(req)
	responseBytes, _ := io.ReadAll(res.Body)

	var dogFact DogFact
	json.Unmarshal(responseBytes, &dogFact)

	fmt.Println(dogFact)

	/*
		var webSiteURL2 = "https://api.waifu.pics/sfw/neko"
		u2, _ := url.Parse(webSiteURL2)
		req2, _ := http.NewRequest(
			http.MethodGet,
			u2.String(),
			nil,
		)
		req2.Header.Add("Accept", "application/json")
		res2, _ := http.DefaultClient.Do(req2)
		responseBytes2, _ := io.ReadAll(res2.Body)
		fmt.Println(string(responseBytes2))
	*/
}
