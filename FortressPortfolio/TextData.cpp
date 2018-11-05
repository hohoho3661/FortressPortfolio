#include "stdafx.h"
#include "TextData.h"



TextData::TextData()
{
}


TextData::~TextData()
{
}

bool TextData::Init()
{
	return true;
}

void TextData::Release()
{
	getSingleton()->releaseSingleton();
}

void TextData::txtSave(const TCHAR * saveFileName, vector<string> vStr)	// vector에 들어있는 자료를 파일로 끄집어 내는 작업,,
{
	HANDLE	file;
	TCHAR	str[128];
	DWORD	write;

	_tcsncpy_s(str, 128, vectorArrayCombine(vStr), 126);

	// 윈도우 api로 쓸때
	//                파일이름 ,     엑세스 방식,  공유모드 할건지, 보안 속성, 생성방식,       파일속성,               템플릿파일
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL,         NULL,      CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL); // 파일의 핸들을 얻고
	//        핸들, 버퍼, 포인트, 버퍼사이즈, lpOverlapped
	WriteFile(file, str, 128,    &write,    NULL);																// 얻은 핸들로 사용
	CloseHandle(file);																						// 파일 닫기


	//// 씨 스타일 형으로 쓸때
	//FILE*	pf;
	//fopen_s(&pf, "경로", "모드");
	//fread(buffer, 사이즈, 카운트, pf);
	//fwrite(buffer, 사이즈, 카운트, pf);
	//fclose(pf);
}

TCHAR * TextData::vectorArrayCombine(vector<string> vArray) // 백터를 스트링으로 만들어줌,,    결합?
{
	char str[128];				// 사이즈 제약이 있다. --> 가장큰 문제점
	ZeroMemory(str, sizeof(str));

	for (int i = 0; i < vArray.size(); i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 126);

		if (i + 1 < vArray.size())
		{
			_tcscat_s(str, sizeof(str), ",");
		}
	}
	
	return str;
}

vector<string> TextData::txtLoad(const TCHAR * loadFileName)
{
	HANDLE	file;
	char	str[128];
	DWORD	read;

	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, 128, &read, NULL);

	CloseHandle(file);

	return charArraySeparation(str);
}

vector<string> TextData::charArraySeparation(TCHAR charArray[])
{
	vector<string> vArray;

	const TCHAR* separator = TEXT(","); // 분리 기호를 지정
	TCHAR* token;

	token = _tcstok(charArray, separator);
	vArray.push_back(token);
	while (NULL != (token = _tcstok(NULL, separator)))
	{
		vArray.push_back(token);
	}
	
	return vArray;	
}

string TextData::GetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszFile)
{
	return string();
}

void TextData::SetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszData, const TCHAR * pszFile)
{
}
