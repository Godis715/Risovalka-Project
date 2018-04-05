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
		bool SearchRequirement(IDReq&) const;
		void DeleteRequirement(IDReq&);
	};

	Array<Component> components;
	void SplitingAndBFS(int index);
	void MergeComponents(int array[], int size);
	void DeleteComponent(int index);
public:
	HyperGraph() {}
	~HyperGraph() {}
	int Optimize(int index);
	int Optimize_2(int index);
	bool SearchPrimitive(ID&) const;
	void DeletePrimitive(ID&);
	bool SearchRequirement(IDReq&) const;
	void DeleteRequirement(IDReq&);
	void Add(IDReq&, Array<ID&>);
	void Add(IRequirement*, Array<Primitive*>);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
};