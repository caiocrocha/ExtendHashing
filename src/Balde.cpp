#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "../include/Balde.hpp"
#include "../include/utils.hpp"

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
	auto it = buscarPosicao(pseudoKey);
	if(it != this->keys.end() && pseudoKey == *it)
	{
		std::cout << "Esta pseudo-chave já foi inserida!" << std::endl;
		return -1;
	}

	//se balde estiver cheio, dividir balde
	if(this->keys.size() >= this->tamMax)
		return 0;
	
	//insere na ordem crescente
	this->keys.insert(it, pseudoKey);
	//std::cout << pseudoKey << " " << sizeof(this->keys[0]) << " bytes" << std::endl;
	return 1;
}

Balde* Balde::dividir(size_t novoIndice, size_t globalDepth)
{
	//atualiza profundidade local
	size_t localDepth = this->atualizarProfundidade();

	//vetor das pseudo-chaves do balde atual
	std::vector<std::string> auxKeys;
	Balde* novoBalde = new Balde(localDepth, this->getTamBalde());

	for(auto it = this->keys.begin(); it != this->keys.end(); ++it)
	{
		//se novoIndice <= indice da pseudo-chave atual, entao adiciona chave ao novo balde
		if(novoIndice <= hash(*it, globalDepth))
			novoBalde->keys.push_back(*it);
		else //mantem pseudo-chave no balde atual
			auxKeys.push_back(*it);
	}

	//atualiza pseudo-chaves do balde atual
	this->keys.clear();
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
