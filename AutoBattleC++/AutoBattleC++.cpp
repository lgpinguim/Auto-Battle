// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "Battlefield.h"
#include <iostream>

int main()
{
	const auto turnHandler = new TurnHandler();

	turnHandler->StartGame();
}
