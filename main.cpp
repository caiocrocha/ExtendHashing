#include <iostream>
#include <string>
#include <random>

#include "include/Balde.hpp"
#include "include/Diretorio.hpp"

int main()
{
	size_t tamBalde = 2, nbits = 3;
	//std::cout << "Tamanho M dos baldes: ";
	//std::cin >> tamBalde;

	//std::cout << "Numero de bits da pseudochave: ";
	//std::cin >> nbits;

	Diretorio* d = new Diretorio(tamBalde, nbits);
	
	/*
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> dist('0', '1'); // define the range

	for(size_t i = 0; i < 13; ++i) {
		std::string s;
		for(size_t i = 0; i < nbits; ++i)
        	s += dist(gen);
		std::cout << s << std::endl;
		d->inserir(s);
	}
	*/

	d->inserir("010");
	d->inserir("011");
	d->inserir("011");
	d->inserir("110");
	d->inserir("101");
	d->inserir("011"); // ja foi inserida
	d->inserir("010");
	d->inserir("000");
	d->inserir("001");
	d->inserir("111");

	d->imprimir();

	return 0;
}
