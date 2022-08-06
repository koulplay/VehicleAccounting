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

	//���������� ����������� ������ ���������� �� id
	void getVehicleDataById(uint32_t, string);
	//���������� ���������� ������ ���������� �� ���������
	void save(string, string, string, string, uint32_t, double);
	//���������� �������������� ������ ���������� �� ��������� �� id
	void update(uint32_t, string, string, string, string, uint32_t, double);
	//���������� �������� ������ ���������� �� id
	void remove(uint32_t, string);
	//���������� ����������� ������ ����������� � ����������� �� ����
	void loadByField(uint32_t, string);
	//���������� ����� �� ����
	void searchByField(uint32_t, string, string);
private:
	uint32_t id_ = 0;
	string type_;
	string brand_;
	string model_;
	uint32_t year_ = 0;
	double weight_ = 0;

	//���������� id
	void generateId();
	//���������� ����� ���� � xml ����� 
	pugi::xml_node nodeFinder(uint32_t);
};
