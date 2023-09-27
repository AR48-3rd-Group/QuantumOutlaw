#pragma once

#include "CommonInclude.h"
#include "..\\FMOD\\inc\\fmod.hpp"
#include "..\\FMOD\\inc\\fmod.h"
#include <map>
#include <string>

#pragma comment(lib, "lib/fmodL_vc.lib")

using namespace FMOD;

#define EXTRA_CHANNEL_BUFFER 50
#define SOUND_BUFFER 100
#define TOTAL_SOUND_BUFFER (EXTRA_CHANNEL_BUFFER + SOUND_BUFFER)

namespace qo
{
    class SoundManager
    {
    private:
        typedef std::map<std::wstring, Sound**> SoundMap;
        typedef SoundMap::iterator SoundMapIterator;

        System* _system;
        Sound** _sound;
        Channel** _channel;
        SoundMap _mTotalSound;

    public:
        void Init();
        void Release();
        void Update();
        void Render();

        void AddSound(const std::wstring& keyName, const std::wstring& soundName, bool bgm = false, bool loop = false);
        void Play(const std::wstring& keyName, float volume = 1.0f);
        void Stop(const std::wstring& keyName);
        void Pause(const std::wstring& keyName);
        void Resume(const std::wstring& keyName);

        bool IsPlaying(const std::wstring& keyName);
        bool IsPaused(const std::wstring& keyName);

    private:
        SoundManager();
        ~SoundManager();
    };
}
