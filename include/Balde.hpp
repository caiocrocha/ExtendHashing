#ifndef BALDE_HPP
#define BALDE_HPP

#include <iostream>
#include <string>
#include <vector>

class Balde
{
	private:
		std::vector<std::string> keys;
		size_t localDepth;
		size_t tamMax;

		std::vector<std::string>::iterator buscarPosicao(const std::string& pseudoKey);
		
	public:
		Balde(size_t localDepth, size_t tamMax) {
			this->localDepth = localDepth;
			this->tamMax = tamMax;
		}

		const size_t& atualizarProfundidade();
		bool buscar(const std::string& pseudoKey);
		int inserir(const std::string& pseudoKey);
		Balde* dividir(size_t novoIndice, size_t globalDepth);

		size_t getLocalDepth() { return this->localDepth; };
		size_t getTamBalde() { return this->keys.size(); };

		void imprimir(std::ofstream& log, size_t n);
};

#endif /* BALDE_HPP */