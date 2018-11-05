#pragma once
#include "SingleTon.h"

class TextData : public SingletonBase<TextData>
{
	typedef map<std::pair<string, string>, string> INIMap;			// 맵형식으로 파일을 관리,,,,, 불러오기
	typedef map<std::pair<string, string>, string>::iterator iINIMap;

	INIMap			mINIData;
	iINIMap			miINIData;

	string			strPath;

public:
	TextData();
	~TextData();

	bool			Init();
	void			Release();

	void			txtSave(const TCHAR* saveFileName, vector<string> vStr);
	TCHAR*			vectorArrayCombine(vector<string> vArray);

	vector<string>	txtLoad(const TCHAR* loadFileName);
	vector<string>	charArraySeparation(TCHAR charArray[]);

	string			GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile);
	void			SetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile);



};

