#pragma once

#ifndef PS_STRING_BASE_H
#define PS_STRING_BASE_H 


#define DEFAULT_STRING_SIZE 4
#define NULL_ACHAR	'\0'
#define NULL_WCHAR	L'\0'

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) {delete (p); (p) = NULL;}}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if( (p) ) {delete [] (p); (p) = NULL;}}
#endif

#include <istream>
#include <stdlib.h>

#ifdef WIN32
	#include <tchar.h>
	#include "Windows.h"
#elif defined(__linux__)
	#include "string.h"
#endif

//#define USE_SECURE_API
#define USE_NORMAL_API

namespace PS{

	template<typename Type>
	class CTString
	{
	public:	
		CTString();
		CTString(const CTString& src);
		CTString(const Type src[], size_t srcSize = 0);

		typedef Type UNIT;

			

		~CTString(){ reset(); }

		__inline Type nullChar() const
		{
			if(sizeof(Type) == 1)
				return (char)NULL_ACHAR;
			else
				return (wchar_t)NULL_WCHAR;
		}
			
		__inline size_t unitSize() const
		{
			return sizeof(Type);
		}

		__inline bool isAnsiCharStr() const
		{
			return (sizeof(Type) == sizeof(char));
		}

		virtual size_t getInputLength(const Type src[]) const
		{
			return static_cast<int>(src[0]) + 1;
		}

		void resize(size_t n);
		void reserve(size_t n);
		size_t length() const {return m_length;}
		size_t capacity() const {return m_allocated - m_length - 1;}


		int replaceChars(Type query, Type rhs);		
		//====================================================		
		void reset();
		void init();
		void zero_sequence();
		bool isPos(size_t pos) const {return (pos >= 0 && pos < m_length);}
		bool isNullTerminated() const	{ return (m_sequence[m_length] == nullChar());}
		bool empty() const { return (m_length == 0);}
		//====================================================		
		//Return a pointer to the start of the string in sequence
		const Type* cptr() const {return static_cast<const Type*>(m_sequence);}
		Type* ptr() const {return m_sequence;}
		Type* c_str() const {return m_sequence;}

		//Other functions
		bool lfindstr(const CTString& src, size_t &pos) const;
		bool rfindstr(const CTString& src, size_t &pos) const;
		bool lfind(Type ch, size_t &pos) const;
		bool rfind(Type ch, size_t &pos) const;		
		bool isEqual(const CTString& src) const
		{
			if(m_length != src.m_length) return false;
			for(size_t i = 0; i<m_length; i++)
				if(m_sequence[i] != src.m_sequence[i])
					return false;
			return true;
		}

		Type firstChar() const;
		Type lastChar() const;


		//Useful functions for string manipulation
		CTString substrT(size_t offset, size_t count = -1) const;
		CTString& toUpper();
		CTString& toLower();
		

		//Handy Copy and append functions
		void copyFrom(const CTString& src);
		void copyFromT(const Type src[], size_t srcSize = 0);
		void copyFromT(const Type ch);
		//====================================================				
		void appendFrom(const CTString& src);
		void appendFromT(const Type src[], size_t srcSize = 0);	
		void appendFromT(const Type ch);
		//====================================================		
		//Operators
		template<typename U>
		friend std::ostream& operator <<(std::ostream& outs, const CTString& src);

		Type operator [](size_t pos) const;

		void operator =(const CTString& src);
		void operator =(const Type src[]);

		//Append to the end of string
		void operator +=(const CTString& src);
		void operator +=(const Type src[]);
		void operator +=(Type src[]);
		void operator +=(const Type ch);
		

		//Add to string
		CTString<Type>& operator +(const CTString& src);
		CTString<Type>& operator +(const Type src[]);
		CTString<Type>& operator +(Type src[]);
		CTString<Type>& operator +(const Type ch);


		//Return true if they are equal
		template<typename U>
		friend bool operator==(const CTString& a, const CTString& b);	
		template<typename U>
		friend bool operator!=(const CTString& a, const CTString& b);	

	protected:
		Type* m_sequence;
		size_t m_length;
		size_t m_allocated;
	};


