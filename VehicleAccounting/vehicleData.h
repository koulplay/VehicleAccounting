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

	void setId(uint32_t);
	void setType(string);
	void setBrand(string);
	void setModel(string);
	void setYear(uint32_t);
	void setWeight(double);

	//ѕроизводит отображени€ данных транспорта по id
	void getVehicleDataById(uint32_t, string);
	//ѕроизводит созранени€ данных транспорта из структуры
	void save(string, string, string, string, uint32_t, double);
	//ѕроизводит редактирование данных транспорта из структуры по id
	void update(uint32_t, string, string, string, string, uint32_t, double);
	//ѕроизводит удаление данных транспорта по id
	void remove(uint32_t, string);
	//¬озвращает десериализированую коллекцию транспорта
	vector<VehicleData> loadVehicleData();
	//ѕроизводит отображение данных транспортов с сортировкой по полю
	void loadByField(uint32_t, string);
	//ѕроизводит поиск по полю
	void searchByField(uint32_t, string, string);
private:
	uint32_t id_ = 0;
	string type_;
	string brand_;
	string model_;
	uint32_t year_ = 0;
	double weight_ = 0;

	//√енерирует id
	void generateId();
	//ѕроизводит поиск тега в xml файле 
	pugi::xml_node nodeFinder(uint32_t);
};
