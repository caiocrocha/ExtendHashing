#include <iostream>
#include <string>
#include <vector>

#include "include/Balde.hpp"
#include "include/Diretorio.hpp"

int main()
{
	size_t tamBalde = 2, nbits = 3;
	//std::cout << "Tamanho M dos baldes: ";
	//std::cin >> tamBalde;

	//std::cout << "Numero de bits da pseudochave: ";
	//std::cin >> nbits;
	
	Diretorio* d = new Diretorio(tamBalde);
	d->inserir("001");
	d->inserir("010");
	d->inserir("100");
	d->inserir("101");
	d->inserir("110");
	d->imprimir();

	return 0;
}