	template<class Type>
	CTString<Type> operator +(const CTString<Type>& s1, const CTString<Type>& s2);
	//CTString<Type> operator +(const CTString<Type>& s1, const CTString<Type>& s2);
	/*	
	std::istream& operator >>(std::istream& ins, CTString& dst);
	std::istream& getLine(std::istream& ins, CTString& dst);
	*/

	template<class Type>
	CTString<Type>::CTString()
	{
		init();
	}

	template<class Type>
	CTString<Type>::CTString(const CTString& src)
	{
		init();
		copyFrom(src);
	}

	template<class Type>			
	CTString<Type>::CTString(const Type src[], size_t srcSize)
	{
		init();
		copyFromT(src, srcSize);
	}

/*
	template<class Type>
	CTString<Type>::~CTString()
	{
		reset();
	}
*/
	template<class Type>
	void CTString<Type>::reset()
	{
		SAFE_DELETE_ARRAY(m_sequence);		
		m_allocated = 0;
		m_length = 0;
	}

	template<class Type>
	void CTString<Type>::init()
	{
		m_allocated = 0;
		m_length    = 0;
		m_sequence  = NULL;		
		reserve(DEFAULT_STRING_SIZE);		
	}

	template<class Type>
	void CTString<Type>::resize(size_t n)
	{
		if(n <= m_length)
			m_length = n;
		m_sequence[m_length] = nullChar();
	}

	template<class Type>
	void CTString<Type>::zero_sequence()
	{
		memset(m_sequence, 0, sizeof(m_allocated) * unitSize());
	}

	template<class Type>
	void CTString<Type>::copyFrom(const CTString& src)
	{
		if(src.length() == 0) 
		{
			reset();	
			init();
			return;
		}

		this->reserve(src.m_allocated);	
		memcpy(m_sequence, src.m_sequence, src.m_allocated * unitSize());
		m_length = src.m_length;
	}
	
	template<class Type>
	void CTString<Type>::copyFromT(const Type src[], size_t srcSize)
	{
		if((src != NULL)&&(srcSize == 0))
			srcSize = getInputLength(src);

		if((src == NULL) || (srcSize == 0)) 
		{
			reset();
			init();
			return;
		}

		this->reserve(srcSize * 2);
		this->zero_sequence();

		memcpy(m_sequence, src, srcSize * sizeof(Type));		
		m_length = srcSize;
		m_sequence[m_length] = nullChar();
	}

	template<class Type>
	void CTString<Type>::copyFromT(const Type ch)
	{
		reset();
		init();
		appendFromT(ch);
	}
	//=============================================================================================
	template<class Type>
	void CTString<Type>::appendFrom(const CTString& src)
	{
		if(src.m_length == 0) return;

		if(capacity() < (src.m_allocated + DEFAULT_STRING_SIZE))
			reserve(m_allocated + src.m_allocated + DEFAULT_STRING_SIZE);

		Type* pDst = &m_sequence[m_length];
		memcpy(pDst, src.m_sequence, src.m_length * unitSize());
		
		//Update length
		m_length += src.m_length;
		m_sequence[m_length] = nullChar();
	}

	//======================================================================================
	template<class Type>
	void CTString<Type>::appendFromT(const Type src[], size_t srcSize)
	{
		if((src != NULL)&&(srcSize == 0))
			srcSize = getInputLength(src);

		if((src == NULL) || (srcSize == 0)) 
			return;

		if(capacity() < (srcSize + DEFAULT_STRING_SIZE))
			reserve(m_allocated + srcSize + DEFAULT_STRING_SIZE);

		Type* pDst = &m_sequence[m_length];
		memcpy(pDst, src, srcSize * unitSize());

		//Update length
		m_length += srcSize;
		m_sequence[m_length] = nullChar();		
	}

