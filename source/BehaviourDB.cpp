#include "BehaviourDB.h"
#include "Util.h"

BehaviourDB g_BehaviourDB;
BehaviourDB* GetBehaviourDB() { return &g_BehaviourDB; }

Behaviour::Behaviour(MObject3d * parentObject, ID id)
: MBehavior(parentObject) 
{
	g_BehaviourDB.RegisterBehaviour(getParentObject(), this, id);
}

Behaviour::~Behaviour()
{
	g_BehaviourDB.RemoveBehaviour(getParentObject(), this);
}

Behaviour* Behaviour::GetBehaviour(ID behaviour)
{
	return g_BehaviourDB.GetBehaviour(getParentObject(), behaviour);
}

Behaviour::ID BehaviourDB::GetBehaviourID(const char* name)
{
	return Util::Hash(name);
}

Behaviour* BehaviourDB::GetBehaviour(MObject3d* obj, Behaviour::ID id)
{
	return m_Objects[obj][id];
}

void BehaviourDB::RemoveBehaviour(MObject3d* obj, Behaviour* behaviour)
{
	behaviourMapIter iBehaviour = m_Objects[obj].find(behaviour->GetID());

	if(iBehaviour != m_Objects[obj].end())
	{
		m_Objects[obj].erase(iBehaviour);
	}

	// cleanup empty objects
	objectMapIter iObj = m_Objects.find(obj);
	if(iObj->second.size() == 0)
	{
		m_Objects.erase(iObj);
	}
}

void BehaviourDB::RegisterBehaviour(MObject3d* obj, Behaviour* behaviour, Behaviour::ID id)
{
	m_Objects[obj][id] = behaviour;
}