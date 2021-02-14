#include <iostream>
#include <string>
#include <random>

#include "include/Balde.hpp"
#include "include/Diretorio.hpp"

int main()
{
	size_t tamMax = 2, nbits = 4;
	//std::cout << "Tamanho M dos baldes: ";
	//std::cin >> tamBalde;

	//std::cout << "Numero de bits da pseudochave: ";
	//std::cin >> nbits;

	Diretorio* d = new Diretorio(tamMax, nbits);
	
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

	d->inserir("1100");
	d->imprimir();
	d->inserir("1101");
	d->imprimir();
	d->inserir("0110");
	d->imprimir();
	d->inserir("1011");
	d->imprimir();
	d->inserir("1010"); // ja foi inserida
	d->imprimir();
	d->inserir("0001");
	d->imprimir();
	d->inserir("1101");
	d->imprimir();
	d->inserir("0001");
	d->imprimir();
	d->inserir("0110");
	d->imprimir();
	d->inserir("1010");
	d->imprimir();

	return 0;
}