	template<class Type>
	void CTString<Type>::appendFromT(const Type ch)
	{
		if(capacity() < DEFAULT_STRING_SIZE)
			reserve(m_allocated + DEFAULT_STRING_SIZE);
		m_sequence[m_length] = ch;
		m_length++;
		m_sequence[m_length] = nullChar();
	}
	//======================================================================================
	template<class Type>
	int CTString<Type>::replaceChars(Type query, Type rhs)
	{
		int ctFound = 0;
		for (size_t i=0; i < m_length; i++)
		{
			if(m_sequence[i] == query)
			{
				m_sequence[i] = rhs;
				ctFound ++;
			}
		}
		return ctFound;
	}
	//======================================================================================
	template<class Type>
	void CTString<Type>::reserve(size_t n)
	{
		if ( n <= m_allocated )
			return;

		Type *newSeq = new Type[ n ];

		// return silently on failure
		if ( newSeq == NULL)
			return;

		//Zero new allocated memory
		memset(newSeq, 0, sizeof(Type) * n);

		//Copy previous content if there is any
		if ( m_sequence )
		{
			if(m_length > 0)
				memcpy( newSeq, m_sequence, m_length * sizeof(Type) );

			SAFE_DELETE_ARRAY(m_sequence);
		}

		m_sequence = newSeq;
		m_allocated = n;
	}

	template<class Type>
	Type CTString<Type>::firstChar() const
	{	
		if(m_length > 0)
			return m_sequence[0];
		else
			return nullChar();
	}

	template<class Type>
	Type CTString<Type>::lastChar() const
	{
		if(m_length > 0)
			return m_sequence[m_length-1];
		else
			return nullChar();
	}

	template<class Type>
	CTString<Type>& CTString<Type>::toUpper()
	{
		for (size_t i=0; i < m_length; i++)
			m_sequence[i] = _totupper((Type)m_sequence[i]);			

		/*
		if(this->isAnsiCharStr());
		{
			for (size_t i=0; i < m_length; i++)
				m_sequence[i] = toupper((char)m_sequence[i]);			
		}
		else
		{
			for (size_t i=0; i < m_length; i++)
				m_sequence[i] = towupper((wchar_t)m_sequence[i]);			
		}
		*/
		return *this;				
	}

	template<class Type>
	CTString<Type>& CTString<Type>::toLower()
	{
		for (size_t i=0; i < m_length; i++)
			m_sequence[i] = _totlower((Type)m_sequence[i]);

		/*
		if(this->isAnsiCharStr())
		{
			for (size_t i=0; i < m_length; i++)
				m_sequence[i] = tolower((char)m_sequence[i]);
		}
		else
		{
			for (size_t i=0; i < m_length; i++)
				m_sequence[i] = towlower((wchar_t)m_sequence[i]);
		}
		*/
		return *this;			
	}

	template<class Type>
	bool CTString<Type>::lfind(Type ch, size_t &pos) const
	{
		if(m_length == 0) return false;
		for (size_t i=0; i < m_length; i++)
		{
			if(m_sequence[i] == ch)
			{
				pos = i;
				return true;
			}
		}
		return false;
	}

	template<class Type>
	bool CTString<Type>::rfind(Type ch, size_t &pos) const
	{
		if(m_length == 0) return false;
		for (int i=(int)m_length-1; i >=0; i--)
		{
			if(m_sequence[i] == ch)
			{
				pos = i;
				return true;
			}
		}
		return false;
	}

	template<class Type>
	bool CTString<Type>::lfindstr(const CTString& src, size_t &pos) const
	{
		pos = -1;
		if(m_length == 0) return false;
		size_t szQuery = src.length();

		if(szQuery > m_length) return false;

		bool bMatched;
		for(size_t i=0; i <= (m_length - szQuery); i++)
		{
			bMatched = true;
			for(size_t j=0; j < szQuery; j++)
			{
				if(m_sequence[i + j] != src[j])
				{
					bMatched = false;
					break;
				}
			}

			if(bMatched)
			{
				pos = i;
				return true;
			}
		}

		return false;
	}

	template<class Type>
	bool CTString<Type>::rfindstr(const CTString& src, size_t &pos) const
	{
		pos = -1;
		if(m_length == 0) return false;
		size_t szQuery = src.length();

		if(szQuery > m_length) return false;

		bool bMatched;
		for(size_t i=m_length - szQuery; i >= 0; i--)
		{
			bMatched = true;
			for(size_t j=0; j < szQuery; j++)
			{
				if(m_sequence[i + j] != src[j])
				{
					bMatched = false;
					break;
				}
			}

			if(bMatched)
			{
				pos = i;
				return true;
			}
		}

		return false;
	}

