
#pragma once

template < class T >
class CSingleton
{
private:
	static T* m_pInstance;

protected:
	CSingleton() {}
	virtual ~CSingleton() {}

public:
	static T* GetInstance() { if (m_pInstance == NULL) m_pInstance = new T; return m_pInstance; }
	static void Release() { SAFE_DELETE(m_pInstance); }
};

template < class T > T* CSingleton< T >::m_pInstance = NULL;