/*****************************************************************//**
 * \file   SoundManager.h
 * \brief  BGMSEを管理するクラス
 * \author momoka
 * \date   2021 2/2
 *********************************************************************/
#pragma once
#include <Tchar.h>
#include <vector>

class SoundManager {
public:
	SoundManager();
	virtual ~SoundManager();

	enum class BGM{
		Title = 0,
		InGame,

		Max
	};

	enum class SECommon{
		Select = 0,  //高音フォーン
		OK,   //ダークな決定音
		Cancel,  //ダークな決定音の対キャンセル音
		Mistake,
		BarUp,
		BarDown,

		Max
	};

	enum class SETitle {
		Select = 0,

		Max
	};

	enum class SEDeckSelect {
		ChoiceMove = 0,

		Max
	};

	enum class InGame {
		BoxOpen = 0,

		Max
	};

	bool Init();

	
	bool LoadSECommon();
	void DeleteSECommon();
	bool PlaySECommon(SECommon type, int delayFrame = 0);

	bool LoadSETitle();
	void DeleteSETitle();
	bool PlaySETitle(SETitle type, int delayFrame = 0);

	bool LoadSEDeckSelect();
	void DeleteSEDeckSelect();
	bool PlaySEDeckSelect(SEDeckSelect type, int delayFrame = 0);

	bool LoadSEInGame();
	void DeleteSEInGame();
	bool PlaySEInGame(InGame type, int delayFrame = 0);
	

	void Process();
	bool PlayBgm(BGM bgm);
	void DirectStopBgm();
	void FadeStopBgm(int fadeFrame);

private:

	struct DelayPlay{
		int delayFrame;
		int handle;
	};

	bool LoadSE(std::vector<const TCHAR*>& fileNameList, std::vector<int>& handleList);
	void DeleteSE(std::vector<int>& handleList);
	bool PlaySE(int handle, int delayFrame);

	std::vector<const TCHAR*> _vBgmFileName;
	std::vector<struct DelayPlay> _vDelayPlay;

	std::vector<int> _vSECommonHandle;
	std::vector<int> _vSETitleHandle;
	std::vector<int> _vSETitleMenuHandle;
	std::vector<int> _vSEDeckSelectHandle;
	std::vector<int> _vSEInGameHandle;

	BGM _nowPlayBgm;

	int _bgmFadeCount;
	float _bgmFadeFrame;
};