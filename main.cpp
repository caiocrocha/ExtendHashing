#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "include/Balde.hpp"
#include "include/Diretorio.hpp"

int main()
{
	size_t tamMax = 0, nbits = 0;
	while(tamMax < 2)
	{	
		std::cout << "Digite o tamanho M dos baldes (deve ser maior que 1): ";
		std::cin >> tamMax;
	}

	while(nbits < 4)
	{
		std::cout << "Digite o numero de bits da pseudochave (4 ou mais): ";
		std::cin >> nbits;
	}

	Diretorio* d = new Diretorio(tamMax, nbits);
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> dist('0', '1'); // define the range

	size_t nInsercoes;
	std::cout << "Digite o numero de insercoes: ";
	std::cin >> nInsercoes;
	
	size_t inseridos = 0;
	bool padronizado;
	std::cout << "Gerar binarios padronizados (casas iniciais iguais)?" << std::endl;
	std::cout << "Digite 1 (Sim) ou 0 (Nao): ";
	std::cin >> padronizado;

	if(padronizado)
	{
		for(size_t i = 0; i < nInsercoes; ++i) {
			std::string s(nbits/2, '0');
			for(size_t i = 0; i < nbits/2; ++i)
				s += dist(gen);
			inseridos += d->inserir(s);
		}
	}
	else
	{
		for(size_t i = 0; i < nInsercoes; ++i) {
			std::string s;
			for(size_t i = 0; i < nbits; ++i)
				s += dist(gen);
			inseridos += d->inserir(s);
		}
	}

	float fatorCarga = inseridos / (float) (d->getNBaldes() * tamMax);
	std::cout << "Inseridos: " << inseridos << std::endl;
	std::cout << "Numero de baldes: " << d->getNBaldes() << std::endl;
	std::cout << "Fator de carga: " << fatorCarga << std::endl;
	std::cout << "Tamanho do diretorio: " << d->getTamDiretorio() << std::endl;
	std::cout << "Ocupacao da memoria (bytes): " << d->getTamDiretorioBytes() << std::endl;

	if(nbits <= 4) {
		std::cout << "Imprimindo diretorio para arquivo `diretorio.log`" << std::endl;
		std::ofstream log;
		log.open("diretorio.log");

		if(!log)
		{
			std::cerr << "Falha ao abrir arquivo `diretorio.log`" << std::endl;
			exit(1);
		}

		d->imprimir(log);
		log.close();
	}

	return 0;
}
