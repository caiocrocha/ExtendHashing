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
		size_t tamBalde;

		std::vector<std::string>::iterator buscarPosicao(const std::string& pseudoKey);
		
	public:
		Balde(size_t localDepth, size_t tamBalde) {
			this->localDepth = localDepth;
			this->tamBalde = tamBalde;
		}

		const size_t& atualizarProfundidade();
		bool buscar(const std::string& pseudoKey);
		int inserir(const std::string& pseudoKey);
		Balde* dividir();

		const size_t& getLocalDepth() { return this->localDepth; };
		const size_t& getTamBalde() { return this->tamBalde; };

		void imprimir(size_t n);
};

#endif /* BALDE_HPP */