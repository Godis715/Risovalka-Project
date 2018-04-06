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
<<<<<<< Updated upstream
		Dict<ID, Primitive*> dataPrimitive;
		Dict<ID, IRequirement*> dataRequirement;
		Component() {}
		~Component() {}
=======
		Component(ID);
		~Component() {}
		Dict<ID, Primitive*> dataPrimitive;
		Dict<ID, IRequirement*> dataRequirement;
>>>>>>> Stashed changes
		bool Search(ID&);
		bool Delete(ID&);
		Array<double*> GetParams();
		double GetError();
		ID GetID() const;
	};

<<<<<<< Updated upstream
	int currentIndex;

	Dict<ID, Component*> components;
	void SplitingAndBFS(int);
	void MergeComponents(Array<ID>);
=======
	Dict<ID, Component*> components;
	void SplitingAndBFS();
	void MergeComponents(Array<ID>&);
>>>>>>> Stashed changes
public:
	HyperGraph() {}
	~HyperGraph() {}
	
<<<<<<< Updated upstream
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
=======
	int GetSize();
	void DeleteComponent();
	bool Search(ID, ID&);
>>>>>>> Stashed changes
	void Delete(ID&);
	void Add(IRequirement*, Array<Primitive*>&);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
};