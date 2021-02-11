#include <iostream>
#include <string>
#include <iomanip>

#include "../include/Balde.hpp"
#include "../include/Diretorio.hpp"

bool Diretorio::buscar(const std::string& pseudoKey)
{
	return this->baldes[hash(pseudoKey)]->buscar(pseudoKey);
}

const size_t& Diretorio::atualizarProfundidade()
{
	return ++(this->globalDepth);
}

size_t Diretorio::hash(const std::string& pseudoKey)
{
	return std::strtoul(pseudoKey.substr(0, this->globalDepth).c_str(), nullptr, 2);
}

void Diretorio::inserir(const std::string& pseudoKey)
{
	size_t i = hash(pseudoKey);
	int status = this->baldes[i]->inserir(pseudoKey);

	if(status == -1)
	{
		dividir(i);
		//verificar retorno
		this->baldes[hash(pseudoKey)]->inserir(pseudoKey);
	}
}

void Diretorio::dividir(size_t i)
{
	if(this->globalDepth < baldes[i]->getLocalDepth())
		duplicar();

	Balde* novoBalde = baldes[i]->dividir();
	this->baldes[i+1] = novoBalde;
}

void Diretorio::duplicar()
{
	this->atualizarProfundidade();
	std::vector<Balde*> auxBaldes;

	for(auto it = this->baldes.begin(); it != this->baldes.end(); ++it)
	{
		auxBaldes.push_back(*it);
		auxBaldes.push_back(*it);
	}
	
	this->baldes = auxBaldes;
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