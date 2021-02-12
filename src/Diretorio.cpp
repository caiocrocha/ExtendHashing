#include <iostream>
#include <string>
#include <iomanip>

#include "../include/Balde.hpp"
#include "../include/Diretorio.hpp"

const size_t& Diretorio::atualizarProfundidade()
{
	return ++(this->globalDepth);
}

size_t Diretorio::hash(const std::string& pseudoKey)
{
	return std::strtoul(pseudoKey.substr(0, this->globalDepth).c_str(), nullptr, 2);
}

bool Diretorio::buscar(std::string pseudoKey)
{
	if(pseudoKey.size() < this->nbits)
	{
		//Inserir zeros à esquerda
		pseudoKey.insert(0, this->nbits - pseudoKey.size(), '0');
	}
	return this->baldes[hash(pseudoKey)]->buscar(pseudoKey);
}

void Diretorio::inserir(std::string pseudoKey)
{
	if(pseudoKey.size() > this->nbits)
	{
		std::cout << "Não é possivel inserir esta pseudo-chave, pois ela excede "
				  << "o número de bits especificado" << std::endl;
		return;
	}
	else if(pseudoKey.size() < this->nbits)
	{
		//Inserir zeros à esquerda
		pseudoKey.insert(0, this->nbits - pseudoKey.size(), '0');
	}

	size_t indice = hash(pseudoKey);
	std::cout << "Indice: " << indice << std::endl;
	int status = this->baldes[indice]->inserir(pseudoKey);

	if(status == -1)
	{
		size_t novoIndice = dividirBalde(pseudoKey, indice);
		//verificar retorno
		std::cout << pseudoKey << " para " << novoIndice << std::endl;
		this->baldes[novoIndice]->imprimir(10);
		std::cout << "\n\n";
		this->baldes[novoIndice]->inserir(pseudoKey);
		this->baldes[novoIndice]->imprimir(10);
		std::cout << "\n\n";
	}
}

size_t Diretorio::dividirBalde(const std::string& pseudoKey, size_t indice)
{
	std::cout << "Divide" << std::endl;
	if(this->globalDepth <= baldes[indice]->getLocalDepth())
		duplicar();

	size_t novoIndice = hash(pseudoKey);
	Balde* novoBalde = baldes[novoIndice]->dividir();
	this->baldes[novoIndice] = novoBalde;
	return novoIndice;
}

void Diretorio::duplicar()
{
	std::cout << "Duplica" << std::endl;
	this->atualizarProfundidade();
	std::vector<Balde*> auxBaldes(this->baldes.size() * 2);

	for(size_t i = 0; i < this->baldes.size(); ++i)
	{
		auxBaldes[i * 2] = this->baldes[i];
		auxBaldes[i * 2 + 1] = this->baldes[i];
	}
	
	this->baldes = auxBaldes;
	std::cout << "\n\nImprimindo diretorio" << std::endl;
	this->imprimir();
	std::cout << "\n\n\n";
}

std::string decimalToBinary(int n)
{
	std::string s = "";
	while(n > 0)
	{
		s += std::to_string(n % 2);
		n /= 2;
	}

	//return reversed string
	return std::string(s.rbegin(), s.rend());
}

void Diretorio::imprimir()
{
	for(size_t i = 0; i < this->baldes.size(); ++i) {
		std::cout << std::setfill('0') << std::setw(this->globalDepth) << decimalToBinary(i) << " - ";
		this->baldes[i]->imprimir(this->globalDepth + 3); //numero de espacos à esquerda
	}
	
}
