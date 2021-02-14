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
		size_t nbits;
		
	public:
		Diretorio(size_t tamBalde, size_t nbits) {
			this->globalDepth = 1;
			this->nbits = nbits;

			//primeiro digito 0
			this->baldes.push_back(new Balde(1, tamBalde));

			//primeiro digito 1
			this->baldes.push_back(new Balde(1, tamBalde));
		}

		bool buscar(std::string pseudoKey);
		int inserir(std::string pseudoKey);
		int dividirBalde(const std::string& pseudoKey, size_t indice);
		void duplicar();

		const size_t& atualizarProfundidade();
		const size_t& getGlobalDepth() { return this->globalDepth; };
		
		void imprimir(std::ofstream& log);
		size_t getTamDiretorio();
		size_t getNBaldes();
		size_t getTamDiretorioBytes();

};

#endif /* DIRETORIO_HPP */