#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>

#include "../include/Balde.hpp"

const size_t& Balde::atualizarProfundidade()
{
	return ++(this->localDepth);
}

bool Balde::buscar(const std::string& pseudoKey)
{
	auto it = buscarPosicao(pseudoKey);
	return it != this->keys.end() && pseudoKey == *it;
}

std::vector<std::string>::iterator Balde::buscarPosicao(const std::string& pseudoKey)
{
	std::vector<std::string>::iterator it = this->keys.begin();
	while(it != this->keys.end() && pseudoKey < *it) ++it;
	return it;
}

int Balde::inserir(const std::string& pseudoKey)
{
	//se balde estiver cheio, dividir balde
	if(this->keys.size() >= tamBalde) {
		this->atualizarProfundidade();
		return -1;
	}

	auto it = buscarPosicao(pseudoKey);

	//se tiver encontrado, entao nao precisa inserir novamente
	if(it != this->keys.end() && pseudoKey == *it)
		return 0;

	//insere na ordem crescente
	this->keys.insert(it, pseudoKey);
	return 1;
}

Balde* Balde::dividir()
{
	size_t localDepth = this->atualizarProfundidade();

	std::vector<std::string> auxKeys;
	Balde* novoBalde = new Balde(localDepth, this->getTamBalde());
	
	auto it = this->keys.begin();
	for(auto next = it+1; next != this->keys.end(); ++it, ++next) {
		//se primeiros digitos de atual < primeiros digitos de proximo
		//insere maior pseudo-chave no novo balde
		if((*it).substr(0, localDepth) < (*next).substr(0, localDepth)) {
			auxKeys.push_back(*it);
			novoBalde->keys.push_back(*next);
		}
		//como o vetor esta ordenado
		//se primeiros digitos de atual == primeiros digitos de proximo
		//mantem pseudo-chaves no balde atual
		else {
			auxKeys.push_back(*it);
			auxKeys.push_back(*next);
		}
	}

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