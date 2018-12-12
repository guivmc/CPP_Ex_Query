// ExsDeSexta.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

enum CommandType {  defaultType = 0, add = 1, del = 2, info = 3, query = 4 };

enum CommandQueryType { defaultQueryType = 0, fn = 1, ln = 2, bd = 3, pn = 4};

std::map<std::string, CommandType> Prompt;

std::map<std::string, CommandQueryType> PromptQuery;

std::vector<struct CRUD> myList;

struct CRUD
{
	int id;
	std::string name;
	std::string lastName;
	std::string birthday;
	std::string phone;
};

std::vector<std::string> split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	size_t pos = txt.find(ch);
	size_t initialPos = 0;
	strs.clear();

	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs;
}

void DoQuery(std::vector<std::string> queries)
{
	for (int i = 1; i < queries.size(); i++)
	{
		CommandQueryType queryType = PromptQuery[queries.at(i)];

		switch (queryType)
		{
		case fn:
			for (int j = 0; j < myList.size(); j++)
			{
				if (myList.at(j).name.compare(queries.at(i)))
				{
					std::cout << myList.at(j).name + " ";
				}
			}
			break;
		case ln:
			for (int j = 0; j < myList.size(); j++)
			{
				if (myList.at(j).lastName.compare(queries.at(i)))
				{
					std::cout << myList.at(j).lastName + " ";
				}
			}
			break;
		case bd:
			for (int j = 0; j < myList.size(); j++)
			{
				if (myList.at(j).birthday.compare(queries.at(i)))
				{
					std::cout << myList.at(j).birthday + " ";
				}
			}
			break;
		case pn:
			for (int j = 0; j < myList.size(); j++)
			{
				if (myList.at(j).phone.compare(queries.at(i + 1)))
				{
					std::cout << myList.at(j).phone  + " ";
				}
			}
			break;
		default:
			std::cout << std::endl;
			break;
		}
	}

	std::cout << std::endl;
}

void ReadInput(std::string input)
{
	struct CRUD crud;

	std::vector<std::string> splits;
	
	splits = split(input, splits, ' ');

	CommandType inputType = Prompt[splits.at(0)];

	switch (inputType)
	{
	case add:
		if (splits.size() > 6)
		{
			for (int i = 0; i < myList.size(); i++)
			{
				if (myList.at(i).id == std::stoi(splits.at(1)))
				{
					std::cout << "Elemnt already exist! \n";
					return;
				}
			}
			crud.id = std::stoi(splits.at(1));
			crud.name = splits.at(2);
			crud.lastName = splits.at(3);
			crud.birthday = splits.at(4);
			crud.phone = splits.at(5);

			myList.push_back(crud);

			return;
		}

		std::cout << "ERROR! \n";

		break;
	case del:
		if (!myList.empty())
		{
			for (int i = 0; i < myList.size() && myList.size() >= 1; i++)
			{
				if (myList.at(i).id == std::stoi(splits.at(1)))
				{
					myList.erase(myList.begin() + i);
					return;
				}
			}			
		}

		std::cout << "No element found! \n";

		break;
	case info:
		if (!myList.empty())
		{
			for (int i = 0; i < myList.size() && myList.size() >= 1; i++)
			{
				if (myList.at(i).id == std::stoi(splits.at(1)))
				{
					std::cout << myList.at(i).id + " - " + myList.at(i).name + " - " + myList.at(i).lastName + " - " + myList.at(i).birthday + " - "+ myList.at(i).phone + " \n";
					return;
				}
			}
		}

		std::cout << "No element found! \n";

		break;
	case query:
		DoQuery(splits);
		break;
	default:
		std::cout << "Invalid Command! \n";
		break;
	}
}

int main()
{
	Prompt["add"] = add;
	Prompt["del"] = del;
	Prompt["info"] = info;
	Prompt["query"] = query;

	PromptQuery["fn:"] = fn;
	PromptQuery["ln:"] = ln;
	PromptQuery["bd:"] = bd;
	PromptQuery["pn:"] = pn;

	std::string commandInserted = "";

	while (commandInserted.compare("000"))
	{

		std::getline(std::cin, commandInserted);

		commandInserted.append(" ");

		ReadInput(commandInserted);
	}

	std::cout << "End of Operation";
}

// Executar programa: Ctrl + F5 ou Menu Depurar > Iniciar Sem Depuração
// Depurar programa: F5 ou menu Depurar > Iniciar Depuração

// Dicas para Começar: 
//   1. Use a janela do Gerenciador de Soluções para adicionar/gerenciar arquivos
//   2. Use a janela do Team Explorer para conectar-se ao controle do código-fonte
//   3. Use a janela de Saída para ver mensagens de saída do build e outras mensagens
//   4. Use a janela Lista de Erros para exibir erros
//   5. Ir Para o Projeto > Adicionar Novo Item para criar novos arquivos de código, ou Projeto > Adicionar Item Existente para adicionar arquivos de código existentes ao projeto
//   6. No futuro, para abrir este projeto novamente, vá para Arquivo > Abrir > Projeto e selecione o arquivo. sln

