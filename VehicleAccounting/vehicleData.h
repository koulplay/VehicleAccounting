#pragma once
#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "pugixml.hpp"

using namespace std;


class VehicleData
{
public:
	uint32_t getId();
	string getType();      
	string getBrand();
	string getModel();
	uint32_t getYear();
	double getWeight();

	//Производит отображения данных транспорта по id
	void getVehicleDataById(uint32_t, string);
	//Производит созранения данных транспорта из структуры
	void save(string, string, string, string, uint32_t, double);
	//Производит редактирование данных транспорта из структуры по id
	void update(uint32_t, string, string, string, string, uint32_t, double);
	//Производит удаление данных транспорта по id
	void remove(uint32_t, string);
	//Возвращает десериализированую коллекцию транспорта
	vector<VehicleData> loadVehicleData();
	//Производит отображение данных транспортов с сортировкой по полю
	void loadByField(uint32_t, string);
	//Производит поиск по полю
	void searchByField(uint32_t, string, string);
private:
	uint32_t id_ = 0;
	string type_;
	string brand_;
	string model_;
	uint32_t year_ = 0;
	double weight_ = 0;

	//Генерирует id
	void generateId();
	//Производит поиск тега в xml файле 
	pugi::xml_node nodeFinder(uint32_t);
	//Проверка существования файла
	void checkExistingFile(string);
};
