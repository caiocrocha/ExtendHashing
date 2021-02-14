#include <iostream>
#include <string>
#include <random>
#include <fstream>

#include "include/Balde.hpp"
#include "include/Diretorio.hpp"

int main()
{
	size_t tamMax = 2, nbits = 16;
	//std::cout << "Tamanho M dos baldes: ";
	//std::cin >> tamBalde;

	//std::cout << "Numero de bits da pseudochave: ";
	//std::cin >> nbits;

	Diretorio* d = new Diretorio(tamMax, nbits);
	
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> dist('0', '1'); // define the range

	for(size_t i = 0; i < 100; ++i) {
		std::string s;
		for(size_t i = 0; i < nbits; ++i)
        	s += dist(gen);
		std::cout << s << std::endl;
		d->inserir(s);
	}

	std::cout << "Imprimindo diretorio para arquivo `log`" << std::endl;
	std::ofstream log;
	log.open("log");

	if(!log)
	{
		std::cerr << "Falha ao abrir arquivo `log`" << std::endl;
		exit(1);
	}

	d->imprimir(log);

	return 0;
}
