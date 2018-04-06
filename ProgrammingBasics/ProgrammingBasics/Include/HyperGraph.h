#pragma once
#include "Requirement.h"

class HyperGraph
{
private:
	class Component
	{
	private:
		Dict<ID, Primitive*> dataPrimitive;
		Dict<ID, IRequirement*> dataRequirement;
	public:
		Component() {}
		~Component() {}
		bool Search(ID&);
		bool Delete(ID&);
		Array<double*> GetParams();
		double GetError();
	};

	int currentIndex;

	Array<Component> components;
	void SplitingAndBFS(int index);
	void MergeComponents(int array[], int size);
public:
	HyperGraph() {}
	~HyperGraph() {}
	
	int GetSize() {
		return components.getSize();
	}
	int GetCurrent() {
		return currentIndex;
	}
	void SetCurrent(int index) {
		currentIndex = abs(index) % components.getSize();
	}
	void DeleteComponent(int index);
	int Search(ID&);
	void Delete(ID&);
	void Add(IRequirement*, Array<Primitive*>);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
};