# Search-Words-in-Script
유닉스 커널에서 제공하는 저수준 입출력 함수를 이용해 스크립트(대본) 파일에서 원하는 단어/구절 찾기 프로그램

저수준 입출력 함수들을 이용해 대본 등의 txt 파일에서 사용자에게 입력받은 단어/구절의 위치를 찾아 출력한다.

## 프로그램 사용
네 가지 형태의 입력이 가능하다.


### 1. Searching single word locations
프로그램에서 하나의 단어를 입력받는 경우, 단어의 위치를 찾는다.

- txt파일에서 입력받은 단어 포함되 행을 찾아 다음의 형식으로 STDOUT에 출력한다.

<div align=center>"[line number]:[start index of the word]"</div>


### 2. Searching several words locations
프로그램이 여러 단어(공백 하나로 구분)을 입력받는 경우, 입력된 모든 단어를 포함하는 행을 찾는다.

- 영화 시나리오에서 입력 받은 단어가 모두 포함된 행을 찾아 STDOUT에 출력한다.

<div align=center>"[line number]"</div>


### 3. Searching several consecutive words locations
프로그램에서 ""로 싸여진 구문을 입력 받는 경우, 구문의 위치를 찾는다.

- 구문 내에는 개행문자가 존재하지 않는다.
- 구문 내에는 연속한 공백 및 탭이 존재할 수 있다.
- 영화 시나리오에서 입력 받은 구문이 포함된 행을 찾아 다음의 형식으로 STDOUT에 출력한다.

<div align=center>"[line number]:[start index of the word]"</div>


### 4. Searching simple regular expressing keyword locations
프로그램에서 [단어1]*[단어2]로 구성된 "두 개의 단어"를 입력 받는 경우, [단어1]과 [단어2] 사이에 하나 이상의 문자가 포함된 행을 찾는다.

- [단어1]과 *, *과 [단어2] 사이에는 빈 칸이 없다.
- [단어2]*[단어1]의 경우는 고려하지 않는다.
- 영화 시나리오에서 위의 설명에 해당하는 행을 찾아 STDOUT에 출력한다.

<div align=center>"[line number]"</div>
