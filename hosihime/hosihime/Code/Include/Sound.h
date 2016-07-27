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
	�����Đ��ő吔 max,�Đ����[�h flag
	GWAVE_WAIT ���̍Đ����E�F�C�g
	GWAVE_LOOP ���[�v�Đ�
	GWAVE_DEFAULT 
	*/
	void loadSE(const std::string& name, int max, 
		GWAVEFLAG flag = GWAVE_DEFAULT,
		const std::string& ps = "Sound\\\\SE\\\\");
	void release();

	void playBGM(const std::string& name)const;
	void pauseBGM()const;
	void restartBGM()const;
	bool isPlayBGM()const;
	void stopBGM()const;

	void playSE(const std::string& name)const;	
	bool isPlaySE(const std::string& name)const;
	void stopSE(const std::string& name)const;
private:
	std::map<const std::string, GSuint>ses;
	std::map<const std::string, GSuint>bgms;
};
#endif