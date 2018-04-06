#pragma once
#include "Requirement.h"

class HyperGraph
{
private:
	class Component
	{
	private:
		Array<Primitive*> dataPrimitive;
		Array<IRequirement*> dataRequirement;
	public:
		Component() {}
		~Component() {}
		bool SearchPrimitive(ID&) const;
		void DeletePrimitive(ID&);
	};

	int currentIndex;

	Array<Component> components;
	void SplitingAndBFS(int index);
	void MergeComponents(int array[], int size);
	void DeleteComponent(int index);
public:
	HyperGraph() {}
	~HyperGraph() {}
	bool SearchPrimitive(ID&) const;
	void DeletePrimitive(ID&);
	void Add(IRequirement*, Array<Primitive*>);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
	int GetSize();
};