#pragma once

template<typename T>
class singletonBase
{
protected:
	static T* m_pInstance;
	// 생성자 소멸자 외부에서 접근 금지
	singletonBase() {};
	virtual ~singletonBase() {};

	// 복사 생성자 사용금지
	singletonBase(const singletonBase&);
	singletonBase& operator = (const singletonBase&);

public:
	// 인스턴스 생성
	static void createInstance()
	{
		// assert() 함수
		// 참일 경우 아무것도 안하지만, 거짓이면 팝업창에
		// 오류를 출력하고 종료
		assert(!m_pInstance);
		// 인스턴스 생성
		m_pInstance = new T();
	}

	static void releaseInstance()
	{
		assert(m_pInstance);
		delete m_pInstance;
		m_pInstance = NULL;
	}

	static T& getInstance()
	{
		return *m_pInstance;
	}
};

template<typename T>
T* singletonBase<T>::m_pInstance = nullptr;


