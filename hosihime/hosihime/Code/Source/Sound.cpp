/*
Sound.cpp
*/
#include "Sound.h"
Sound::Sound()
{
	ses.clear();
	bgms.clear();
}
Sound::Sound(const Sound& sound)
	:ses(sound.ses), bgms(sound.bgms)
{

}
void Sound::LoadBGM(const std::string& name,const std::string& ps)
{
	std::string name_ps = ps + name;
	gsLoadBGM(bgms.size(), name_ps.c_str(),GMIDI_LOOP);
	bgms.insert(std::pair<const std::string, GSuint>(name, bgms.size()));
}

void Sound::loadSE(const std::string& name, int max, GWAVEFLAG flag,
	const std::string& ps)
{
	std::string name_ps = ps + name;
   	gsLoadSE(ses.size(), name_ps.c_str(), max, flag);
	ses.insert(std::pair<const std::string, GSuint>(name, ses.size()));
}
void Sound::playBGM(const std::string& name)const
{
	gsPlayBGM(bgms.at(name));
}
bool Sound::isPlayBGM()const
{
	return !!gsIsPlayBGM();
}
void Sound::pauseBGM()const
{
	gsPauseBGM();
}
void Sound::restartBGM()const
{
	gsRestartBGM();
}
void Sound::stopBGM()const
{
	gsStopBGM();
}

void Sound::playSE(const std::string& name)const
{
	gsPlaySE(ses.at(name));
}
bool Sound::isPlaySE(const std::string& name)const
{
	return !!gsIsPlaySE(ses.at(name));
}
void Sound::stopSE(const std::string& name)const
{
	gsStopSE(ses.at(name));
}
void Sound::release()
{
	for (auto itr = bgms.begin(); itr != bgms.end(); ++itr)
	{
		gsDeleteBGM(itr->second);
	}
	bgms.clear();
	for (auto itr =ses.begin(); itr != ses.end(); ++itr)
	{
		gsDeleteSE(itr->second);
	}
	ses.clear();
}