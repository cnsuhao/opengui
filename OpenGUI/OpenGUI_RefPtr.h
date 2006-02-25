#ifndef D77A8D21_C400_424b_B7C4_3A8242D75BA2
#define D77A8D21_C400_424b_B7C4_3A8242D75BA2

//Enable the following #define to make each refptr output to its own log.
//Great way to find out if all refptrs are actually getting destructed correctly.
//#define REFPTR_DEBUG

#ifdef REFPTR_DEBUG
#include <iostream>
#include <fstream>
#include <sstream>
#endif

namespace OpenGUI{
	template<typename T>
	class RefPtr;

	template<typename T>
	class __RefObj {
		friend class RefPtr;
	private:
		__RefObj(T *payload){
			m_objPtr = payload;
			refcount=1;
#ifdef REFPTR_DEBUG
			std::stringstream ss;
			ss << "REFPTR_" << m_objPtr << ".log";
			std::ofstream out;
			out.open(ss.str().c_str(),std::ios::app);
			out <<"[+] NEW RefObj: 0x" << this <<" : (0x"<< m_objPtr <<") {"<<refcount<<"}\n";
			out.close();
#endif
		}
		~__RefObj(){
#ifdef REFPTR_DEBUG
			std::stringstream ss;
			ss << "REFPTR_" << m_objPtr << ".log";
			std::ofstream out;
			out.open(ss.str().c_str(),std::ios::app);
			out<<"[-] DEL RefObj: 0x" << this <<" : (0x"<< m_objPtr <<") {"<<refcount<<"}\n";
			out.close();
#endif
			delete m_objPtr;
		}
		void ref(){
			refcount++;
#ifdef REFPTR_DEBUG
			std::stringstream ss;
			ss << "REFPTR_" << m_objPtr << ".log";
			std::ofstream out;
			out.open(ss.str().c_str(),std::ios::app);
			out<<"[R] REF RefObj: 0x" << this <<" : (0x"<< m_objPtr <<") {"<<refcount<<"}\n";
			out.close();
#endif
		}
		void unref(){
			refcount--;
#ifdef REFPTR_DEBUG
			std::stringstream ss;
			ss << "REFPTR_" << m_objPtr << ".log";
			std::ofstream out;
			out.open(ss.str().c_str(),std::ios::app);
			out<<"[U] URF RefObj: 0x" << this <<" : (0x"<< m_objPtr <<") {"<<refcount<<"}\n";
			out.close();
#endif
			if(refcount==0)
				delete this;
		}
		T* m_objPtr;
		unsigned int refcount;
	};

	template<typename T>
	class RefPtr {
	public:
		RefPtr(T *ptr=0){
			m_refObjPtr=0;
			if(ptr)
				m_refObjPtr = new __RefObj<T>(ptr);
		}
		RefPtr(const RefPtr<T> &ptr){
			m_refObjPtr = ptr.m_refObjPtr;
			if(m_refObjPtr)	m_refObjPtr->ref();
		}
		~RefPtr(){
			if(m_refObjPtr)
				m_refObjPtr->unref();
		}

		unsigned int getRefCount() {
			if(m_refObjPtr)
				return m_refObjPtr->refcount;
			return 0;
		}

		RefPtr<T>& operator=(const RefPtr<T>& ptr){
			if(m_refObjPtr) m_refObjPtr->unref();
			m_refObjPtr = ptr.m_refObjPtr;
			if(m_refObjPtr) m_refObjPtr->ref();
			return *this;
		}

		T& operator*() const {
			return *(m_refObjPtr->m_objPtr);
		}
		T* operator->() const{
			return (m_refObjPtr->m_objPtr);
		}
		operator bool() const {
			return m_refObjPtr == 0? false : true;
		}

		
		bool operator==(int p) const {
			//yep, they're testing for null, but we need to make sure
			if(0 == p)
				return operator ==((T*)0);
			//mmkay, i don't know of anyone that holds pointers inside of ints
			//so no, we don't equal that
			return false;
		}
		bool operator!=(int p) const {
			//yet another null test type
			return !operator==(p);
		}
		bool operator ==(const T* p) const {
			if(m_refObjPtr)
				return m_refObjPtr->m_objPtr  == p;
			return p == 0;
		}
		bool operator==(const RefPtr& r) const {
			return m_refObjPtr == r.m_refObjPtr;
		}
		
		bool operator!=(const RefPtr& r) const { return !operator==(r); }
		bool operator!=(const T* p) const { return !operator==(p); }

		bool isNull()const{ return m_refObjPtr==0; }
		T* get() const { 
			return (m_refObjPtr->m_objPtr);
		}
	protected:
		__RefObj<T> *m_refObjPtr;
	};
};//namespace OpenGUI{
#endif