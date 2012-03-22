#ifndef __BEHAVIOUR_DB_H__
#define __BEHAVIOUR_DB_H__

#include <map>

#include <MEngine.h>

class Behaviour : public MBehavior
{
public:
	typedef int ID;

	Behaviour(MObject3d * parentObject, ID id);
	~Behaviour();

	virtual ID GetID() { return 0; }
	
protected:
	template <typename T>
	T* GetBehaviour()
	{
		return (T*)GetBehaviour(T::GetID());
	}

	Behaviour* GetBehaviour(ID behaviour);
};

#define IMPLEMENT_BEHAVIOUR(x) \
static void SetID(Behaviour::ID id) { m_ID = id; } \
static Behaviour::ID GetStaticID() { return m_ID; } \
static Behaviour::ID m_ID; \
virtual Behaviour::ID GetID() { return GetStaticID(); }

#define REGISTER_BEHAVIOUR(x) \
Behaviour::ID x::m_ID = GetBehaviourDB()->GetBehaviourID(#x);

class BehaviourDB
{
public:
	Behaviour::ID GetBehaviourID(const char* name);

	Behaviour* GetBehaviour(MObject3d* obj, Behaviour::ID id);
	void RemoveBehaviour(MObject3d* obj, Behaviour* behaviour);
	void RegisterBehaviour(MObject3d* obj, Behaviour* behaviour, Behaviour::ID id);

private:
	typedef std::map<Behaviour::ID, Behaviour*>	behaviourMap;
	typedef behaviourMap::iterator				behaviourMapIter;
	typedef std::map<MObject3d*, behaviourMap>	objectMap;
	typedef objectMap::iterator					objectMapIter;

	objectMap		m_Objects;
};

BehaviourDB* GetBehaviourDB();

#endif /*__BEHAVIOUR_DB_H__*/