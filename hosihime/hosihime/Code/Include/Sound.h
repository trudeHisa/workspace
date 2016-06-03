/*
Sound.h
*/
#ifndef _SOUND_H_
#define _SOUND_H_
#include <gslib.h>
#include <map>
class Sound
{
public:
	Sound();
	Sound(const Sound& sound);
	void LoadBGM(const std::string& name,
		const std::string& ps = "Sound\\\\BGM\\\\");
	/*
	同時再生最大数 max,再生モード flag
	GWAVE_WAIT 他の再生中ウェイト
	GWAVE_LOOP ループ再生
	GWAVE_DEFAULT 
	*/
	void LoadSE(const std::string& name, int max, 
		GWAVEFLAG flag = GWAVE_DEFAULT,
		const std::string& ps = "Sound\\\\SE\\\\");
	void Release();

	void PlayBGM(const std::string& name)const;
	void PauseBGM()const;
	void RestartBGM()const;
	bool IsPlayBGM()const;
	void StopBGM()const;

	void PlaySE(const std::string& name)const;	
	bool IsPlaySE(const std::string& name)const;
	void StopSE(const std::string& name)const;
private:
	std::map<const std::string, GSuint>ses;
	std::map<const std::string, GSuint>bgms;
};
#endif