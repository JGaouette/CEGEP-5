package main

import (
	"fmt"
	"github.com/go-playground/validator/v10"
	_ "github.com/go-playground/validator/v10"
	"math/big"
	"math/rand"
	"time"

	r "crypto/rand"
)

type User struct {
	Email string `json:"email" validate:"required,email"`
	Name  string `json:"name" validate:"required"`
	DA    int    `json:"da" validate:"numeric,min=1000000,max=9999999"`
}

func main() {
	v := validator.New()
	user := User{
		Email: "test@yahoo.ca",
		DA:    1234567,
	}
	err := v.Struct(user)

	for _, e := range err.(validator.ValidationErrors) {
		switch e.Field() {
		case "Email":
			switch e.Tag() {
			case "required":
				fmt.Println("Email is required")
			case "email":
				fmt.Println("Email is not valid")
			}
		case "DA":
			fmt.Println("DA is not valid")
		case "Name":
			fmt.Println("Name is not valid")
		}
	}

	//Faux aléatoire
	rand.Seed(time.Now().Unix())
	r1 := rand.Intn(100)
	fmt.Println(r1)

	//Vrais aléatoire
	r2, _ := r.Int(r.Reader, big.NewInt(100))
	fmt.Println(r2)
}
