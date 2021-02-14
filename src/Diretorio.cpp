#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

#include "../include/Balde.hpp"
#include "../include/Diretorio.hpp"
#include "../include/utils.hpp"

const size_t& Diretorio::atualizarProfundidade()
{
	return ++(this->globalDepth);
}

bool Diretorio::buscar(std::string pseudoKey)
{
	if(pseudoKey.size() < this->nbits)
	{
		//Inserir zeros à esquerda
		pseudoKey.insert(0, this->nbits - pseudoKey.size(), '0');
	}
	return this->baldes[getIndice(pseudoKey, this->globalDepth)]->buscar(pseudoKey);
}

int Diretorio::inserir(std::string pseudoKey)
{
	if(pseudoKey.size() > this->nbits)
	{
		std::cout << "Não é possivel inserir esta pseudo-chave, pois ela excede "
				  << "o número de bits especificado" << std::endl;
		return 0;
	}
	else if(pseudoKey.size() < this->nbits)
	{
		//Inserir zeros à esquerda
		pseudoKey.insert(0, this->nbits - pseudoKey.size(), '0');
	}

	size_t indice = getIndice(pseudoKey, this->globalDepth);
	int status = this->baldes[indice]->inserir(pseudoKey);

	if(status == -1)
	{
		status = dividirBalde(pseudoKey, indice);
		if(status)
			this->inserir(pseudoKey);
		else
			return 0;
	}
	return status;
}

int Diretorio::dividirBalde(const std::string& pseudoKey, size_t indice)
{
	if(this->globalDepth < baldes[indice]->getLocalDepth())
	{
		if(this->globalDepth > this->nbits)
			return 0;
		else
			duplicar();
	}

	size_t novoIndice = getIndice(pseudoKey, this->globalDepth);
	Balde* novoBalde = this->baldes[novoIndice]->dividir(novoIndice, this->globalDepth);
	this->baldes[novoIndice] = novoBalde;
	return 1;
}

void Diretorio::duplicar()
{
	this->atualizarProfundidade();
	std::vector<Balde*> auxBaldes(this->baldes.size() * 2);

	for(size_t i = 0; i < this->baldes.size(); ++i)
	{
		auxBaldes[i * 2] = this->baldes[i];
		auxBaldes[i * 2 + 1] = this->baldes[i];
	}
	
	this->baldes.clear();
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

void Diretorio::imprimir(std::ofstream& log)
{
	for(size_t i = 0; i < this->baldes.size(); ++i) {
		log << std::setfill('0') << std::setw(this->globalDepth) << decimalToBinary(i) << " - ";
		this->baldes[i]->imprimir(log, this->globalDepth + 3); //numero de espacos à esquerda
	}
}

size_t Diretorio::getTamDiretorio()
{
	return this->baldes.size();
}

size_t Diretorio::getNBaldes()
{
	size_t nBaldes = 1;
	auto it = this->baldes.begin();
	for(auto next = it+1; next != this->baldes.end(); ++it, ++next)
		if(*it != *next)
			nBaldes++;
	return nBaldes;
}

size_t Diretorio::getTamDiretorioBytes()
{
	size_t tam = sizeof(this->baldes.capacity()) * sizeof(Balde*) + sizeof(this->baldes);
	auto it = this->baldes.begin();
	for(auto next = it+1; next != this->baldes.end(); ++it, ++next)
		if(*it != *next)
			tam += (*it)->getTamBaldeBytes();
	tam += (*it)->getTamBaldeBytes();
	return tam;
}
