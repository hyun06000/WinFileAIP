// WinFileAIP.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

/*
* 작성일 : 20210104
* 작성자 : davi06000
* 
* 소스에 관한 설명
* 
* https://davi06000.tistory.com/manage/newpost/?type=post&returnURL=%2Fmanage%2Fposts
* 
* 내용
* 
* Windows에서 제공하는ㄹileAPI를 이해하기위한 간단한 튜토리얼
* 
* 참고
* https://raisonde.tistory.com/entry/Windows-API-%ED%8C%8C%EC%9D%BC-%EC%97%B4%EA%B8%B0-%EC%9D%BD%EA%B8%B0-%EC%93%B0%EA%B8%B0-%EB%8B%AB%EA%B8%B0
* https://noirstar.tistory.com/11
* http://blog.daum.net/redhair/18266970
* https://m.blog.naver.com/PostView.nhn?blogId=isentator&logNo=10183690935&proxyReferer=https:%2F%2Fwww.google.com%2F
*  
*/

#include <iostream>
#include <string>

#include <Windows.h> // 윈도우즈 기능을 사용하기 위함.
#include <tchar.h>   // LPCTSTR (Long Point Constant Tstring), TCHAR을 쓰기 위한 라이브러리
#include <locale.h>  

int _tmain(int argc, LPTSTR argv[])
{
    HANDLE fHandle;
    TCHAR Strings[] = _T("AABBCCDDEEFFGGHHIIJJKKLLMMNNOOPP");
    //DWORD result;
    LARGE_INTEGER curPtr;
    _wsetlocale(
        LC_ALL,
        _T("Korean")
    );

    fHandle = CreateFile(                // HANDLE CreateFile();
        _T("data.txt"),                  // LPCTSTR lpFileName, TCHAR 타입의 파일이름
        GENERIC_READ | GENERIC_WRITE,    // DWORD dwDesiredAccess, 만들고자 하는 파일의 접근 권한 |(or) 를 이용해서 여러개 적을 수 있다.
        0,                               // DWORD dwShareMode, 다른 프로세스에서 이 파일에 접근할때의 권한 마찬가지로 | 사용가능
        NULL,                            // LPSECURITY_ATTRIBUTES lpSecurityAttributes, 보안에 관련된 구조체 설정. 기본적으로 NULL을 쓴다.
        CREATE_ALWAYS,                   // dwCreationDisposition, 파일을 새로 만들어서 열지 기존의 파일을 열어서 수정할지 결정하는 옵션.
        0,                               // DWORD dwFlagsAndAttributes, 파일의 특성을 지정하는 플래그. 기존의 파일을 열때는 무시된다. 일반적으로 0
        NULL);                           // HANDLE hTemplateFile, 존재하는 파일을 열었을때 기존 파일의 핸들. 일반적으로 NULL

    // fHandle = [/]

    WriteFile(                           //BOOL WINAPI WriteFile();
        fHandle,                         // HANDLE hFile, 만들어둔 파일의 핸들.
        _T("abcdefghijklmnopqrs"),                // LPCVOID lpBuffer, 핸들로 다루는 파일에 쓰고싶은 데이터
        sizeof(TCHAR) * 13,               // DWORD nNumberOfBytesToWrite, 얼마나 쓸 것인가
        NULL,//&result,                         // LPDWORD lpNumberOfBytesWritten, 얼마나 쓰여졌는가에 대한 결과값
        NULL                             // LPOVERLAPPED lpOverlapped, 어려운거. NULL을 일반적으로 넣어줌
    );

    // fHandle = [/abcdefghijklm]

    //_tprintf(_T("쓰여진 바이트 수 : %d\n"), result);
    
    curPtr.QuadPart = sizeof(TCHAR)*4;     // 파일 포인터 조정
    
    SetFilePointerEx(                    // BOOL WINAPI SetFilePointerEx(); 파일 내에서 이동할 포인터 조작 함수
        fHandle,                         // 핸들 
        curPtr,                          // 얼마나 이동할 것인가
        NULL,                            // 이동이 끝난 결과 값이 궁금할 때
        FILE_BEGIN                       // 어디서 시작해서 이동할 것인가 (FILE_BEGIN, FILE_END,FILE_CURRENT)
    );
    //     curPtr |--->|
    // fHandle = [ abcd efghijklm]

    _tprintf(_T("%s\n"), Strings);

    ReadFile(                            // BOOL WINAPI ReadFile()
        fHandle,                         // HANDLE hFile,
        Strings,                         // LPVOID lpBuffer,
        sizeof(TCHAR)*7,                 // DWORD nNumberOfBytesToRead,
        NULL,//&result,                         // LPDWORD lpNumberOfBytesRead,
        NULL                             // LPOVERLAPPED lpOverlapped,
    );
    //     curPtr      |------>|
    // fHandle = [ abcd efghijk lm]


    //_tprintf(_T("읽혀진 바이트 수 : %d\n현재 포인터 위치 : %d\n"), result, curPtr.QuadPart);

    _tprintf(_T("%s\n"), Strings);

    CloseHandle(fHandle);
}