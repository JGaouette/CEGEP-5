CREATE DATABASE Atelier_01_BD
On PRIMARY
(
	NAME = Atelier_01_BD,
	FILENAME = "C:\Users\Public\Atelier_01.mdf",
	SIZE = 5MB, 
	MAXSIZE = 5MB, 
	FILEGROWTH = 1MB
)
LOG ON
(
	NAME = Atelier_01_BD_log,
	FILENAME = "C:\Users\Public\Atelier_01_log.ldf",
	SIZE = 1MB, 
	MAXSIZE = 1MB, 
	FILEGROWTH = 2KB
)
GO

USE Atelier_01_BD
CREATE TABLE Produits(
	ProdID int NOT NULL IDENTITY(0,1),
	ProdNom nvarchar(50) NOT NULL,
	ProdPrix money,
	CONSTRAINT PK_Prod PRIMARY KEY (ProdID)
)

CREATE TABLE Vendeurs(
	VendID int NOT NULL IDENTITY(0,1),
	VendNom nvarchar(50) NOT NULL,
	VendNaissance date NOT NULL,
	CONSTRAINT PK_Vend PRIMARY KEY (VendID)
)

CREATE TABLE Ventes(
	VentID int NOT NULL IDENTITY(0,1),
	VentProdID int NOT NULL,
	VentVendID int NOT NULL,
	CONSTRAINT PK_Vent PRIMARY KEY (VentID),
	CONSTRAINT FK_VentProd FOREIGN KEY (VentProdID)
		REFERENCES Produits (ProdID),
	CONSTRAINT FK_VentVend FOREIGN KEY (VentVendID)
		REFERENCES Vendeurs (VendID)
)