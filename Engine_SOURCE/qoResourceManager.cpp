#include "qoResourceManager.h"
#include "qoResource.h"

namespace qo
{
	std::map<std::wstring, Resource*> ResourceManager::mResources;

	void ResourceManager::Release()
	{
		std::map<std::wstring, Resource*>::iterator iter = mResources.begin();
		for (; iter != mResources.end(); ++iter)
		{
			delete iter->second;
			iter->second = nullptr;
		}
	}
}
