#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "../include/Balde.hpp"

const size_t& Balde::atualizarProfundidade()
{
	return ++(this->localDepth);
}

std::vector<std::string>::iterator Balde::buscarPosicao(const std::string& pseudoKey)
{
	std::vector<std::string>::iterator it = this->keys.begin();
	//busca posicao em que a pseudo-chave pode ser inserida
	//mantendo a ordenacao do vetor
	while(it != this->keys.end() && pseudoKey.compare(*it) > 0) ++it;
	return it;
}

bool Balde::buscar(const std::string& pseudoKey)
{
	auto it = buscarPosicao(pseudoKey);
	return it != this->keys.end() && pseudoKey == *it;
}

int Balde::inserir(const std::string& pseudoKey)
{
	//se balde estiver cheio, dividir balde
	if(this->keys.size() >= tamBalde)
		return -1;

	auto it = buscarPosicao(pseudoKey);

	if(it != this->keys.end() && pseudoKey == *it)
	{
		std::cout << "Esta pseudo-chave já foi inserida!" << std::endl;
		return 0;
	}
	
	//insere na ordem crescente
	this->keys.insert(it, pseudoKey);
	std::cout << pseudoKey << " " << sizeof(this->keys[0]) << " bytes" << std::endl;
	return 1;
}

Balde* Balde::dividir()
{
	size_t localDepth = this->atualizarProfundidade();
	std::cout << "Atualiza profundidade: " << localDepth << std::endl;

	std::vector<std::string> auxKeys;
	Balde* novoBalde = new Balde(localDepth, this->getTamBalde());
	
	auto it = this->keys.begin();
	for(auto next = it+1; next != this->keys.end(); ++it, ++next) {
		//como o vetor esta ordenado
		//se primeiros digitos de atual == primeiros digitos de proximo
		//mantem pseudo-chaves no balde atual
		if((*it).substr(0, localDepth) == (*next).substr(0, localDepth)) {
			auxKeys.push_back(std::move(*it));
			auxKeys.push_back(std::move(*next));
		}
		//se primeiros digitos de atual < primeiros digitos de proximo
		//mantem menor pseudo-chave no balde atual e insere maior pseudo-chave no novo balde
		else {
			auxKeys.push_back(std::move(*it));
			novoBalde->keys.push_back(std::move(*next));
		}
	}

	/*
	std::cout << "\n\nBalde atual: ";
	for(size_t i = 0; i < auxKeys.size(); ++i)
		std::cout << auxKeys[i] << ", ";

	std::cout << "\nNovo balde: ";
	for(size_t i = 0; i < novoBalde->keys.size(); ++i)
		std::cout << novoBalde->keys[i] << ", ";

	std::cout << "\n\n";
	*/

	//atualiza pseudo-chaves do balde atual
	this->keys = auxKeys;
	return novoBalde;
}

void Balde::imprimir(size_t n)
{
	auto it = this->keys.begin();
	if(it == this->keys.end()) {
		std::cout << "Empty" << std::endl;
		return;
	}

	std::cout << (*it) << "\tEndereco: " << this << std::endl;
	for(it = it+1; it != this->keys.end(); ++it)
		std::cout << std::setfill(' ') << std::setw(n + (*it).size()) << (*it) << std::endl;
}
