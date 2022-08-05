#include <iostream>
#include "vehicleData.h"

using namespace std;

string fileName = "asdasd.xml";

enum
{
	ADD = 1,
	UPDATE,
	REMOVE,
	LOAD,
	SEARCH,
};

void addNewVehicleData();
void updateVehicleData();
void removeVehicleData();
void loadByFieldVehicleData();
void searchByFieldVehicleData();

uint32_t main()
{
	setlocale(LC_ALL, "Russian");

	while (true)
	{
		cout << "������� �������� ����� (� ����������� .xml): ";
		cin >> fileName;

		uint32_t exit = true;
		while (exit == 1)
		{
			uint32_t action;
			cout << "�������� ��������:" << endl << endl;
			cout << "1. ������ � ���� ������������ �������� (��� ���������� ����� ����� ������ �����)" << endl
				<< "2. �������� ������ ������������� ��������" << endl
				<< "3. ������� �� ����� ������������ ��������" << endl
				<< "4. ���������� ������������ ������� � ����������� �� ����" << endl
				<< "5. ����� ������������� �������� �� ����" << endl << endl;
			cin >> action;
			switch (action)
			{
			case ADD:
				addNewVehicleData();
				break;
			case UPDATE:
				updateVehicleData();
				break;
			case REMOVE:
				removeVehicleData();
				break;
			case LOAD:
				loadByFieldVehicleData();
				break;
			case SEARCH:
				searchByFieldVehicleData();
				break;
			default:
				cout << "������ �������� �� ����������" << endl;
				break;
			}

			cout << "���������� �������� � ������� �����? 1/0" << endl << endl;
			cin >> exit;
		}
	}
}

void addNewVehicleData()
{
	string type;
	string brand;
	string model;
	uint32_t year;
	double weight;

	cout << "������� ��� ������������� ��������" << endl;
	cin >> type;
	cout << "������� ����� ������������� ��������" << endl;
	cin >> brand;
	cout << "������� ������ ������������� ��������" << endl;
	cin >> model;
	cout << "������� ��� ������� ������������� ��������" << endl;
	cin >> year;
	cout << "������� ���(��) ������������� ��������" << endl;
	cin >> weight;

	VehicleData *vehicle = new VehicleData;
	vehicle->setType(type);
	vehicle->setBrand(brand);
	vehicle->setModel(model);
	vehicle->setYear(year);
	vehicle->setWeight(weight);

	vehicle->save(fileName);

	delete vehicle;
}

void updateVehicleData()
{
	uint32_t id;
	string type;
	string brand;
	string model;
	uint32_t year;
	double weight;

	VehicleData *vehicle = new VehicleData;

	cout << "������� ������������� ������������ �������� ��� ��������� ������: ";
	cin >> id;

	cout << endl << "������� ������:" << endl << endl;
	vehicle->getVehicleDataById(id, fileName);

	cout << endl << "������� ����� ������:" << endl << endl;

	cout << "��� ������������� ��������: ";
	cin >> type;
	cout << endl << "����� ������������� ��������: ";
	cin >> brand;
	cout << endl << "������ ������������� ��������: ";
	cin >> model;
	cout << endl << "��� ������� ������������� ��������: ";
	cin >> year;
	cout << endl << "���(��) ������������� ��������: ";
	cin >> weight;


	vehicle->setId(id);
	vehicle->setType(type);
	vehicle->setBrand(brand);
	vehicle->setModel(model);
	vehicle->setYear(year);
	vehicle->setWeight(weight);

	vehicle->update(fileName);

	delete vehicle;
}

void removeVehicleData()
{
	uint32_t id;
	cout << "������� ������������� ������������ �������� ��� ��������: ";
	cin >> id;

	VehicleData *vehicle = new VehicleData;
	vehicle->setId(id);

	vehicle->remove(id, fileName);

	delete vehicle;
}

void loadByFieldVehicleData()
{
	uint32_t sortType;
	cout << "�������� ���� ��� ���������� ������ ������������ �������:" << endl << endl;
	cout << "1. ID)" << endl
		<< "2. ���" << endl
		<< "3. �����" << endl
		<< "4. ������" << endl
		<< "5. ���" << endl
		<< "6. ���" << endl;
	cin >> sortType;

	VehicleData *vehicle = new VehicleData;
	vehicle->loadByField(sortType, fileName);

	delete vehicle;
}

void searchByFieldVehicleData()
{
	uint32_t sortType;
	cout << "�������� ���� ��� ���������� ������ ������������ �������:" << endl << endl;
	cout << "1. ID" << endl
		<< "2. ���" << endl
		<< "3. �����" << endl
		<< "4. ������" << endl
		<< "5. ���" << endl
		<< "6. ���" << endl;
	cin >> sortType;

	string searchWord;
	cout << "������� �����: ";
	cin >> searchWord;

	VehicleData *vehicle = new VehicleData;
	vehicle->searchByField(sortType, fileName, searchWord);

	delete vehicle;
}