	template<class Type>
	CTString<Type> CTString<Type>::substrT(size_t offset, size_t count) const
	{
		CTString output;
		if(m_length == 0) return output;
		if(!isPos(offset)) return output;

		if(count == size_t(-1))
			count = m_length - offset;		
		
		if(!isPos(offset+count-1)) 
		{
			count = m_length - offset;
		}

		if(count <= 0) return output;


		Type *buffer = new Type[count+1];
		size_t idx = 0;
		for (size_t i=offset; i < offset + count; i++)
		{
			buffer[idx] = m_sequence[i];
			idx++;
		}
		buffer[idx] = nullChar();

		output.copyFromT(buffer, count);
		SAFE_DELETE_ARRAY(buffer);
		return output;
	}

	template<class Type>
	std::ostream& operator <<(std::ostream& outs, const CTString<Type>& src)
	{
		outs << src.m_length;
		for (size_t i = 0; i < src.m_length; i++)
		{
			outs << static_cast<Type>(src.m_sequence[i]);
		}
		outs << src.nullChar();
		return outs;
	}

	template<class Type>
	Type CTString<Type>::operator [](size_t pos) const
	{
		if(isPos(pos))
			return m_sequence[pos];
		else
			return nullChar();
	}

	template<class Type>
	void CTString<Type>::operator =(const CTString& src)
	{
		this->copyFrom(src);
	}

	template<class Type>
	void CTString<Type>::operator =(const Type src[])
	{
		this->copyFromT(src);
	}
	//==================================================================
	//Append to string
	template<class Type>
	void CTString<Type>::operator +=(const CTString& src)
	{
		this->appendFrom(src);
	}

	template<class Type>
	void CTString<Type>::operator +=(const Type src[])
	{
		size_t len = getInputLength(src);
		this->appendFromT(src, len);
	}

	template<class Type>
	void CTString<Type>::operator +=(Type src[])
	{
		size_t len = getInputLength(src);
		this->appendFromT(src, len);
	}

	template<class Type>
	void CTString<Type>::operator +=(Type ch)
	{
		this->appendFromT(ch);
	}
	//======================================================================================
	//Add to string
	template<class Type>
	CTString<Type>& CTString<Type>::operator +(const CTString& src)
	{
		this->appendFrom(src);
		return (*this);
	}

	template<class Type>
	CTString<Type>& CTString<Type>::operator +(const Type src[])
	{
		size_t len = getInputLength(src);
		this->appendFromT(src, len);
		return (*this);
	}

	template<class Type>	
	CTString<Type>& CTString<Type>::operator +(Type src[])
	{
		size_t len = getInputLength(src);
		this->appendFromT(src, len);
		return (*this);
	}

	template<class Type>
	CTString<Type>& CTString<Type>::operator +(const Type ch)
	{		
		this->appendFromT(ch);
		return (*this);
	}
	//============================================================================
	//friend bool operator==(const CTString& a, const CTString& b);	
	template<class Type>
	bool operator==(const CTString<Type>& a, const CTString<Type>& b)
	{
		if(a.m_length != b.m_length) return false;

		for (size_t i=0; i<a.m_length; i++)
		{
			if(a.m_sequence[i] != b.m_sequence[i])
				return false;
		}
		return true;
	}

	template<class Type>
	bool operator!=(const CTString<Type>& a, const CTString<Type>& b)
	{
		if(a == b)
			return false;
		else
			return true;
	}


	
	template<class Type>
	CTString<Type> operator +(const CTString<Type>& s1, const CTString<Type>& s2)
	{
		CTString<Type> str(s1);

		str += s2;	
		return str;
	}

	/*
	std::istream& operator >>(std::istream& ins, CTString& dst)
	{
		return getLine(ins, dst);
	}

	std::istream& getLine(std::istream& ins, CTString& dst)
	{
		size_t len = 0;
		ins >> len;

		int val;
		wchar_t* chrBuffer = new wchar_t[len];
		for (size_t i=0;i < len; i++)
		{
			ins >> val;
			chrBuffer[i] = static_cast<wchar_t>(val);
		}

		CTString strOutput(chrBuffer, len);
		
		dst = strOutput;
		return ins;
	}
*/

}
#endif