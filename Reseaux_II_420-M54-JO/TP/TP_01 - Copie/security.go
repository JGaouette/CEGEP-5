package main

import "golang.org/x/crypto/bcrypt"

func hash(toHash string) string {
	bytes, _ := bcrypt.GenerateFromPassword([]byte(toHash), 14)
	return string(bytes)
}

func checkHash(password, hash string) bool {
	err := bcrypt.CompareHashAndPassword([]byte(hash), []byte(password))
	return err == nil
}
