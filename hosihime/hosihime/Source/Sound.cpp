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
	bgms[name] = bgms.size();
}

void Sound::LoadSE(const std::string& name, int max, GWAVEFLAG flag,
	const std::string& ps)
{
	std::string name_ps = ps + name;
   	gsLoadSE(ses.size(), name_ps.c_str(), max, flag);
	ses[name] = ses.size();
}
void Sound::PlayBGM(const std::string& name)
{
	gsPlayBGM(bgms[name]);
}
bool Sound::IsPlayBGM()
{
	return !!gsIsPlayBGM();
}
void Sound::PauseBGM()
{
	gsPauseBGM();
}
void Sound::RestartBGM()
{
	gsRestartBGM();
}
void Sound::StopBGM()
{
	gsStopBGM();
}
void Sound::PlaySE(const std::string& name)
{
	gsPlaySE(ses[name]);
}
bool Sound::IsPlaySE(const std::string& name)
{
	return !!gsIsPlaySE(ses[name]);
}
void Sound::Release()
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