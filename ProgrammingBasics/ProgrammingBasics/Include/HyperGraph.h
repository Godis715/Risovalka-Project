#pragma once
#include "Requirement.h"

class HyperGraph
{
private:
	class Component
	{
	private:
		const ID id;
	public:
		Dict<ID, Primitive*> dataPrimitive;
		Dict<ID, IRequirement*> dataRequirement;
		Component() {}
		~Component() {}
		bool Search(ID&);
		bool Delete(ID&);
		Array<double*> GetParams();
		double GetError();
		ID GetID() const;
	};

	int currentIndex;

	Dict<ID, Component*> components;
	void SplitingAndBFS(int);
	void MergeComponents(Array<ID>);
public:
	HyperGraph() {}
	~HyperGraph() {}
	
	int GetSize() {
		return components.GetSize();
	}
	int GetCurrent() {
		return currentIndex;
	}
	void SetCurrent(int index) {
		currentIndex = abs(index) % components.GetSize();
	}
	void DeleteComponent(ID id);
	int Search(ID&);
	void Delete(ID&);
	void Add(IRequirement*, Array<Primitive*>);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
};