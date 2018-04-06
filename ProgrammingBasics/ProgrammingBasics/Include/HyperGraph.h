#ifndef __HYPERGRAPH
#define __HYPERGRAPH
#include "Requirement.h"
#include "Set.h"

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

		Component(ID);
		~Component() {}
		bool Search(ID&);
		bool Delete(ID&);
		Array<double*> GetParams();
		double GetError();
		ID GetID() const;
	};

	Dict<ID, Component*> components;

	Array<Primitive*> SplitingAndBFS(ID);
	void MergeComponents(Array<ID>&);
public:
	HyperGraph() {}
	~HyperGraph() {}
	

	int GetSize();
	void DeleteComponent(ID id);
	bool Search(ID, ID&);
	void Delete(Array<ID>&);
	void Add(IRequirement*, Array<Primitive*>&);
	Array<Primitive*> UploadingDataPrimitive();
	Array<IRequirement*> UploadingDataRequirement();
};



#endif