#ifndef DIRETORIO_HPP
#define DIRETORIO_HPP

#include <iostream>
#include <string>
#include <vector>

#include "./Balde.hpp"

class Diretorio
{
	private:
		std::vector<Balde*> baldes;
		size_t globalDepth;
		
	public:
		Diretorio(size_t tamBalde) {
			this->globalDepth = 1;

			//primeiro digito 0
			this->baldes.push_back(new Balde(1, tamBalde));

			//primeiro digito 1
			this->baldes.push_back(new Balde(1, tamBalde));
		}

		bool buscar(const std::string& pseudoKey);
		void inserir(const std::string& pseudoKey);
		size_t dividirBalde(const std::string& pseudoKey, size_t indice);
		void duplicar();

		size_t hash(const std::string& str);
		const size_t& atualizarProfundidade();

		const size_t& getGlobalDepth() { return this->globalDepth; };
		
		void imprimir();
};

#endif /* DIRETORIO_HPP */