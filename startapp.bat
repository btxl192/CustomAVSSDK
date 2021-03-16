if not exist ".\firststart" pip install flask
if not exist ".\firststart" pip install eventlet
if not exist ".\firststart" pip install pvporcupine
if not exist ".\firststart" pip install pyaudio
if not exist ".\firststart" pip install eng_to_ipa

echo. > ".\firststart"

if not exist .\build\bin\audioOutput\NUL mkdir .\build\bin\audioOutput
if not exist .\build\bin\textOutput\NUL mkdir .\build\bin\textOutput
DEL .\build\bin\textOutput\*.txt
echo 1 > ".\build\bin\alexaInput.txt"
echo. >> ".\build\bin\alexaInput.txt"
start startsample.bat
start startaudiohost.bat