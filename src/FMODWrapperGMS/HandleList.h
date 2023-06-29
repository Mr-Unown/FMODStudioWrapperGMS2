#pragma once

// Code by: RadixComet

#include <vector>
#include <functional>

typedef size_t PointerHandle;

constexpr PointerHandle InvalidPointerHandle = -1;



template<typename T>
class PointerHandleList
{
private:
	std::vector<T*> m_handleList{ };
	std::function<bool(T*)> m_customValidityPredicate = nullptr;

public:
	PointerHandleList(std::function<bool(T*)> validityPredicate)
	{
		m_customValidityPredicate = validityPredicate;
	}

	/// <summary>
	/// Determines if a given handle is assigned to a valid pointer address
	/// </summary>
	/// <param name="handle">The handle to check</param>
	/// <returns></returns>
	bool IsHandleValid(const PointerHandle& handle)
	{
		if (handle >= m_handleList.size())
			return false;

		if (handle <= InvalidPointerHandle)
			return false;

		if (m_handleList[handle] == nullptr)
			return false;

		if (m_customValidityPredicate != nullptr)
		{
			bool result = m_customValidityPredicate(m_handleList[handle]);

			if (!result)
				m_handleList[handle] = nullptr;

			return result;
		}

		return true;
	}

	/// <summary>
	/// Peeks the next free handle in the list
	/// </summary>
	/// <returns>Next free handle, or `InvalidPointerHandle` if all slots are used</returns>
	PointerHandle PeekNextFreeHandle()
	{
		if (!m_handleList.size()) // No size = No free Handles
			return InvalidPointerHandle;

		for (int i = 0; i < m_handleList.size(); i++)
		{
			if (m_handleList[i] == nullptr)
				return i;
		}

		return InvalidPointerHandle;
	}

	/// <summary>
	/// Adds a new object to the list
	/// </summary>
	/// <param name="pointer">The object to add</param>
	/// <returns>Handle of the object</returns>
	PointerHandle Add(T* pointer)
	{
		PointerHandle freeHandle = PeekNextFreeHandle();
		if (freeHandle == InvalidPointerHandle)
		{
			m_handleList[freeHandle] = pointer;
			return freeHandle;
		}
		else
		{
			m_handleList.push_back(pointer);
			return m_handleList.size() - 1;
		}
	}
	/// <summary>
	/// Removes a given object at the specified handle
	/// </summary>
	/// <param name="handle">Object handle to nullify</param>
	/// <returns></returns>
	bool Remove(const PointerHandle& handle)
	{
		if (!IsHandleValid(handle))
			return false;

		m_handleList[handle] = nullptr;

		return true;
	}



	/// <summary>
	/// Gets the handle assigned to a valid pointer address
	/// </summary>
	/// <param name="pointer">The pointer value to check for</param>
	/// <returns></returns>
	PointerHandle Get(const T* pointer)
	{
		if (!m_handleList.size())
			return InvalidPointerHandle;

		for (int i = 0; i < m_handleList.size(); i++)
		{
			if (m_handleList[i] == pointer)
				return i;
		}

		return InvalidPointerHandle;
	}

	/// <summary>
	/// Gets the pointer assigned to a handle
	/// </summary>
	/// <param name="handle">The handle value to check for</param>
	/// <returns></returns>
	T* Get(const PointerHandle& handle)
	{
		if (!IsHandleValid(handle))
			return nullptr;

		return m_handleList[handle];
	}
};