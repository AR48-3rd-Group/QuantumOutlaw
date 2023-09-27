#include "qoSoundManager.h"

namespace qo
{
    SoundManager::SoundManager()
        : _system(nullptr)
        , _sound(nullptr)
        , _channel(nullptr)
    {
    }

    SoundManager::~SoundManager()
    {
        Release();
    }

    void SoundManager::Init()
    {
        // Sound system creation
        System_Create(&_system);

        // Set the number of sound channels
        _system->init(TOTAL_SOUND_BUFFER, FMOD_INIT_NORMAL, 0);

        // Dynamic allocation for sound channels
        _sound = new Sound * [TOTAL_SOUND_BUFFER];
        _channel = new Channel * [TOTAL_SOUND_BUFFER];

        // Memory initialization
        memset(_sound, 0, sizeof(Sound*) * TOTAL_SOUND_BUFFER);
        memset(_channel, 0, sizeof(Channel*) * TOTAL_SOUND_BUFFER);
    }

    void SoundManager::Release()
    {
        // Release sound channels
        if (_channel != nullptr || _sound != nullptr)
        {
            for (int i = 0; i < TOTAL_SOUND_BUFFER; i++)
            {
                if (_channel != nullptr) _channel[i]->stop();
                if (_sound != nullptr) _sound[i]->release();
            }
        }

        SAFE_DELETE_ARRAY(_sound);
        SAFE_DELETE_ARRAY(_channel);

        // Close and release the sound system
        if (_system != nullptr)
        {
            _system->release();
            _system->close();
        }
    }

    void SoundManager::Update()
    {
        _system->update();
    }

    void SoundManager::Render()
    {
        // Add rendering logic if needed
    }

    void SoundManager::AddSound(const std::wstring& keyName, const std::wstring& soundName, bool bgm, bool loop)
    {
        // Determine sound flags based on loop and bgm settings
        int soundFlags = FMOD_DEFAULT;
        if (loop)
        {
            soundFlags |= FMOD_LOOP_NORMAL;
        }

        // Create the sound based on flags
        if (bgm)
        {
            _system->createStream(soundName.c_str(), soundFlags, 0, &_sound[_mTotalSound.size()]);
        }
        else
        {
            _system->createSound(soundName.c_str(), soundFlags, 0, &_sound[_mTotalSound.size()]);
        }

        // Store the sound in the map
        _mTotalSound.insert(std::make_pair(keyName, &_sound[_mTotalSound.size()]));
    }

    void SoundManager::Play(const std::wstring& keyName, float volume)
    {
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to play the sound
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Find an available channel, set volume, and play the sound
                _system->playSound(FMOD_CHANNEL_FREE, *itr->second, false, &_channel[count]);
                _channel[count]->setVolume(volume);
            }
        }
    }

    void SoundManager::Stop(const std::wstring& keyName)
    {
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to stop the sound
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Stop the sound
                _channel[count]->stop();
                break;
            }
        }
    }

    void SoundManager::Pause(const std::wstring& keyName)
    {
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to pause the sound
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Pause the sound
                _channel[count]->setPaused(true);
                break;
            }
        }
    }

    void SoundManager::Resume(const std::wstring& keyName)
    {
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to resume the sound
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Resume the sound
                _channel[count]->setPaused(false);
                break;
            }
        }
    }

    bool SoundManager::IsPlaying(const std::wstring& keyName)
    {
        bool isPlaying;
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to check if the sound is playing
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Check if the sound is playing
                _channel[count]->isPlaying(&isPlaying);
                break;
            }
        }

        return isPlaying;
    }

    bool SoundManager::IsPaused(const std::wstring& keyName)
    {
        bool isPaused;
        int count = 0;
        SoundMapIterator itr = _mTotalSound.begin();

        // Search for the channel to check if the sound is paused
        for (itr; itr != _mTotalSound.end(); itr++, count++)
        {
            if (keyName == itr->first)
            {
                // Check if the sound is paused
                _channel[count]->getPaused(&isPaused);
                break;
            }
        }

        return isPaused;
    }
}
